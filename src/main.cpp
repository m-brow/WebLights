#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include <sstream>
#include <vector>

ESP8266WiFiMulti WiFiMulti;
const char* ssid = ""; 			// Add your own network SSID
const char* password = ""; 		// Add your SSID password
const char* url = "http://weblight/state";
int state;

const int RedPin = D3;
const int BluePin = D4;
const int GreenPin = D2;
int brightness = 1023;
int red = 0;
int green = 0;
int blue = 0;
int fadeSpeed = 2;

void setup() {
  Serial.begin(9600);
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password);

  // Setup GPIO pins
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(RedPin, OUTPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);

  state = 0;  
}

// Fade to the new colour
void changeTo(int r, int g, int b) {

  while (r != red || g != green || b != blue) {
    if (r > red)
      red++;
    else if(r < red)
      red--;

    if (g > green)
      green++;
    else if(g < green)
      green--;

    if (b > blue)
      blue++;
    else if(b < blue)
      blue--;

    // Write new colours
    analogWrite(RedPin, red);
    analogWrite(GreenPin, green);
    analogWrite(BluePin, blue);  
    delay(fadeSpeed);
  }
}

void loop() {

  std::vector<String> payload_parts;
  int next_red;
  int next_green;
  int next_blue;

  // Get data from /state
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    WiFiClient client;
    HTTPClient http;

    Serial.println("[HTTP] begin...\n");
    if (http.begin(client, url)) {
      
      Serial.println("[HTTP] Get...\n");
      int httpCode = http.GET();

      if (httpCode > 0) {
        // Successful GET request
        // Find the light state
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);

          payload_parts.clear();
          // manually split the string into its components
          unsigned int i, prev = 0;
          for (i = 0; i < payload.length(); i++) {
            if (payload.charAt(i) == '&') {
              // Print out the values

              payload_parts.push_back(payload.substring(prev, i));
              prev = i + 1;
            }
          }

          next_red = payload_parts.at(0).toInt();
          next_green = payload_parts.at(1).toInt();
          next_blue = payload_parts.at(2).toInt();

          changeTo(next_red, next_green, next_blue);

          Serial.printf("Red: %d, Green: %d, Blue: %d\n", next_red, next_green, next_blue);

          if (next_red > 0 && next_green > 0 && next_blue > 0) {
            digitalWrite(LED_BUILTIN, HIGH);
          }
          else{
            digitalWrite(LED_BUILTIN, LOW);
          }

        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP] Unable to connect\n");
    }

  }
  
  // Wait a second between each ping
  delay(1000);

}