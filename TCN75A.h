#ifndef TCN75A_ft
#define TCN75A_ft

#include "Arduino.h"
#include "Wire.h"

//im starting to regret making this library

class TCN75A{
  public:
  TCN75A(uint8_t adr);
  void begin(TwoWire &wire = Wire);
  
  float readTemperature(); //read temperature as normal
  
  /* alert craps
   * val = value, take in as decimal
   * take in val, round down
   * val - round down val; if < 0.5, use round down value
   * if == 0.5, use that val + lsb, if > 0.5, use round up value
   */
  void setHystTemp(float val); //ditto, set limit-set temp
  void setLimitTemp(float val); //ditto
  void setRangeTemp(float val_down, float val_up);
  float getLimitTemp(); //get limit-set
  float getHystTemp(); //get hysteresis loop
  
  //config registers
  void setOneShot(bool sw); // 1 = enabled, 0 = disabled (def)
  void setResolution(uint8_t val); // need some constants 0.5 = def
  void setFaultQueue(uint8_t val); // why -> 00 = def
  void setAlertPolarity(bool sw); //1 = active-high, 0 = active-low
  void setAlertMode(bool sw); // 1 = interrupt, 0 = comparator (def)
  void setShutdown(bool sw); // 1 = enable, 0 = disable (def)
  //remember. use bitWrite() to change a bit in the read byte
  private:
  uint8_t readConfig();
  void writeConfig(uint8_t data);
  float getTemp(uint8_t p); //reducing nuisance
  void setTemp(uint8_t p, float value); //same here
  float fractalCalc(String bin);
  TwoWire *_wire;
  uint8_t _adr;
};

#endif

/* 
 * 
 */
