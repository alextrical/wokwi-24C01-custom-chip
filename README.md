
# 24C01 Custom Chip

- [todo - link to image]()
- [chip data sheet](https://ww1.microchip.com/downloads/en/DeviceDoc/21201K.pdf)

The 24C01 Custom Chip simulates the Microchip chip of the same name. It provides 1K of serial eeprom.

The chip has the following pin groups

| Name         | Description                                            |
| ------------ | ------------------------------------------------------ |
| `A0-A2`        | Address pins. See [addressing](#adressing) below for more info    |
| `VCC, GND`     | The usual power and ground pins                        |
| `SCL, SDA`      | THe I2C pins. See [I2c](#i2c-comms) below for more info           |
| `TEST`           | Output enable  pin - unused                       |

## Simulator examples

- [24C01 Custom Chip](https://wokwi.com/projects/329482717479567954)
