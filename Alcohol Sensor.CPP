   #include <LiquidCrystal.h>
   #include <SoftwareSerial.h>
   SoftwareSerial msgSerial(10,5); //rx,tx  //IC -16,11
   LiquidCrystal lcd(11, 12, 2, 3, 4, 7);  //IC-13(ARDI-7)
   #define buzzerPin 8
   #define MOTORPin 6
   #define gasPin A0
   void setup()
   {
   Serial.begin(9600);
   lcd.begin(16, 2); 
   msgSerial.begin(9600);
   pinMode(buzzerPin,OUTPUT);
   pinMode(MOTORPin,OUTPUT);
   lcd.setCursor(0, 0);
   lcd.print("Calibrating");
   for(int i = 0; i <10; i++){
      if (i==4)
        {
         lcd.setCursor(0, 1);
         lcd.print(".");
        }
       else  lcd.print(".");
      delay(500);
        }
    lcd.setCursor(5, 1);
    lcd.print("done");
    delay(1000);
    lcd.clear(); 
    lcd.setCursor(1, 0);
    lcd.print("SENSOR ACTIVE");
    delay(1500);
    lcd.clear();
   }
   void loop() 
   {
   int gasSensor = analogRead(gasPin);
   if (gasSensor < 500)
   {
     digitalWrite(buzzerPin,LOW);
     digitalWrite(MOTORPin,HIGH);
     lcd.setCursor(0, 0);
     lcd.print("Value: ");
     lcd.print(gasSensor);
     Serial.print(gasSensor);
     Serial.print("\t");
     lcd.setCursor(0, 1);
     Serial.println("Alcohol NOT Detected");   
     lcd.print("Engine ON");  
     delay(1000); 
     lcd.clear();
      }
    else  //greater that 800 
      {
     digitalWrite(buzzerPin,HIGH);
     digitalWrite(MOTORPin,LOW);
     lcd.setCursor(0, 0);
     lcd.print("Value : ");
     Serial.println("Value : ");
     lcd.print(gasSensor);
     Serial.print(gasSensor);
     Serial.print("\t");
     lcd.setCursor(0, 1);
     Serial.println("Alcohol Detected"); 
     lcd.print("Alcohol Detected");   
     delay(300);
     funDoGSMCall();
      
    }
  
    } 
  
void funDoGSMCall()
{


  Serial.println("\n am doing call");
  msgSerial.println("ATD+919518714326;");        // ATDxxxxxxxxxx; -- watch out here for semicolon at the end!!
  delay(20000);
  Serial.println("\n call done");  

}