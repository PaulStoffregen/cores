#if ARDUINO >= 100
#include "Arduino.h"
#include "IPAddress.h"

IPAddress::IPAddress()
{
    _address.dword = 0;
}

IPAddress::IPAddress(uint8_t first_octet, uint8_t second_octet, uint8_t third_octet, uint8_t fourth_octet)
{
    _address.bytes[0] = first_octet;
    _address.bytes[1] = second_octet;
    _address.bytes[2] = third_octet;
    _address.bytes[3] = fourth_octet;
}

IPAddress::IPAddress(uint32_t address)
{
    _address.dword = address;
}

IPAddress::IPAddress(const uint8_t *address)
{
    memcpy(_address.bytes, address, sizeof(_address));
}

IPAddress& IPAddress::operator=(const uint8_t *address)
{
    memcpy(_address.bytes, address, sizeof(_address.bytes));
    return *this;
}

IPAddress& IPAddress::operator=(uint32_t address)
{
    _address.dword = address;
    return *this;
}

bool IPAddress::operator==(const uint8_t* addr)
{
    return memcmp(addr, _address.bytes, sizeof(_address.bytes)) == 0;
}

size_t IPAddress::printTo(Print& p) const
{
    for (int i= 0; i < 3; i++) {
        p.print(_address.bytes[i], DEC);
        p.print('.');
    }
    p.print(_address.bytes[3], DEC);
    return 4;
}

#endif
