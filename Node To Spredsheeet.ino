

#include<ESP8266WiFi.h>
#include"HTTPSRedirect.h"
#include"DebugMacros.h"
#include<SoftwareSerial.h>

//------------------------
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


const long utcOffsetInSeconds = 19800;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
//------------------------


SoftwareSerial mton(D5,D6);
 p = "";
float h;
float t;
//String sheetHumid = "";
String sheetTem
String sheetRange="";
String sheetTimeStamp="";
//const char* ssid = "............";                //replace with our wifi ssid
//const char* password = .............";         //replace with your wifi password

const char* ssid = ".............";                //replace with our wifi ssid
const char* password = ".............";         //replace with your wifi password


const char* host = "script.google.com";
const char *GScriptId = ".........................................."; // Replaced with kmsanghvigrapes mail sheet  temp4 sheet id 
const int httpsPort = 443; 

// echo | openssl s_client -connect script.google.com:443 |& openssl x509 -fingerprint -noout
const char* fingerprint = "";

//const uint8_t fingerprint[20] = {};

String url = String("/macros/s/") + GScriptId + "/exec?value=Temperature";  // Write Teperature to Google Spreadsheet at cell A1
// Fetch Google Calendar events for 1 week ahead
String url2 = String("/macros/s/") + GScriptId + "/exec?cal";  // Write to Cell A continuosly

//replace with sheet name not with spreadsheet file name taken from google



String payload_base =  "{\"command\": \"appendRow\", \
                    \"sheet_name\": \"TempSheet\", \
                       \"values\": "; 
                       
                       
String payload = "";

HTTPSRedirect* client = nullptr;



int data;


void setup() {
  delay(1000);
 Serial.begin(9600);

  mton.begin(9600);
  //dht.begin();     //initialise DHT11

  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  // Use HTTPSRedirect class to create a new TLS connection
  client = new HTTPSRedirect(httpsPort);
  client->setInsecure();
  client->setPrintResponseBody(true);
  client->setContentTypeHeader("application/json");
  Serial.print("Connecting to ");
  Serial.println(host);          //try to connect with "script.google.com"

  // Try to connect for a maximum of 5 times then exit
  bool flag = false;
  for (int i = 0; i < 5; i++) {
    int retval = client->connect(host, httpsPort);
    if (retval == 1) {
      flag = true;
      break;
    }
    else
      Serial.println("Connection failed. Retrying...");
  }

  if (!flag) {
    Serial.print("Could not connect to server: ");
    Serial.println(host);
    Serial.println("Exiting...");
    return;
  }
// Finish setup() function in 1s since it will fire watchdog timer and will reset the chip.
//So avoid too many requests in setup()

  Serial.println("\nWrite into cell 'A1'");
  Serial.println("------>");
  // fetch spreadsheet data
  client->GET(url, host);
  
  Serial.println("\nGET: Fetch Google Calendar Data:");
  Serial.println("------>");
  // fetch spreadsheet data
  client->GET(url2, host);

 Serial.println("\nStart Sending Sensor Data to Google Spreadsheet");

  
  // delete HTTPSRedirect object
  delete client;
  client = nullptr;
  timeClient.begin();
}

void loop() {

 delay(10000);
 
 readDataFromMega();
                                //convert integer Range to string Range
 timeClient.update(); 
  static int error_count = 0;
  static int connect_count = 0;
  const unsigned int MAX_CONNECT = 20;
  static bool flag = false;
 payload = payload_base + "\"" + sheetTemp + "," + sheetRange+ "," + sheetTimeStamp + "\"}";
 //  payload = payload_base + "\"" + sheetTemp + "," + sheetRange + "\"}";
 
  if (!flag) {
    client = new HTTPSRedirect(httpsPort);
    client->setInsecure();
    flag = true;
    client->setPrintResponseBody(true);
    client->setContentTypeHeader("application/json");
  }

  if (client != nullptr) {
    if (!client->connected()) {
      client->connect(host, httpsPort);
      client->POST(url2, host, payload, false);
      Serial.print("Sent : ");  Serial.println("Temp and range");
    }
  }
  else {
    DPRINTLN("Error creating client object!");
    error_count = 5;
  }

  if (connect_count > MAX_CONNECT) {
    connect_count = 0;
    flag = false;
    delete client;
    return;
  }

  Serial.println("POST or SEND Sensor data to Google Spreadsheet:");
  if (client->POST(url2, host, payload)) {
    ;
  }
  else {
    ++error_count;
    DPRINT("Error-count while connecting: ");
    DPRINTLN(error_count);
  }

  if (error_count > 3) {
    Serial.println("Halting processor...");
    delete client;
    client = nullptr;
    Serial.printf("Final free heap: %u\n", ESP.getFreeHeap());
    Serial.printf("Final stack: %u\n", ESP.getFreeContStack());
    Serial.flush();
    ESP.deepSleep(0);
  }
  
  delay(3000);    // keep delay of minimum 2 seconds as dht allow reading after 2 seconds interval and also for google sheet
}

//-----------------------------------------------------------------------------


//---------------------------
void readDataFromMega()
 {

    Serial.println("\n am in  readDataFromMega");
       delay(1000);
     // mton.write("s");
      if (mton.available()>0)
      {
      
    String myString=mton.readString();
    Serial.println("\n am printing myString  data received from node ");
    Serial.println(myString);
   
   //----------------
     Serial.println("\n am doing spliting");
    // String myString=str;
   int commaIndex = myString.indexOf(',');
   int secondCommaIndex = myString.indexOf(',', commaIndex+1);
   int thirdCOmmaIndex=myString.indexOf(',', secondCommaIndex+1);
    sheetTemp=myString.substring(0, commaIndex);
    sheetRange=myString.substring(commaIndex+1,secondCommaIndex);
   sheetTimeStamp=myString.substring(secondCommaIndex+1,thirdCOmmaIndex);
    Serial.println(" Sheet Temp");
   Serial.println(sheetTemp);
   Serial.println("sheet Range");
   Serial.println(sheetRange);
    Serial.println("sheet TimeStamp");
   Serial.println(sheetTimeStamp);
delay(1000);
   
  
   
      }//end of if
 }

//---------------------------------------------------------------------------