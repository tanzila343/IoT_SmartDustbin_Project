#define BLYNK_TEMPLATE_ID "TMPL6Q7nCFIkO"
#define BLYNK_TEMPLATE_NAME "DustbinDistance"
#define BLYNK_AUTH_TOKEN "qRFdAHinF_fTxb6F0ZCCnUSFMnuMi173"
#define BLYNK_FIRMWARE_VERSION "0.1.0"
#define BLYNK_PRINT Serial
#define USE_NODE_MCU_BOARD

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

const char* ssid = "Nikomma WIFI"; // Your WiFi SSID
const char* password = "philocse422"; // Your WiFi password
char auth[] = BLYNK_AUTH_TOKEN;
const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;


void setup() {
  Serial.begin(9600);
  //Serial.print("Connecting.. ");
  Blynk.begin(auth, ssid, password);
  //Serial.print("Connected.. ");
}

void loop() {
  Blynk.run(); // Continuously process Blynk tasks
  
  if (Serial.available() > 0) {
    String distance = Serial.readStringUntil('\n'); // Read the string until a newline
    //Serial.print("Distance: ");
    Serial.println(distance);
    //Serial.println(" cm");
    int distanceInt = distance.toInt(); // Convert string to integer
    Blynk.virtualWrite(V0, distanceInt); // Send sensor value to Virtual Pin V0
  }

  delay(1000); // Delay a little bit to improve stability
}
