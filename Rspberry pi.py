/*  
 *  GPRS+GPS Quadband Module (SIM908)
 *  
 *  Copyright (C) Libelium Comunicaciones Distribuidas S.L. 
 *  http://www.libelium.com 
 *  
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 3 of the License, or 
 *  (at your option) any later version. 
 *  a
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see http://www.gnu.org/licenses/. 
 *  
 *  Version:           1.0
 *  Design:            David Gascón 
 *  Implementation:    Marcos Martínez
 */

//Include arduPi library
#include "arduPi.h"

int8_t sendATcommand(const char* ATcommand, const char* expected_answer, unsigned int timeout);
void power_on();
 

//Enter here you data
const char pin_number[] = "****";         // Write the pin number of the SIM card
const char phone_numberA[] = "*********"; // Write here the number A to call
const char phone_numberB[] = "*********"; // Write here the number B to call
const char phone_numberC[] = "*********"; // Write here the number C to call

//Digital pin definitions
int onModulePin = 2; 
int buttonA = 3;
int buttonB = 4;
int buttonC = 5;
int endbutton = 6;

int8_t answer;
char aux_string[30];


void setup() {
  pinMode(onModulePin, OUTPUT);
  pinMode(buttonA, INPUT);
  pinMode(buttonB, INPUT);
  pinMode(buttonC, INPUT);
  pinMode(endbutton, INPUT);
  Serial.begin(115200);

  printf("Starting...\n");
  power_on(); // Powering the module

  delay(3000);

  //sets the PIN code
  sprintf(aux_string, "AT+CPIN=%s", pin_number);
  sendATcommand(aux_string, "OK", 2000);

  delay(3000);

  printf("Connecting to the network...\n");
  
  //Check network registration
  while ( (sendATcommand("AT+CREG?", "+CREG: 0,1", 1000) ||
           sendATcommand("AT+CREG?", "+CREG: 0,5", 1000)) == 0 );

  printf("Connected to the network!!\n");
  delay(1000);
  
  printf("Press a button to call\n");
}

void loop() {
  //If button A is pressed call to number A
  if (digitalRead(buttonA) == 1) {
    sprintf(aux_string, "ATD%s;", phone_numberA); 
    sendATcommand(aux_string, "OK", 10000);
    delay(100);
  }
  //If button B is pressed call to number B
  if (digitalRead(buttonB) == 1) {
    sprintf(aux_string, "ATD%s;", phone_numberB);
    sendATcommand(aux_string, "OK", 10000);
    delay(100);
  }
  //If button C is pressed call to number C
  if (digitalRead(buttonC) == 1) {
    sprintf(aux_string, "ATD%s;", phone_numberC); //calls to number C
    sendATcommand(aux_string, "OK", 10000);
    delay(100);
  }

  //If endbutton is pressed disconnects the existing call
  if (digitalRead(endbutton) == 1) {
    Serial.println("ATH");   
    printf("Call disconnected\n");
    delay(500);
  }
}


/************************************************************************
 ****               Definition of functions                          ****
 ************************************************************************/

void power_on() {
  uint8_t answer = 0;

  // checks if the module is started
  answer = sendATcommand("AT", "OK", 2000);
  if (answer == 0)
  {
    // power on pulse
    digitalWrite(onModulePin, HIGH);
    delay(3000);
    digitalWrite(onModulePin, LOW);

    // waits for an answer from the module
    while (answer == 0) {   // Send AT every two seconds and wait for the answer
      answer = sendATcommand("AT", "OK", 2000);
    }
  }

}

int8_t sendATcommand(const char* ATcommand, const char* expected_answer, unsigned int timeout){

    uint8_t x=0,  answer=0;
    char response[100];
    unsigned long previous;

    memset(response, '\0', 100);    // Initialize the string

    delay(100);

    while( Serial.available() > 0) Serial.read();    // Clean the input buffer

    Serial.println(ATcommand);    // Send the AT command 


        x = 0;
    previous = millis();

    // this loop waits for the answer
    do{
        if(Serial.available() != 0){    
            // if there are data in the UART input buffer, reads it and checks for the asnwer
            response[x] = Serial.read();
            printf("%c",response[x]);
            x++;
            // check if the desired answer  is in the response of the module
            if (strstr(response, expected_answer) != NULL)    
            {
				printf("\n");
                answer = 1;
            }
        }
    }
    // Waits for the asnwer with time out
    while((answer == 0) && ((millis() - previous) < timeout));    

        return answer;
}

int main (){
    setup();
    while(1){
        loop();
    }
    return (0);
}