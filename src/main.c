// Wokwi Custom Chip - For information and examples see:
// https://link.wokwi.com/custom-chips-alpha
//
// SPDX-License-Identifier: MIT
// Copyright (C) 2022 Uri Shaked / wokwi.com

#include "wokwi-api.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EEPROM_SIZE 0x100

const int BASE_ADDRESS = 0x50;

typedef enum {
  IDLE,
  ADDRESS_1,
  DATA
} eeprom_state_t;

typedef struct {
  eeprom_state_t state;
  pin_t pin_a0;
  pin_t pin_a1;
  pin_t pin_a2;
  pin_t pin_wp;
  uint16_t address_register;
  uint8_t mem[EEPROM_SIZE];
  uint8_t byte_counter;
} chip_state_t;


static bool on_i2c_connect(void *user_data, uint32_t address, bool connect);
static uint8_t on_i2c_read(void *user_data);
static bool on_i2c_write(void *user_data, uint8_t data);
static void on_i2c_disconnect(void *user_data);


static uint8_t get_addr(chip_state_t *chip) {
  uint8_t address = BASE_ADDRESS;
  address |= pin_read(chip->pin_a2) << 2;
  address |= pin_read(chip->pin_a1) << 1;
  address |= pin_read(chip->pin_a0);

  return address;
}

void chip_init(void) {
  chip_state_t *chip = malloc(sizeof(chip_state_t));
  uint8_t address = get_addr(chip);
  chip->pin_a0 = pin_init("A0", INPUT);
  chip->pin_a1 = pin_init("A1", INPUT);
  chip->pin_a2 = pin_init("A2", INPUT);
  chip->pin_wp = pin_init("WP", INPUT);
  chip->address_register = 0;
  memset(chip->mem, 0, EEPROM_SIZE);
  chip->state = IDLE;
  chip->byte_counter = 0;

    const i2c_config_t i2c_config = {
    .user_data = chip,
    .address = address,
    .scl = pin_init("SCL", INPUT),
    .sda = pin_init("SDA", INPUT),
    .connect = on_i2c_connect,
    .read = on_i2c_read,
    .write = on_i2c_write,
    .disconnect = on_i2c_disconnect, // Optional
  };
  i2c_init(&i2c_config);



  // The following message will appear in the browser's DevTools console:
  printf("Hello from 24c01 at address %x \n", address);
}

bool on_i2c_connect(void *user_data, uint32_t address, bool connect) {
  return true; /* Ack */
}

uint8_t on_i2c_read(void *user_data) {
  chip_state_t *chip = user_data;
  uint8_t data = chip->mem[chip->address_register];
  chip->address_register = (chip->address_register + 1) & 0xff /*0x7ffff*/;
  return data;
}

bool on_i2c_write(void *user_data, uint8_t data) {
  chip_state_t *chip = user_data;
  switch(chip->state)
  {
    case IDLE:
      chip->address_register = (data & 0x7f) << 8;
      chip->state = ADDRESS_1;
    break;
    case ADDRESS_1:
      chip->address_register |= data;
      chip->state = DATA;
    break;
    case DATA:
      if (chip->byte_counter > 63) {
        return false;
      }
      chip->mem[chip->address_register] = data;
      chip->address_register = (chip->address_register + 1) & 0xff /*0x7ffff*/;
    break;
    default:
      printf("error");
    break;
  }
    return true; // Ack
}

void on_i2c_disconnect(void *user_data) {
  chip_state_t *chip = user_data;
  chip->state = IDLE;
}