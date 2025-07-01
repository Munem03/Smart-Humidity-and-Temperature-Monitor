#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// OLED screen size
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Create OLED display object (I2C address 0x3C, no reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT11 sensor setup
#define DHTPIN 2       // DHT11 data pin connected to digital pin 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Infinite loop if OLED fails
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Initializing...");
  display.display();

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  delay(2000); // Wait 2 seconds between readings

  // Read humidity and temperature
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature(); // Celsius

  // Check for failed readings
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Sensor Error");
    display.display();
    return;
  }

  // Print to Serial Monitor
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\tTemperature: ");
  Serial.print(temperature);
  Serial.println(" *C");

  // Display on OLED
  display.clearDisplay();

  display.setTextSize(2); // Large text
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");

  display.setCursor(0, 32);
  display.print("Hum:  ");
  display.print(humidity);
  display.println(" %");

  display.display();
}
