#include <stdint.h>

#ifndef I2C_CUSTOM_H
#define I2C_CUSTOM_H

typedef struct _I2CCR1 {
    volatile uint32_t PE        : 1;
    volatile uint32_t TXIE      : 1;
    volatile uint32_t RXIE      : 1;
    volatile uint32_t ADDRIE    : 1;
    volatile uint32_t NACKIE    : 1;
    volatile uint32_t STOPIE    : 1;
    volatile uint32_t TCIE      : 1;
    volatile uint32_t ERRIE     : 1;
    volatile uint32_t DNF       : 4;
    volatile uint32_t ANFOFF    : 1;
    volatile uint32_t Res1      : 1;
    volatile uint32_t TXDMAEN   : 1;
    volatile uint32_t RXDMAEN   : 1;
    volatile uint32_t SBC       : 1;
    volatile uint32_t NOSTRETCH : 1;
    volatile uint32_t WUPEN     : 1;
    volatile uint32_t GCEN      : 1;
    volatile uint32_t SMBHEN    : 1;
    volatile uint32_t SMBDEN    : 1;
    volatile uint32_t ALERTEN   : 1;
    volatile uint32_t PECEN     : 1;
    volatile uint32_t Res2      : 1;
    volatile uint32_t Res3      : 1;
    volatile uint32_t Res4      : 1;
    volatile uint32_t Res5      : 1;
    volatile uint32_t Res6      : 1;
    volatile uint32_t Res7      : 1;
    volatile uint32_t Res8      : 1;
    volatile uint32_t Res9      : 1;
} I2CCR1;

typedef struct _I2CCR2 {
    volatile uint32_t SADD      : 10;
    volatile uint32_t RD_WRN    : 1;
    volatile uint32_t ADD10     : 1;
    volatile uint32_t HEAD10R   : 1;
    volatile uint32_t START     : 1;
    volatile uint32_t STOP      : 1;
    volatile uint32_t NACK      : 1;
    volatile uint32_t NBYTES    : 8;
    volatile uint32_t RELOAD    : 1;
    volatile uint32_t AUTOEND   : 1;
    volatile uint32_t PECBYTE   : 1;
    volatile uint32_t Res1      : 1;
    volatile uint32_t Res2      : 1;
    volatile uint32_t Res3      : 1;
    volatile uint32_t Res4      : 1;
    volatile uint32_t Res5      : 1;
} I2CCR2;

typedef struct _I2CTIMINGR {
    volatile uint32_t SCLL      : 8;
    volatile uint32_t SCLH      : 8;
    volatile uint32_t SDADEL    : 4;
    volatile uint32_t SCLDEL    : 4;
    volatile uint32_t Res1      : 1;
    volatile uint32_t Res2      : 1;
    volatile uint32_t Res3      : 1;
    volatile uint32_t Res4      : 1;
    volatile uint32_t PRESC     : 4;
} I2CTIMINGR;

typedef struct _I2CISR {
    volatile uint32_t TXE       : 1;
    volatile uint32_t TXIS      : 1;
    volatile uint32_t RXNE      : 1;
    volatile uint32_t ADDR      : 1;
    volatile uint32_t NACKF     : 1;
    volatile uint32_t STOPF     : 1;
    volatile uint32_t TC        : 1;
    volatile uint32_t TCR       : 1;
    volatile uint32_t BERR      : 1;
    volatile uint32_t ARLO      : 1;
    volatile uint32_t OVR       : 1;
    volatile uint32_t PECERR    : 1;
    volatile uint32_t TIMEOUT   : 1;
    volatile uint32_t ALERT     : 1;
    volatile uint32_t Res1      : 1;
    volatile uint32_t BUSY      : 1;
    volatile uint32_t DIR       : 1;
    volatile uint32_t ADDCODE   : 7;
    volatile uint32_t Res2      : 1;
    volatile uint32_t Res3      : 1;
    volatile uint32_t Res4      : 1;
    volatile uint32_t Res5      : 1;
    volatile uint32_t Res6      : 1;
    volatile uint32_t Res7      : 1;
    volatile uint32_t Res8      : 1;
    volatile uint32_t Res9      : 1;
} I2CISR;

typedef struct _I2CTXDR {
    volatile uint32_t TXDATA    : 8;
    volatile uint32_t Res1      : 1;
    volatile uint32_t Res2      : 1;
    volatile uint32_t Res3      : 1;
    volatile uint32_t Res4      : 1;
    volatile uint32_t Res5      : 1;
    volatile uint32_t Res6      : 1;
    volatile uint32_t Res7      : 1;
    volatile uint32_t Res8      : 1;
    volatile uint32_t Res9      : 1;
    volatile uint32_t Res10     : 1;
    volatile uint32_t Res11     : 1;
    volatile uint32_t Res12     : 1;
    volatile uint32_t Res13     : 1;
    volatile uint32_t Res14     : 1;
    volatile uint32_t Res15     : 1;
    volatile uint32_t Res16     : 1;
    volatile uint32_t Res17     : 1;
    volatile uint32_t Res18     : 1;
    volatile uint32_t Res19     : 1;
    volatile uint32_t Res20     : 1;
    volatile uint32_t Res21     : 1;
    volatile uint32_t Res22     : 1;
    volatile uint32_t Res23     : 1;
    volatile uint32_t Res24     : 1;
} I2CTXDR;

typedef struct _I2CRXDR {
    volatile uint8_t  RXDATA    : 8;
    volatile uint32_t Res1      : 1;
    volatile uint32_t Res2      : 1;
    volatile uint32_t Res3      : 1;
    volatile uint32_t Res4      : 1;
    volatile uint32_t Res5      : 1;
    volatile uint32_t Res6      : 1;
    volatile uint32_t Res7      : 1;
    volatile uint32_t Res8      : 1;
    volatile uint32_t Res9      : 1;
    volatile uint32_t Res10     : 1;
    volatile uint32_t Res11     : 1;
    volatile uint32_t Res12     : 1;
    volatile uint32_t Res13     : 1;
    volatile uint32_t Res14     : 1;
    volatile uint32_t Res15     : 1;
    volatile uint32_t Res16     : 1;
    volatile uint32_t Res17     : 1;
    volatile uint32_t Res18     : 1;
    volatile uint32_t Res19     : 1;
    volatile uint32_t Res20     : 1;
    volatile uint32_t Res21     : 1;
    volatile uint32_t Res22     : 1;
    volatile uint32_t Res23     : 1;
    volatile uint32_t Res24     : 1;
} I2CRXDR;

#define I2C_CR1      ((I2CCR1 *) 0x40005400)
#define I2C_CR2      ((I2CCR2 *) 0x40005404)
#define I2C_TIMINGR  ((I2CTIMINGR *) 0x40005410)
#define I2C_ISR      ((I2CISR *) 0x40005418)
#define I2C_TXDR     ((I2CTXDR *) 0x40005428)
#define I2C_RXDR     ((I2CRXDR *) 0x40005424)


uint32_t string_len(const uint8_t *str);
uint32_t power(uint16_t base, uint16_t exponent);
void set_nbytes(uint32_t size);
void get_nbytes(uint8_t *data);
uint32_t hex_to_decimal(uint8_t *data);
void get_data(uint8_t *text, uint32_t totalLength);
void i2c_init(void);
void i2c_write_byte (const uint8_t data);
void i2c_write(const uint8_t *data);
void i2c_read_string(void);

#endif