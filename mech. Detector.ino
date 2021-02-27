#include<LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);  // configure the pin RS,enable,D4,D5,D6,D7  resp.


int sensorPin=9;
int ledPin=11;
int sensorValue;                              
int count=0;
int flag=0;


void setup() 
{
Serial.begin(9600);     

lcd.begin(16,2);          // initialize LCD of size 16/2 (2 rows, 16 col)
lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  
lcd.clear();               //clear the screen
lcd.print("Initilization .....");  //displaying the message on LCD
delay(500);

lcd.clear(); 
lcd.begin(16,2);          // initialize LCD of size 16/2 (2 rows, 16 col)
lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  

lcd.print("Mrunal Wagh .....");  //displaying the message on LCD
delay(500);

lcd.clear(); 
lcd.begin(16,2);          // initialize LCD of size 16/2 (2 rows, 16 col)
lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  
lcd.print("Ready .....");  //displaying the message on LCD

delay(500); 

                   
pinMode(sensorPin, INPUT); 
pinMode(ledPin, OUTPUT);          
}

void loop() 
{
sensorValue= digitalRead(sensorPin);            


if(sensorValue==0 && flag==0)
     {      
    Serial.println("\n am in if ...................................");
                                              
    Serial.println("Motion is detected");
    Serial.print("Sensorvalue is:");                         
    Serial.println(sensorValue);
    count ++;
    digitalWrite(ledPin,HIGH);
    delay(500);
    digitalWrite(ledPin,LOW);

    flag=1;
    showCountOnLCD(count);
    delay(500); 
     }
else if( sensorValue==0)
     {  
    Serial.println("\n signal is high but dont take action ");
     }

   else
   {
      Serial.println("Motion is not detected");
        Serial.print("Sensorvalue is:");                         
      Serial.println(sensorValue);
      flag=0;
    delay(500); 
     }
}

//----------------------------end of loop


void showCountOnLCD(int strCount)
{
  lcd.clear();               //clear the screen
  lcd.begin(16,2);          // initialize LCD of size 16/2 (2 rows, 16 col)
  lcd.setCursor(1,0);       // set the cursor at position (C1,R0)  
   lcd.print("Count:");//displaying the message on LCD
   lcd.setCursor(8,0);       // set the cursor at position (C1,R0)  
  lcd.print(strCount);//displaying the message on LCD
}

