#include <Wire.h>
#define EEPROM_I2C_ADDRESS 0x50

bool is_device_available(uint8_t address)
{
  Wire.beginTransmission(address);
  uint8_t error = Wire.endTransmission();

  return (error == 0);
}

void wait_for_device(uint8_t i2c_device_address) {
  while(!is_device_available(i2c_device_address));
}

void eeprom_write_byte(uint8_t i2c_device_address, uint16_t eeprom_data_address, uint8_t data) {
  Wire.beginTransmission(i2c_device_address);
  Wire.write((uint8_t)(eeprom_data_address >> 8)); //writes the MSB
  Wire.write((uint8_t)(eeprom_data_address & 0xFF)); //writes the LSB
  Wire.write(data);
  Wire.endTransmission();
  wait_for_device(i2c_device_address);
}

byte eeprom_read_byte(uint8_t i2c_device_address, uint16_t eeprom_data_address) {
  uint8_t rdata = 0xFF;

  Wire.beginTransmission(i2c_device_address);
  Wire.write((uint8_t)(eeprom_data_address >> 8)); //writes the MSB
  Wire.write((uint8_t)(eeprom_data_address & 0xFF)); //writes the LSB
  Wire.endTransmission();
  Wire.requestFrom(i2c_device_address,(uint8_t)1);
  if (Wire.available()) {
    rdata = Wire.read();
  }
  return rdata;
}

void setup()
{
  Wire.begin();

  Serial.begin(9600);
  while (!Serial);

  if (!is_device_available(EEPROM_I2C_ADDRESS))
  {
    Serial.println("No device was found");
    while(true);
  }

  eeprom_write_byte(EEPROM_I2C_ADDRESS, 0x123, 0xf4);
  byte data = eeprom_read_byte(EEPROM_I2C_ADDRESS, 0x123);
  if(data == 0xf4) {
    Serial.println("Works");
  } else {
    Serial.println("Doesn't work");
  }
}

void loop()
{

}
