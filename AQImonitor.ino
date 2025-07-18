#include <U8g2lib.h>
#include <Wire.h>
#include <DHT.h>
#include <WiFi.h>
#define BLYNK_TEMPLATE_ID "TMPL3b8-yGfEE"
#define BLYNK_TEMPLATE_NAME "Air Quality Monitoring"
#define BLYNK_AUTH_TOKEN "MIT-5c_0mI2y-Z5b6JEhudlxiboCju8y"
#include <BlynkSimpleEsp32.h>

// ========== BLYNK CONFIGURATION ==========



// WiFi credentials
char ssid[] = "net ses";
char pass[] = "23456789";

// Blynk virtual pins
#define VPIN_TEMP V0
#define VPIN_HUM  V1
#define VPIN_AQI  V2

// ==========================================

// OLED setup (I2C)
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// DHT11 setup
#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// MQ138 setup
#define MQ138_PIN 34  // Analog input pin

void setup() {
  Serial.begin(115200);
  dht.begin();
  u8g2.begin();

  // OLED: initializing message
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tr);
  u8g2.drawStr(0, 20, "Initializing sensors...");
  u8g2.sendBuffer();
  delay(2000);

  // WiFi manual connection
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 20) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("\nWiFi connection failed!");

    // OLED: display WiFi failure
    u8g2.clearBuffer();
    u8g2.drawStr(0, 20, "WiFi connection");
    u8g2.drawStr(0, 36, "FAILED!");
    u8g2.drawStr(0, 52, "Retrying in 10s...");
    u8g2.sendBuffer();

    delay(10000); // wait before retry
    ESP.restart(); // reboot ESP32
  }

  Serial.println("\nWiFi connected.");
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();

  // Read sensor data
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int mq138_raw = analogRead(MQ138_PIN);
  float aqi = map(mq138_raw, 0, 4095, 0, 500); // Simulated AQI

  // Serial debug output
  Serial.print("Temp: "); Serial.print(temp);
  Serial.print(" C, Hum: "); Serial.print(hum);
  Serial.print(" %, AQI: "); Serial.println(aqi);

  // OLED Display
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_6x12_tr);

  char buffer[32];
  snprintf(buffer, sizeof(buffer), "Temp: %.1f C", temp);
  u8g2.drawStr(0, 16, buffer);

  snprintf(buffer, sizeof(buffer), "Humidity: %.1f %%", hum);
  u8g2.drawStr(0, 32, buffer);

  snprintf(buffer, sizeof(buffer), "AQI: %.0f (est)", aqi);
  u8g2.drawStr(0, 48, buffer);
  u8g2.sendBuffer();

  // Send data to Blynk
  Blynk.virtualWrite(VPIN_TEMP, temp);
  Blynk.virtualWrite(VPIN_HUM, hum);
  Blynk.virtualWrite(VPIN_AQI, aqi);

  delay(2000);
}
