# TCN75A
Arduino Library for TCN75A, Temperature Sensor.

For more technical details, please refer to the [datasheet.](http://ww1.microchip.com/downloads/en/devicedoc/21935d.pdf)

## TCN75A Overview
## ALERT Output
### ALERT Functionality
ALERT function works by using two configurable variables: **'limit-set temperature'** and **'hysteresis temperature'.**

ALERT output is active when ambient temperature is greater than limit-set temperature, then become inactive when ambient temperature is lower than than hysteresis temperature.

### Alert Modes
- **Comparator Mode**: Send out an comparator signal (default: ACTIVE-LOW).
- **Interrupt Mode**: Send out an interrupt signal (default: ACTIVE-LOW).

## How To Use The Library
Include the library, then simply create an object like this:
```C
#include <TCN75A.h>
TCN75A tcn(*i2c address*);
```
Then in the setup function of Arduino IDE:
```C
void setup(){
  tcn.begin();
  ...
```
To use this library with other I2C ports, you can simply create a TwoWire object then parse it into the 'begin' function:
```C
// ESP32
#define I2C_SDA 33
#define I2C_SCL 32

TwoWire esp = TwoWire(0);
TCN75A tcn(*i2c address*);

void setup(){
  esp.begin(I2C_SDA, I2C_SCL, 1000000);
  tcn.begin(&esp);
}
```

## Methods
```C
void begin(TwoWire &wire = Wire);
```
Initiate the TCN75A library.

Can be configured to use other I2C ports from a 'TwoWire' object. For default I2C port, just leave the parameter blank.

```C
float readTemperature();
```
Read the temperature.

```C
void setHystTemp(float val);
void setLimitTemp(float val);
void setRangeTemp(float val_down, float val_up);
```
As following:
- Set Hysteresis Temperature, should be lower than Limit-Set Temperature. *(Default: 80.0)*
- Set Limit-Set Temperature, should be higher than Hysteresis Temperature. *(Default: 75.0)*
- Set both of them ('val_down' for hysteresis, 'val_up' for limit-set).

**^Decimal values are rounded. Unless the value is absolute '.5'**<br>
**^Input values should be in the range of -40.0 to +125.0**

```C
float getHystTemp();
float getLimitTemp();
```
As following:
- Get Hysteresis Temperature.
- Get Limit-Set Temperature.

```C
void setOneShot(bool sw);
```
Configure One-Shot Mode. *(Default: False)*

**^Perform a single measurement, then returns to shutdown mode**

```C
void setShutdown(bool sw);
```
Configure Shutdown Mode. *(Default: False)*

**^Oneshot: Disable the power-consuming activities, while leaving serial interface on.**

#### Oneshot and Shutdown Mode Description

| Oneshot | Shutdown | Operation |
|------|---------------|---------|
| logic 0 | logic 0 | Continuous Conversion |
| logic 0 | logic 1 | Shutdown |
| logic 1 | logic 0 | Continuous Conversion (Oneshot is ignored) |
| logic 1 | logic 1 | One-shot |

**^The shutdown command <01> needs to be programmed before oneshot command <11>.**


```C
void setResolution(uint8_t val);
```
Configure ADC conversion resolution. *(Default: 9-Bit)*

| val | ADC Resolution |
|------|---------------|
| 0x00 | 9-bit  |
| 0x01 | 10-bit |
| 0x02 | 11-bit |
| 0x03 | 12-bit |

**^Beyond than 0x03 will set output back to 0x03**

```C
void setFaultQueue(uint8_t val);
```
Configure Fault Queue. *(Default: 1)*

| Value | Fault Queue |
|------|---------------|
| 0x00 | 1 |
| 0x01 | 2 |
| 0x02 | 4 |
| 0x03 | 6 |

**^Fault Queue: A way to check how many times does ambient temperature remain above limit-set temperature take for ALERT to deassert or assert.**<br>
**^Beyond than 0x03 will set output back to 0x03**

```C
void setAlertPolarity(bool sw);
```
Configure Alert Polarity. *(Default: Active-Low)*

| 'sw' | Mode |
|------|---------------|
| logic 0 | Active-Low |
| logic 1 | Active-High |

```C
void setAlertMode(bool sw);
```
Configure Alert Mode. Accept the following literals. *(Default: Comparator Mode)*

| 'sw' | Literals | Mode |
|------|----------|-----------|
| logic 0 | COMP_MODE | Comparator Mode |
| logic 1 | INT_MODE | Interrupt Mode |

```C
int8_t checkConfig(uint8_t op);
```
Return the value of a specific feature. Accept the following literals.

| 'op' | Literals | Features |
|------|----------|-----------|
| 0x00 | SHUTDOWN | Shutdown |
| 0x01 | COMP_INT| Alert Mode |
| 0x02 | ALERT_POL | Alert Polarity |
| 0x03 | F_QUEUE | Fault Queue |
| 0x04 | ADC_RESO | ADC Resolution |
| 0x05 | ONESHOT | Oneshot |

**^Beyond than 0x05 will return as -1**
