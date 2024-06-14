#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"

#define PinDHT 4          // Pin yang terhubung ke data DHT11
#define DHTTYPE DHT11     // Tentukan jenis sensor DHT

const char* ssid = "Punya Biyu";
const char* password = "DuaRibu15";
const char* serverName = "http://127.0.0.1:5000/data";

DHT dht(PinDHT, DHTTYPE);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  dht.begin();
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    float h = dht.readHumidity();//membaca kelembapan
    float t = dht.readTemperature();//untuk membaca suhu

    if (isnan(h) || isnan(t)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    // Menyiapkan data JSON
    String postData = "{\"temperature\":";
    postData += String(t);
    postData += ", \"humidity\":";
    postData += String(h);
    postData += "}";

    http.begin(serverName);
    http.addHeader("Content-Type", "application/json");

    
    int httpResponseCode = http.POST(postData);//mulai perintah untuk mengirim data ke server

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();
  }

  
  delay(5000);  // ini perintah untuk menunggu selama 5 detik sebelum mengirim data lagi
}
