#include "imxrt.h"
#include "core_pins.h"
#include "avr/pgmspace.h"
#include "debug/printf.h"

static const uint16_t frequency = 0x03U;

static uint32_t s_hotTemp, s_hotCount, s_roomC_hotC;
static float s_hot_ROOM;

float tempmonGetTemp(void)
{
  uint32_t nmeas;
  float tmeas;

  while (!(TEMPMON_TEMPSENSE0 & 0x4U)) {
    ;
  }

  /* ready to read temperature code value */
  nmeas = (TEMPMON_TEMPSENSE0 & 0xFFF00U) >> 8U;
  /* Calculate temperature */
  tmeas = s_hotTemp - (float)((nmeas - s_hotCount) * s_hot_ROOM / s_roomC_hotC);

  return tmeas;
}

void tempmon_Start()
{
  TEMPMON_TEMPSENSE0 |= 0x2U;
}

void tempmon_Stop()
{
  TEMPMON_TEMPSENSE0 &= ~0x2U;
}

void tempmon_PwrDwn()
{
  TEMPMON_TEMPSENSE0 |= 0x1U;
}

FLASHMEM
static uint32_t calcTempCnt(int celsius) {
  return (uint32_t)(s_hotCount + (s_hotTemp - celsius) * s_roomC_hotC / s_hot_ROOM);
}

FLASHMEM
void tempmon_LowAlarm(int celsius) {
  TEMPMON_TEMPSENSE2 = (TEMPMON_TEMPSENSE2 & ~(0xfff)) | calcTempCnt(celsius);
}

FLASHMEM
void tempmon_HighAlarm(int celsius) {
  TEMPMON_TEMPSENSE0 = (TEMPMON_TEMPSENSE0 & ~(0xfff << 20)) | (calcTempCnt(celsius) << 20);
}

FLASHMEM
void tempmon_PanicAlarm(int celsius) {
  TEMPMON_TEMPSENSE2 = (TEMPMON_TEMPSENSE2 & ~(0xfff << 16)) | (calcTempCnt(celsius) << 16);
}

void Temp_isr(void) {
  SNVS_LPCR |= SNVS_LPCR_TOP; //switch off
  asm volatile ("dsb":::"memory");
  while (1) asm ("wfi"); //sleep if power-off did not work.
}

FLASHMEM
void tempmon_init(void)
{
  // Notes:
  //    TEMPMON_TEMPSENSE0 &= ~0x2U;  Stops temp monitoring
  //    TEMPMON_TEMPSENSE0 |= 0x1U;   Powers down temp monitoring
  uint32_t calibrationData;
  uint32_t roomCount;

  //first power on the temperature sensor - no register change
  TEMPMON_TEMPSENSE0 &= ~0x1U;

  //set monitoring frequency - no register change
  TEMPMON_TEMPSENSE1 = (((uint32_t)(((uint32_t)(frequency)) << 0U)) & 0xFFFFU);

  //read calibration data - this works
  calibrationData = HW_OCOTP_ANA1;
  s_hotTemp = (uint32_t)(calibrationData & 0xFFU) >> 0x00U;
  s_hotCount = (uint32_t)(calibrationData & 0xFFF00U) >> 0X08U;
  roomCount = (uint32_t)(calibrationData & 0xFFF00000U) >> 0x14U;
  s_hot_ROOM = s_hotTemp - 25.0f;
  s_roomC_hotC = roomCount - s_hotCount;

  //set alarm temperatures
  tempmon_LowAlarm(-100); // not used
  tempmon_HighAlarm(90); // switch off
  tempmon_PanicAlarm(92); // reset if HighAlarm was not successful

  //Start temp monitoring
  TEMPMON_TEMPSENSE0 |= 0x2U;   //starts temp monitoring

  //Init interrupt for shutdown:
  attachInterruptVector(IRQ_TEMPERATURE, &Temp_isr);
  NVIC_SET_PRIORITY(IRQ_TEMPERATURE, 0); //Use highest priority
  NVIC_CLEAR_PENDING(IRQ_TEMPERATURE);
  NVIC_ENABLE_IRQ(IRQ_TEMPERATURE);
}
