//#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiSetup.h>
#include "vars.h"

// Create WiFiSetup object
WiFiSetup wifiSetup("SuperFanMan", "fanman123", 80);

// Global variable to store current fan speed
int currentFanSpeed;

// Send main fan control page
void showFanControls() {
  wifiSetup.server.send(200, "text/html", fanControlPage);
}

// Set fan speed to zero
void off() {
  // Turn fan off or to zero percent
  currentFanSpeed = FAN_SPEED_OFF;
  showFanControls();
}

// Set fan speed to fifty percent we start at 50 percent because 25% isn't enough to even turn the fan
void low() {
  // Set fan to fifty percent
  currentFanSpeed = FAN_SPEED_LOW;
  showFanControls();

  Serial.println("Fan Low");
}

// Set fan to seventy five percent
void medium() {
  // Set fan to seventy five percent
  currentFanSpeed = FAN_SPEED_MEDIUM;
  showFanControls();

  Serial.println("Fan Medium");
}

// Set fan to one hundred percent
void high() {
  // Set fan to full or one hundred percent
  currentFanSpeed = FAN_SPEED_HIGH;
  showFanControls();

  Serial.println("Fan High");
}

// Generate fan speed signal based on passed fanSpeed
void setFanTo(int fanSpeed) {
  switch (fanSpeed) {
    case FAN_SPEED_OFF:
      digitalWrite(PWM_PIN, LOW);
      break;
    case FAN_SPEED_LOW:
      digitalWrite(PWM_PIN, HIGH);
      delayMicroseconds(fanSpeed * 20);
      digitalWrite(PWM_PIN, LOW);
      delayMicroseconds(fanSpeed * 10);
      break;
    case FAN_SPEED_MEDIUM:
      digitalWrite(PWM_PIN, HIGH);
      delayMicroseconds(fanSpeed * 10);
      digitalWrite(PWM_PIN, LOW);
      delayMicroseconds((fanSpeed / 3) * 10);
      break;
    case FAN_SPEED_HIGH:
      digitalWrite(PWM_PIN, HIGH);
      break;
    default:
      Serial.println("Invalid fan speed.");
      break;
  }
}

void setup() {
  Serial.begin(115200);
  wifiSetup.setAppPage(fanControlPage);
  wifiSetup.begin();
  pinMode(PWM_PIN, OUTPUT);
  while (!Serial) {
    ;
  }

  // Set initial fan speed to zero
  currentFanSpeed = FAN_SPEED_OFF;

  // Serve main page
  wifiSetup.server.on("/off", off);
  wifiSetup.server.on("/low", low);
  wifiSetup.server.on("/medium", medium);
  wifiSetup.server.on("/high", high);

  // Print board's IP
  Serial.println(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  wifiSetup.handleClient();
  setFanTo(currentFanSpeed);
}