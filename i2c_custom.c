/*
    - I2C1_SCL - PB6 - D5 Alternate Function
    - I2C1_SDA - PB7 - D4 Alternate Function
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "uart.h"
#include "i2c_custom.h"
#include "systick.h"

uint32_t string_len(const uint8_t *str) {
    uint32_t length = 0;
    while(*str != '\0') {
        str++;
        length++;
    }

    return length;
}

uint32_t power(uint16_t base, uint16_t exponent) {
    uint32_t result = 1;
    
    for(uint16_t i = 0; i < exponent; i++) {
        result = result * base;
    }
    return result;
}

//Keeping this, could be valuable elsewhere
static uint32_t string_to_num(uint8_t *input) {
    uint32_t number = 0;
    
    if(input[0] == '-') {
        ++input;
        while(*input != '\0') {
            number *= 10;
            number += (*input - '0');
            ++input;
        }
        int negate = number + number;
        number -= negate;
        return number;
    }
    
    while(*input != '\0') {
        number *= 10;
        number += (*input - '0');
        ++input;
    }
    
    return number;
}

//Setting NBYTE size, each address frame is 1 byte = 8 bits = data frame, after each address frame, target will send an NACK and then a stop or another data frame will be sent
void set_nbytes(uint32_t size) {
    I2C_CR2 -> NBYTES = 0;
    I2C_CR2 -> NBYTES = size;
}

void get_nbytes(uint8_t *data) {
    uint16_t i = 0;
    while(i < 8) {
        while(!(I2C_ISR -> RXNE & (1 << 0))) {};
        data[i] = I2C_RXDR -> RXDATA;
        i++;
    }
    data[8] = '\0';
}

void get_data(uint8_t *text, uint32_t length) {
    uint16_t i = 0;
    while(i < length) {
        while(!(I2C_ISR -> RXNE & (1 << 0))) {};
        text[i] = I2C_RXDR -> RXDATA;
        i++;
    }
    text[(length - 8)] = '\0';
}

//Convert hex to decimal
uint32_t hex_to_decimal(uint8_t *data) {
    uint16_t i = 0;
    uint32_t decimal = 0;
    while(i < 8) {
        if(data[i] > 64 && data[i] < 71) {
            decimal += (data[i] - 'A' + 10) * power(16, i);
        } else if(data[i] > 41 && data[i] < 65) {
            decimal += (data[i] - '0') * power(16, i);
        }
        i++;
    }

    return decimal;
}

void i2c_init(void) {
    volatile uint32_t *RCC_AHBENR = (uint32_t *) 0x40021014;
    volatile uint32_t *GPIO_MODER = (uint32_t *) 0x48000400;
    volatile uint32_t *GPIO_OTYPER = (uint32_t *) 0x48000404;
    volatile uint32_t *GPIO_PUPDR = (uint32_t *) 0x4800040C;
    volatile uint32_t *GPIO_AFRL = (uint32_t *) 0x48000420;

    *RCC_AHBENR |= (1 << 18);
    *GPIO_MODER |= (2 << 14); //Alternate function mode for PB7
    *GPIO_MODER |= (2 << 12); //Alternate function mode for PB6

    *GPIO_OTYPER |= (1 << 7); //Open drain for PB7
    *GPIO_OTYPER |= (1 << 6); //Open drain for PB6

    *GPIO_PUPDR |= (1 << 14); //Using internal pull up for PB7
    *GPIO_PUPDR |= (1 << 12); //Using internal pull up for PB6

    *GPIO_AFRL |= (4 << 28); //AF4 for PB7
    *GPIO_AFRL |= (4 << 24); //AF4 for PB6

    //Set the I2C interface
    volatile uint32_t *RCC_APB1ENR = (uint32_t *) 0x4002101C;

    *RCC_APB1ENR |= (1 << 21);

    //Setting the clock speed for I2C with clock at 8MHz
    I2C_TIMINGR -> SCLL = 199; // SCLL-SCL low period (master mode) 11000111 = 0xC7
    I2C_TIMINGR -> SCLH = 195; // SCLH-SCL high period (master mode) 11000011 = 0xC3
    I2C_TIMINGR -> SDADEL = 2; // SDADEL-Data hold time 00000010 = 0x2
    I2C_TIMINGR -> SCLDEL = 4; // SCLDEL-Data setup time 00000100 = 0x4
    I2C_TIMINGR -> PRESC = 1; // PRESC-Timing prescaler 00000001 = 0x1

    //Setting the addressing mode to 7-bit
    I2C_CR2 -> ADD10 = 0;

    //Enable the peripheral PE
    I2C_CR1 -> PE = 1;
}

void i2c_write_byte (const uint8_t data) {
    set_nbytes(1);

    I2C_CR2 -> AUTOEND = 1;

    //Setting the read/write bit to write
    I2C_CR2 -> RD_WRN = 0;

    //Picking target addresss
    I2C_CR2 -> SADD = (8 << 1); 

    //Check if the bus is idle before sending anything
    while(I2C_ISR -> BUSY  & (1 << 15)){}

    while(!(I2C_ISR -> TXE & (1 << 0))){}
    I2C_TXDR -> TXDATA = (uint32_t)data;

    //Start transmission
    I2C_CR2 -> START = 1;
}

void i2c_write(const uint8_t *data) {
    const uint8_t *str_copy = data;
    uint32_t length = string_len(str_copy);
    set_nbytes(length);

    //Data transfer will end automatically; a STOP condition is automatically sent when NBYTES data transferred
    I2C_CR2 -> AUTOEND = 1;
    
    //Setting the read/write bit to write
    I2C_CR2 -> RD_WRN = 0;

    //Picking target addresss
    I2C_CR2 -> SADD = (8 << 1); 

    //Check if the bus is idle before sending anything
    while(I2C_ISR -> BUSY  & (1 << 15)){}

    //Start transmission
    I2C_CR2 -> START = 1;

    for(uint32_t i = 0; i < length; i++) {
        //Check if the TXE bit = 1, that means no data was written into the I2C_TXDR and it's empty ready for data input
        while(!(I2C_ISR -> TXE & (1 << 0))){}
        I2C_TXDR -> TXDATA = (uint32_t)data[i];
    }
}

void i2c_read_string(void) {
    //Setting the AUTOEND bit to 0, transfer will complete once the number of data bytes has been read, TC flag will be set & we get to request to STOP reading or restart the transfer
    I2C_CR2 -> AUTOEND = 0;

    //Setting NBYTES bit to 8 for now, need to know how much data the target will send first and then it can be changed based on what the target specifies
    set_nbytes(8);

    //Set the read/write bit to read
    I2C_CR2 -> RD_WRN = 1;

    I2C_CR2 -> SADD = (8 << 1);

    //Check if the bus is idle before reading anything
    while(I2C_ISR -> BUSY & (1 << 15)) {}

    //Start recieving
    I2C_CR2 -> START = 1;

    uint8_t data[8];

    get_nbytes(data);

    //Got the length of incoming string data
    uint32_t length = (hex_to_decimal(data));

    while(!(I2C_ISR -> TC & (1 << 0))) {};

    //Set the size of the incoming data
    set_nbytes(length);
    I2C_CR2 -> SADD = (8 << 1);

    uint8_t text[length];

    //Start recieving
    I2C_CR2 -> START = 1;

    get_data(text, length);

    uart_write(text, length);

    I2C_CR2 -> STOP = 1;
}

//Anything more than 33 length, is not allowed

