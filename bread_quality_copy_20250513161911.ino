// Example testing sketch for various DHT humidity/temperature sensors
// Written by ladyada, public domain

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#include "MQ135.h"
#include <MQSensor.h>
// Sensor pin
#define pinA A0
#define MQ7_PIN A1
MQ135 sensorMQ = MQ135(pinA);
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));
  dht.begin();
  Serial.println("MQ7 CO Gas Sensor Reading");
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
   // reading the gas concentration in ppm into the variable
  float ppm = sensorMQ.getPPM();
  // reading time from Arduino start in seconds
  long time = millis() / 1000;
  // print the measured concentration
  Serial.print("Concentration of gases: ");
  Serial.print(ppm);
  Serial.print(" ppm | time since the launch of the Arduino: ");
  Serial.print(time / 60);  
  Serial.print("m");
  Serial.print(time % 60);  
  Serial.println("s.");

  delay(3000);
   int mq7Value = analogRead(MQ7_PIN);

  // Print the raw value from the sensor to the Serial Monitor
  Serial.print("MQ7 Sensor Raw Value: ");
  Serial.println(mq7Value);

  // For better readability, print a separator
  Serial.println("--------------------------");

  // Delay for 1 second before reading again
  delay(1000);

}
