# Wokwi 24C01 EEPROM Chip Example

The 24C01 Custom Chip simulates the Microchip chip of the same name. It provides 1K of serial EEPROM.

## Pin names

| Name         | Description                                            |
| ------------ | ------------------------------------------------------ |
| `A0-A2`        | Address pins. See [addressing](#adressing) below for more info    |
| GND  | Ground                   |
| VCC  | Supply voltage           |                |
| `SCL, SDA`      | THe I2C pins. See [I2c](#i2c-comms) below for more info           |
| `TEST`           | Write enable pin - unused        

## Usage

To use this chip in your project, include it as a dependency in your `diagram.json` file:

```json
  "dependencies": {
    "chip-24C01": "github:alextrical/wokwi-24C01-custom-chip@1.0.0"
  }
```

Then, add the chip to your circuit by adding a `chip-24C01` item to the `parts` section of diagram.json:

```json
  "parts": {
    ...,
    { "type": "chip-24C01", "id": "chip1" }
  },
```

For a complete example, see [the EEPROM chip test project](https://wokwi.com/projects/329482717479567954).
