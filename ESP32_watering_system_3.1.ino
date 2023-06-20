#include <WiFi.h>
#include <PulseSensorPlayground.h>

// WiFi credentials
const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

// Access point IP configuration
IPAddress apIP(192, 168, 1, 1);      // IP address of the access point
IPAddress netMsk(255, 255, 255, 0);  // Subnet mask
const IPAddress gateway(192, 168, 1, 1);
const IPAddress dns(192, 168, 1, 1);

WiFiServer server(80);  // Create a server object

// Pin definitions
const int solenoidPin = 26;         // Pin connected to the solenoid valve
const int moistureSensor1Pin = 34;  // Pin connected to the first soil moisture sensor
const int moistureSensor2Pin = 35;  // Pin connected to the second soil moisture sensor
const int moistureSensor3Pin = 36;  // Pin connected to the third soil moisture sensor
const int waterFlowSensor1Pin = 4; // Pin connected to the first water flow sensor
const int waterFlowSensor2Pin = 5; // Pin connected to the second water flow sensor
const int waterFlowSensor3Pin = 6; //Pin connect5ed to the third water flow sensor
const int waterFlowSensor4Pin = 7; //Pin connected to the forth water flow sensor
const int waterFlowSensor5Pin = 8; // Pin connected to the fifth water flow sensor
const int waterFlowSensor6Pin = 9; // Pin connected to the sixth water flow sensor
void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Start WiFi in access point mode
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, gateway, netMsk);
  WiFi.softAP(ssid, password);

  Serial.print("Access Point SSID: ");
  Serial.println(ssid);
  Serial.print("' Access Point Password: ");
  Serial.println(password);

  // Get the IP address of the access point
  IPAddress APIP = WiFi.softAPIP();
  Serial.print("Access Point IP address: ");
  Serial.println(APIP);

  server.begin();

  // Set pin modes
  pinMode(solenoidPin, OUTPUT);
  pinMode(moistureSensor1Pin, INPUT);
  pinMode(moistureSensor2Pin, INPUT);
  pinMode(moistureSensor3Pin, INPUT);
  pinMode(waterFlowSensor1Pin, INPUT);
  pinMode(waterFlowSensor2Pin, INPUT);
  pinMode(waterFlowSensor3Pin, INPUT);
  pinMode(waterFlowSensor4Pin, INPUT);
  pinMode(waterFlowSensor5Pin, INPUT);
  pinMode(waterFlowSensor6Pin, INPUT);

  PulseSensorPlayground waterFlowSensor1;
PulseSensorPlayground waterFlowSensor2;
PulseSensorPlayground waterFlowSensor3;
PulseSensorPlayground waterFlowSensor4;
PulseSensorPlayground waterFlowSensor5;
PulseSensorPlayground waterFlowSensor6;

waterFlowSensor1.setPin(waterFlowSensor1Pin);
waterFlowSensor2.setPin(waterFlowSensor2Pin);
waterFlowSensor3.setPin(waterFlowSensor3Pin);
waterFlowSensor4.setPin(waterFlowSensor4Pin);
waterFlowSensor5.setPin(waterFlowSensor5Pin);
waterFlowSensor6.setPin(waterFlowSensor6Pin);

}

void loop() {
  // Listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New Client connected.");
    String currentLine = "";

    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);

        if (c == '\n') {
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();

            // Send the HTML response
            client.println("<html>");
            client.println("<head><title>ESP32 Access Point</title></head>");
            client.println("<body>");
            client.println("<h1>Welcome to ESP32 Access Point</h1>");
            client.println("<p>This is a sample web page served from ESP32 in access point mode.</p>");
            client.println("</body></html>");

            break;  // Exit the while loop
          }
          currentLine = "";
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }

    // Read soil moisture levels
    float moistureLevel1 = map(analogRead(moistureSensor1Pin), 0, 4095, 0, 100);  // Scale analog reading to the moisture percentage
    float moistureLevel2 = map(analogRead(moistureSensor2Pin), 0, 4095, 0, 100);
    float moistureLevel3 = map(analogRead(moistureSensor3Pin), 0, 4095, 0, 100);

    float waterFlow1 = waterFlowSensor1.getFlowRate();
float waterFlow2 = waterFlowSensor2.getFlowRate();
float waterFlow3 = waterFlowSensor3.getFlowRate();
float waterFlow4 = waterFlowSensor4.getFlowRate();
float waterFlow5 = waterFlowSensor5.getFlowRate();
float waterFlow6 = waterFlowSensor6.getFlowRate();

float waterVolume1 = waterFlowSensor1.getMilliLitres();
float waterVolume2 = waterFlowSensor2.getMilliLitres();
float waterVolume3 = waterFlowSensor3.getMilliLitres();
float waterVolume4 = waterFlowSensor4.getMilliLitres();
float waterVolume5 = waterFlowSensor5.getMilliLitres();
float waterVolume6 = waterFlowSensor6.getMilliLitres();

Serial.print("Water Flow 1: ");
Serial.print(waterFlow1);
Serial.print(" L/min, Volume: ");
Serial.print(waterVolume1);
Serial.println(" mL");

Serial.print("Water Flow 2: ");
Serial.print(waterFlow2);
Serial.print(" L/min, Volume: ");
Serial.print(waterVolume2);
Serial.println(" mL");

Serial.print("Water Flow 3: ");
Serial.print(waterFlow3);
Serial.print(" L/min, Volume: ");
Serial.print(waterVolume3);
Serial.println(" mL");

Serial.print("Water Flow 4: ");
Serial.print(waterFlow4);
Serial.print(" L/min, Volume: ");
Serial.print(w


    // Check moisture levels and control solenoid valve
    if (moistureLevel1 < 30 && moistureLevel2 < 40 && moistureLevel3 < 30) {
      digitalWrite(solenoidPin, HIGH);  // Turn on the solenoid valve
      Serial.println("Solenoid valve turned on.");
    } else {
      digitalWrite(solenoidPin, LOW);  // Turn off the solenoid valve
      Serial.println("Solenoid valve turned off.");
    }

    // Read water flow sensor values
    int waterFlowSensor1Value = digitalRead(waterFlowSensor4Pin);
    int waterFlowSensor2Value = digitalRead(waterFlowSensor5Pin);
    int waterFlowSensor3Value = digitalRead(waterFlowSensor6Pin);
    int waterFlowSensor4Value = digitalRead(waterFlowSensor7Pin);
    int waterFlowSensor5Value = digitalRead(waterFlowSensor8Pin);
    int waterFlowSensor6Value = digitalRead(waterFlowSensor9Pin);


    // Print water flow sensor values
    Serial.println("Water Flow Sensor Values:");
    Serial.print("Sensor 1: ");
    Serial.println(waterFlowSensor1Value);
    Serial.print("Sensor 2: ");
    Serial.println(waterFlowSensor2Value);
    Serial.print("Sensor 3: ");
    Serial.println(waterFlowSensor3Value);
    Serial.print("Sensor 4: ");
    Serial.println(waterFlowSensor4Value);
    Serial.print("Sensor 5: ");
    Serial.println(waterFlowSensor5Value);
    Serial.print("Sensor6: ");
    Serial.println(waterFlowSensor6Value);

    delay(5000);  // Wait for 5 seconds
  }

  client.stop();
  Serial.println("Client disconnected.");
}
