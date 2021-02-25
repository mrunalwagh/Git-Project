#include <SoftwareSerial.h>

SoftwareSerial mySerial(53,52);

void setup()
{
  mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(100);
  Serial.println("GSM initialized.");
  Serial.println("Waiting for messages");
}


void loop()
{

 SendMessage();
 delay(10000);
  
  if (Serial.available()>0)
   switch(Serial.read())
  {
    case 's':
      SendMessage();
      break;
    case 'r':
      RecieveMessage();
      break;
   case 'a':
      RecieveMessageAll();
      break;
  }

 if (mySerial.available()>0)
   Serial.write(mySerial.read());
}


 void SendMessage()
{
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  Serial.println("\n am sending msg ");
  mySerial.println("AT+CMGS=\"+910000000000\"\r"); // Replace x with mobile number
  Serial.println("\n msg sended sucessfully ");
  delay(1000);
  mySerial.println("I am SMS from GSM Module");// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
}


 void RecieveMessage()
{
  mySerial.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
  Serial.println("msg received sucessfully");
  delay(1000);
 }
 void RecieveMessageAll()
{
  mySerial.println("AT+CMGL=\”ALL\”\r"); // AT Command to receive a live SMS
  Serial.println("All msg received sucessfully");
  delay(1000);
 }
 