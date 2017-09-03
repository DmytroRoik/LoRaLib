#ifndef _LORALIB_MODULE_H
#define _LORALIB_MODULE_H

#include <SPI.h>

#include "TypeDef.h"

#define SPI_READ  0b00000000
#define SPI_WRITE 0b10000000

class Module {
  public:
    virtual uint8_t begin(void) = 0;
    
    virtual uint8_t tx(char* data, uint8_t length) = 0;
    virtual uint8_t rxSingle(char* data, uint8_t* length) = 0;
    
    virtual uint8_t setMode(uint8_t mode) = 0;
    virtual uint8_t config(uint8_t bw, uint8_t sf, uint8_t cr) = 0;
    virtual int8_t getLastPacketRSSI(void) = 0;
    
    uint8_t initModule(int nss);
    
    uint8_t getRegValue(uint8_t reg, uint8_t msb = 7, uint8_t lsb = 0);
    uint8_t readRegisterBurst(uint8_t reg, uint8_t numBytes, uint8_t* inBytes);
    uint8_t readRegisterBurstStr(uint8_t reg, uint8_t numBytes, char* str);
    uint8_t readRegister(uint8_t reg);
    
    uint8_t setRegValue(uint8_t reg, uint8_t value, uint8_t msb = 7, uint8_t lsb = 0);
    void writeRegisterBurst(uint8_t reg, uint8_t* data, uint8_t numBytes);
    void writeRegisterBurstStr(uint8_t reg, const char* data, uint8_t numBytes);
    void writeRegister(uint8_t reg, uint8_t data);
  
  private:
    int _nss = 0;
    int _dio0 = 2;
    int _dio1 = 3;
    
    #if defined(__AVR_ATmega168__) || defined(__AVR_ATmega328P__)
      int _sck = 13;
      int _miso = 12;
      int _mosi = 11;
    #elif defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
      int _sck = 52;
      int _miso = 50;
      int _mosi = 51;
    #else
      #error "Unsupported board selected, please select Arduino UNO or Mega"
    #endif
};

#endif
