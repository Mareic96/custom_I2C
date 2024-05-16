//Arduino Uno example code acting as target for I2C communication
#include <Wire.h>
#include <stdint.h>

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

// function that executes whenever data is received from master
void receiveEvent(int howMany) {
 while (0 <Wire.available()) {
    char c = Wire.read();      /* receive byte as a character */
    Serial.print(c);           /* print the character */
  }
 Serial.println();             /* to newline */
}

// function that executes whenever data is requested from master
void requestEvent() {
  //Target should send me a number of bytes to the controller
  //Get the length of the string -> convert the number into hex -> save the hex values into an array of size 4 -> send the hex four times to stm32;
  static uint16_t check = 0;

  uint8_t *sometext = "Dream of Californication!";
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
    Wire.write((const uint8_t *)sometext, len);
  }

}