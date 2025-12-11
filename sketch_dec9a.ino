// Required libraries:
// - DHT sensor library by Adafruit
// - LiquidCrystal_I2C (e.g., by Frank de Brabander or similar)
//
// Install via Library Manager: "DHT sensor library" and "LiquidCrystal I2C"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ====== User settings ======
#define DHTPIN 2        // digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11

// Change address here if your LCD uses 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

DHT dht(DHTPIN, DHTTYPE);

const unsigned long READ_INTERVAL = 2000; // read every 2 seconds
unsigned long lastRead = 0;

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Initialize the LCD
  lcd.init();          // initialize the I2C LCD
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DHT11 Monitor");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(1000);
  lcd.clear();
}

void loop() {
  unsigned long now = millis();
  if (now - lastRead >= READ_INTERVAL) {
    lastRead = now;
    readAndDisplay();
  }
}

// Read sensor and update LCD + Serial
void readAndDisplay() {
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();      // Celsius
  float tempF = dht.readTemperature(true);  // Fahrenheit (optional)

  // Check if any reads failed
  if (isnan(humidity) || isnan(tempC)) {
    Serial.println("Failed to read from DHT sensor!");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Sensor error");
    lcd.setCursor(0, 1);
    lcd.print("Check wiring");
    return;
  }

  // Print to Serial
  Serial.print("Temp: ");
  Serial.print(tempC);
  Serial.print(" *C  (");
  Serial.print(tempF);
  Serial.print(" *F)  Hum: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Display on 16x2 LCD
  // Row 0: "Temp: XX.X C"
  // Row 1: "Hum : XX.X %"
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(tempC, 1);   // one decimal place
  lcd.print((char)223);  // degree symbol (°) - 223 often works on HD44780
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("Hum : ");
  lcd.print(humidity, 1);
  lcd.print(" %");
}
