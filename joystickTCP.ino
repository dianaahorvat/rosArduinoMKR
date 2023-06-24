#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

// Destination IP address and port number
IPAddress serverIP(192, 168, 100, 30);
int serverPort = 8080; 

// TCP client instance
WiFiClient client;

// Joystick pin definitions
const int joystickXPin = A5;
const int joystickYPin = A6;

void setup() {
  pinMode(joystickXPin, INPUT);
  pinMode(joystickYPin, INPUT);

  Serial.begin(9600);                                                                       
  
   //Connect to Wi-Fi network
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);
    delay(5000);
  }

  Serial.println("Connected to Wi-Fi");

  // Connect to TCP server
  while (!client.connect(serverIP, serverPort)) {
    Serial.println("Could not connect to server");
    delay(5000);
  }

  Serial.println("Connected to server");
}

void loop() {
  int xValue = analogRead(joystickXPin);
  int yValue = analogRead(joystickYPin);

  String dataString = String(xValue) + "," + String(yValue);

  // Send TCP packet to server
  client.print(dataString);

  delay(500);
}
