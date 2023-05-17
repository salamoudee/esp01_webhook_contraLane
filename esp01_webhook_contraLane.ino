#include <Servo.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <ESP8266Webhook.h>
#include <ESP8266WiFi.h>

#define _SSID ""      // Your WiFi SSID
#define _PASSWORD "12345"  // Your WiFi Password
#define KEY "bnl0hscGbTWW3VRcDRjQfd"        // Webhooks Key
#define EVENT1 "gate_open"      // Webhooks Event Name
#define pot A0
#define EVENT2 "gate_close"

Webhook webhook(KEY, EVENT1);    // Create an object.
Webhook webhook1(KEY, EVENT2);    // Create an object.

// Set the LCD address to 0x27 for a 16 chars and 2 line display
LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
//int ledPin = 12; // choose pin for the LED
int inputPin = 13; // choose input pin (for Infrared sensor) GPIO7
int val = 0; // variable for reading the pin status

long duration;
int distance;
int Num = 1234;
int potRead = 0;

void warning(){
  lcd.setCursor(0,0);
  lcd.print("WARNING: Contra Lane");
  
  //To print O
  lcd.setCursor(0, 1);
  lcd.write(255);
  lcd.setCursor(0, 2);
  lcd.write(255);
  lcd.setCursor(0, 3);
  lcd.write(255);
  lcd.setCursor(1, 1);
  lcd.write(255);
  lcd.setCursor(2, 1);
  lcd.write(255);
  lcd.setCursor(2, 2);
  lcd.write(255);
  lcd.setCursor(2, 3);
  lcd.write(255);
  lcd.setCursor(1, 3);
  lcd.write(255);

  //To print O
  lcd.setCursor(0+6, 1);
  lcd.write(255);
  lcd.setCursor(0+6, 2);
  lcd.write(255);
  lcd.setCursor(0+6, 3);
  lcd.write(255);
  lcd.setCursor(1+6, 1);
  lcd.write(255);
  lcd.setCursor(2+6, 1);
  lcd.write(255);
  lcd.setCursor(2+6, 2);
  lcd.write(255);
  lcd.setCursor(2+6, 3);
  lcd.write(255);
  lcd.setCursor(1+6, 3);
  lcd.write(255);

  //To print O
  lcd.setCursor(0+11, 1);
  lcd.write(255);
  lcd.setCursor(0+11, 2);
  lcd.write(255);
  lcd.setCursor(0+11, 3);
  lcd.write(255);
  lcd.setCursor(1+11, 1);
  lcd.write(255);
  lcd.setCursor(2+11, 1);
  lcd.write(255);
  lcd.setCursor(2+11, 2);
  lcd.write(255);
  lcd.setCursor(2+11, 3);
  lcd.write(255);
  lcd.setCursor(1+11, 3);
  lcd.write(255);

  //print X
  lcd.setCursor(19,1);
  lcd.write(255);
  lcd.setCursor(17,1);
  lcd.write(255);
  lcd.setCursor(18,2);
  lcd.write(255);
  lcd.setCursor(19,3);
  lcd.write(255);
  lcd.setCursor(17,3);
  lcd.write(255);
  }

void setup() {
  Serial.begin(9600); // Starts the serial communication
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(pot, INPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  
  // initialize the LCD
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  
  lcd.print("Connecting to: ");
  lcd.setCursor(0,1);
  lcd.print(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }
  lcd.setCursor(0,2);
  lcd.print("");
  lcd.print("WiFi Connected");
  delay(5000);
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);

//  // Trigger without any value and get response.
//  int response = webhook.trigger();
//  if(response == 200)
//    Serial.println("OK");
//  else
//    Serial.println("Failed");
  
  myservo.attach(14);  // attaches the servo on GIO5 to the servo object
  myservo.write(0);
  
  pinMode(inputPin, INPUT); // declare Infrared sensor as input
  pinMode(15, OUTPUT);
  // Turn on the blacklight and print a message.
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Smart Lane System");
  
  lcd.setCursor(0,2);
  lcd.print("Hariz Hafiz");
  lcd.setCursor(0,3);
  lcd.print("2020985097");
  delay(5000);
//  digitalWrite(15, HIGH);
//  delay(5000);
//  digitalWrite(15, LOW);
  

  

}

void loop() {
  int pos;
  delay(500);
  
  potRead = analogRead(pot);
  Serial.println(potRead);
  delay(1000);
  
  val = digitalRead(inputPin); // read input value 
//   if (potRead >= 500 || val == 1)
   if (potRead >= 500)
   { // check if the input is HIGH
      lcd.clear();
      delay(20);
      warning();
      Serial.println("HIGH"); // turn LED OFF  
      digitalWrite(15,HIGH);
      int pos = 0;
      for(pos;pos<180;pos++){
          myservo.write(pos);
        delay(50);  
        }
      digitalWrite(15,LOW);
      
      lcd.clear();
      delay(20);
      lcd.print("Gate Open1");
      int response = webhook.trigger();
      if(response == 200)
        Serial.println("OK");
      else
        Serial.println("Failed");
      delay(5000);
      lcd.clear();
      delay(20);
      
      lcd.print("Gate Open2");
      response = webhook.trigger();
      if(response == 200)
        Serial.println("OK");
      else
        Serial.println("Failed");
      delay(5000);

      delay(20);  

      lcd.clear();
      lcd.print("Gate Open3");
      response = webhook.trigger();
      if(response == 200)
        Serial.println("OK");
      else
        Serial.println("Failed");
      
      delay(5000);

      //Gate closing
      digitalWrite(15,HIGH);
      for(pos;pos>0;pos--){
          myservo.write(pos);
        delay(50);  
        }
      digitalWrite(15,LOW);
      int response1 = webhook1.trigger();
      if(response1 == 200)
        Serial.println("OK");
      else
        Serial.println("Failed");
      delay(3000);
      
      response1 = webhook1.trigger();
      if(response1 == 200)
        Serial.println("OK");
      else
        Serial.println("Failed");
      delay(3000);

      response1 = webhook1.trigger();
      if(response1 == 200)
        Serial.println("OK");
      else
        Serial.println("Failed");
      delay(3000);
   } 
   else if (potRead < 500){
    Serial.println("LOW");
    lcd.clear();
    lcd.print("Gate Closed");
    myservo.write(0);
    delay(5000);
    }
  
}
