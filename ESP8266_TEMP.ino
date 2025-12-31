#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DHT.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

#define DHTPIN 5      // Pin D1 on NodeMCU is GPIO 5
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);

void handleRoot() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    server.send(200, "text/plain", "Failed to read from DHT sensor!");
    return;
  }

  String html = "<!DOCTYPE html><html><head><meta http-equiv='refresh' content='5'>";
  html += "<style>body{font-family: sans-serif; text-align: center; margin-top: 50px;} h1{color: #333;} .data{font-size: 2em; color: #0275d8;}</style></head>";
  html += "<body><h1>ESP8266 Weather Station</h1>";
  html += "<p>Temperature: <span class='data'>" + String(t) + " &deg;C</span></p>";
  html += "<p>Humidity: <span class='data'>" + String(h) + " %</span></p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
