#include <Wire.h>
#include <stdint.h>

typedef struct leds {
  uint8_t state;
  uint16_t pins[3];
} LED;

void num_to_char(uint32_t *data, uint8_t *nbytes) {
  uint16_t i = 0;
  while(i < 8) {
    uint32_t conversion = (*data & 0xF);
    if(conversion < 10) {
      nbytes[i] = conversion + '0';
    } else {
      nbytes[i] = conversion + 'A' - 10;
    }
    *data = *data >> 4;
    i++;
  }
  nbytes[8] = '\0';
}

void setup() {
 Wire.begin(8);                /* join i2c bus with address 8 */
 Wire.onReceive(receiveEvent); /* register receive event */
 Wire.onRequest(requestEvent); /* register request event */
 Serial.begin(115200);           /* start serial comm. */
 Serial.println("I am I2C Slave");
}

void loop() {
 delay(100);
}

void read_string(uint8_t *data, uint8_t length) {
  //data++;
  Serial.print("Printing data: ");
  uint8_t i = 0;
  while(i < length) {
    Serial.print((char)data[i]);
    i++;
  }             /* to newline */
  Serial.println();
}

void read_led(void) {
  uint8_t *request[4];
  uint8_t i = 0;
  while (0 < Wire.available()) {
    request[i] = Wire.read();
    Serial.print((uint8_t)request[i]);
    Serial.print(" ");
    i++;
  }
  Serial.println();
  LED *leds = (LED *)request;
  Serial.print("State = ");
  Serial.print(leds -> state);
  Serial.print("pins[0] = ");
  Serial.print(leds -> pins[0]);
  Serial.print("pins[1] = ");
  Serial.print(leds -> pins[1]);
  Serial.print("pins[2] = ");
  Serial.print(leds -> pins[2]);
  Serial.println();
}//Not ready, it's a prototype

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
  uint8_t data[50];
  static uint8_t type;
  static uint8_t check = 0;

  if(!check) {
    Serial.println("Received event for the first time");
    while(Wire.available()) {
      type = Wire.read(); 
    }
    Serial.print("Received type: ");
    Serial.print((char) type);
    check++;
  } else {
    check = 0;
  }

  if(!check) {
    uint8_t length = 0;
    while(Wire.available()) {
      data[length] = Wire.read();
      length++;
    }

    switch(type) {
      case ('s'):
        Serial.println(", reading string");
        read_string(data, length);
        break;
      case ('b'):
        Serial.println(", reading one byte");
        read_string(data, length);
        break;
      case ('l'):
        Serial.println(": reading struct");
        break;
      default:
        Serial.println(": Unrecognised type");
    }
  }
}

// function that executes whenever data is requested from master
void requestEvent() {
  //Target should send me a number of bytes to the controller
  //Get the length of the string -> convert the number into hex -> save the hex values into an array of size 4 -> send the hex four times to stm32;
  static uint16_t check = 0;

  uint8_t *sometext = "Hello STM32!";
  uint32_t len = strlen(sometext);

  if(!check) {
    uint8_t nbytes[9];
    num_to_char(&len, nbytes);

    len = strlen(sometext);
    uint8_t *temp = nbytes;
    
    while(*temp != '\0') {
      Wire.write(*temp);
      temp++;
    }
    check++;
  } else {
    check = 0;
  }

  Serial.println(check);
  if(!check) {
    Serial.println("Inside second if statement");
    Wire.write((const uint8_t *)sometext, len);
  }

}
