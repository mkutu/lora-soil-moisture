#include <Wire.h>
#include <SPI.h>
#include <RH_RF95.h>
#include <SoftwareSerial.h>

// Pin definitions
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

// LoRa Frequency
#define RF95_FREQ 915.0 // Change to 868.0 if using the 868 MHz band

// LoRa radio
RH_RF95 rf95(RFM95_CS, RFM95_INT);

// Sensor pin
#define SENSOR_PIN A0

// SoftwareSerial for UART communication with the Plant Monitor
SoftwareSerial plantMonitorSerial(0, 1); // RX, TX

// Unique identifier for each sensor
const uint8_t sensorID = 1; // Change this ID for each sensor

void setup() {
  Serial.begin(115200);
  while (!Serial);

  // Initialize SoftwareSerial
  plantMonitorSerial.begin(9600);

  // Initialize LoRa module
  pinMode(RFM95_RST, OUTPUT);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);
  digitalWrite(RFM95_RST, LOW);
  delay(10);
  digitalWrite(RFM95_RST, HIGH);
  delay(10);

  if (!rf95.init()) {
    Serial.println("LoRa radio init failed");
    while (1);
  }
  Serial.println("LoRa radio init OK!");

  if (!rf95.setFrequency(RF95_FREQ)) {
    Serial.println("setFrequency failed");
    while (1);
  }
  Serial.print("Set Freq to: "); Serial.println(RF95_FREQ);
}

void loop() {
  // Read soil moisture level
  int moisture = analogRead(SENSOR_PIN);
  Serial.print("Soil Moisture: "); Serial.println(moisture);

  // Read temperature and humidity from Plant Monitor
  if (plantMonitorSerial.available()) {
    String data = plantMonitorSerial.readStringUntil('\n');
    Serial.print("Received: "); Serial.println(data);

    // Parse the data if format is known (assuming comma-separated values)
    int commaIndex1 = data.indexOf(',');
    int commaIndex2 = data.lastIndexOf(',');

    if (commaIndex1 != -1 && commaIndex2 != -1 && commaIndex1 != commaIndex2) {
      int temperature = data.substring(0, commaIndex1).toInt();
      int humidity = data.substring(commaIndex1 + 1, commaIndex2).toInt();

      Serial.print("Temperature: "); Serial.println(temperature);
      Serial.print("Humidity: "); Serial.println(humidity);

      // Prepare data to send
      uint8_t payload[7];
      payload[0] = sensorID; // Add sensor ID to the payload
      payload[1] = (moisture >> 8) & 0xFF;
      payload[2] = moisture & 0xFF;
      payload[3] = (temperature >> 8) & 0xFF;
      payload[4] = temperature & 0xFF;
      payload[5] = (humidity >> 8) & 0xFF;
      payload[6] = humidity & 0xFF;

      rf95.send(payload, sizeof(payload));
      rf95.waitPacketSent();
      Serial.println("Data sent!");
    }
  }

  delay(5000); // Wait for 5 seconds before reading again
}
