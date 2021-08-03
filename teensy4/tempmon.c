#include "imxrt.h"
#include "core_pins.h"
#include "avr/pgmspace.h"
#include "debug/printf.h"


static uint16_t frequency = 0x03U;
static uint32_t highAlarmTemp   = 85U;
static uint32_t lowAlarmTemp    = 25U;
static uint32_t panicAlarmTemp  = 90U;

static uint32_t s_hotTemp, s_hotCount;
static float s_hot_ROOM, s_roomC_hotC;

extern void unused_interrupt_vector(void); // startup.c

void Panic_Temp_isr(void) {
  unused_interrupt_vector();
  //IOMUXC_GPR_GPR16 = 0x00000007;
  //SNVS_LPCR |= SNVS_LPCR_TOP; //Switch off now
  //asm volatile ("dsb":::"memory");
  //while (1) asm ("wfi");
}

FLASHMEM void tempmon_init(void)
{
  // Notes:
  //    TEMPMON_TEMPSENSE0 &= ~0x2U;  Stops temp monitoring
  //    TEMPMON_TEMPSENSE0 |= 0x1U;   Powers down temp monitoring 
  uint32_t calibrationData;
  uint32_t roomCount;
  uint32_t tempCodeVal;
      
  //first power on the temperature sensor - no register change
  TEMPMON_TEMPSENSE0 &= ~0x1U;

  //set monitoring frequency - no register change
  TEMPMON_TEMPSENSE1 = (((uint32_t)(((uint32_t)(frequency)) << 0U)) & 0xFFFFU);
  
  //read calibration data - this works
  calibrationData = HW_OCOTP_ANA1;
    s_hotTemp = (uint32_t)(calibrationData & 0xFFU) >> 0x00U;
    s_hotCount = (uint32_t)(calibrationData & 0xFFF00U) >> 0X08U;
    roomCount = (uint32_t)(calibrationData & 0xFFF00000U) >> 0x14U;
    s_hot_ROOM = (float) (s_hotTemp) - 25.0f;
    s_roomC_hotC = (float) roomCount - (float) s_hotCount;

    //time to set alarm temperatures
  //Set High Alarm Temp
  tempCodeVal = ((float)s_hotCount + ((float)s_hotTemp - highAlarmTemp) * s_roomC_hotC / s_hot_ROOM);
    TEMPMON_TEMPSENSE0 |= (((uint32_t)(((uint32_t)(tempCodeVal)) << 20U)) & 0xFFF00000U);
  
  //Set Panic Alarm Temp
  tempCodeVal = ((float)s_hotCount + ((float)s_hotTemp - panicAlarmTemp) * s_roomC_hotC / s_hot_ROOM);
    TEMPMON_TEMPSENSE2 |= (((uint32_t)(((uint32_t)(tempCodeVal)) << 16U)) & 0xFFF0000U);
  
  // Set Low Temp Alarm Temp
  tempCodeVal = ((float)s_hotCount + ((float)s_hotTemp - lowAlarmTemp) * s_roomC_hotC / s_hot_ROOM);
    TEMPMON_TEMPSENSE2 |= (((uint32_t)(((uint32_t)(tempCodeVal)) << 0U)) & 0xFFFU);
  
  //Start temp monitoring
  TEMPMON_TEMPSENSE0 |= 0x2U;   //starts temp monitoring

  //PANIC shutdown:
  NVIC_SET_PRIORITY(IRQ_TEMPERATURE_PANIC, 0);
  attachInterruptVector(IRQ_TEMPERATURE_PANIC, &Panic_Temp_isr);
  NVIC_ENABLE_IRQ(IRQ_TEMPERATURE_PANIC);
}


float tempmonGetTemp(void)
{
    uint32_t nmeas;
    float tmeas;

    while (!(TEMPMON_TEMPSENSE0 & 0x4U))
    {
    }

    /* ready to read temperature code value */
    nmeas = (TEMPMON_TEMPSENSE0 & 0xFFF00U) >> 8U;
    /* Calculate temperature */
    tmeas = s_hotTemp - (((float)nmeas - (float)s_hotCount) * s_hot_ROOM / s_roomC_hotC);

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
