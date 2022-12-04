#include <ESP8266WiFi.h>

const int trigPin = 12;
const int echoPin = 14;
const int b  = 2;
const int vibrator = 0;

const char* ssid = "Cench";
const char* password = "aaaaaaaa";
const char* host = "maker.ifttt.com";  

 
#define SOUND_VELOCITY 0.034 
long duration;
float distanceCm; 


void setup() {
  
  Serial.begin(9600);  
  pinMode(trigPin, OUTPUT);  
  pinMode(echoPin, INPUT); 
  pinMode (b, OUTPUT);
  pinMode(vibrator, OUTPUT);


  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    digitalWrite(b, HIGH);
    delay(1000);
    digitalWrite(b, LOW); 
    delay(3000);
  }
}



void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW); 
  duration = pulseIn(echoPin, HIGH);   
  distanceCm = duration * SOUND_VELOCITY/2;   
  Serial.print("Distance (cm): ");
  Serial.println(distanceCm);
  WiFiClient client ;
  const int httpPort = 80;
  if (!client.connect(host, httpPort )) {
    Serial.println("connection failed");
    delay(1000);
    return;
  } 
  if( distanceCm < 5){
    String url = "/trigger/BlindStick/with/key/oCuiEyMjY14rYHFOTIGdqjKctN7yCel-Z-JDZAXvtBA";
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                  "Host: " + host +  "\r\n" + 
                              "Connection: close\r\n\r\n");
  }
  if(distanceCm <30) {
    digitalWrite(vibrator, HIGH);
  } 
  if (distanceCm < 15) {
    digitalWrite(b, LOW);
  } else  {
    digitalWrite(vibrator, LOW);
    digitalWrite(b,HIGH);
  }  
  delay(1000);
}