#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/* -------- WiFi Credentials -------- */
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

/* -------- Pin Definition -------- */
#define LED_PIN D1   // GPIO5

/* -------- Web Server -------- */
ESP8266WebServer server(80);

/* -------- LED State -------- */
bool ledState = false;

/* -------- Web Page -------- */
void handleRoot() {
  String page = "<html><body style='text-align:center;'>";
  page += "<h1>ESP8266 LED TOGGLE</h1>";

  if (ledState)
    page += "<p>LED is ON</p>";
  else
    page += "<p>LED is OFF</p>";

  page += "<a href='/toggle'><button style='font-size:30px;'>TOGGLE</button></a>";
  page += "</body></html>";

  server.send(200, "text/html", page);
}

/* -------- Toggle Function -------- */
void handleToggle() {
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState ? HIGH : LOW);
  server.sendHeader("Location", "/");
  server.send(303);
}

/* -------- Setup -------- */
void setup() {
  Serial.begin(9600);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  WiFi.begin(ssid, password);
  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  server.begin();
}

/* -------- Loop -------- */
void loop() {
  server.handleClient();
}
