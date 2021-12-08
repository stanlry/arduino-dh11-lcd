#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <OneWire.h>


// I2C scanner
void beginScanner() {
  Wire.begin();
}

void readI2CAddress() {
  byte error, address;
  int Devices;
  Serial.println("Scanning...");
  Devices = 0;
  for (address = 1; address < 127; address++ )
  {

    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");
      Devices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
}

// DS18B20
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

void beginDS18B20() {
  sensors.begin();
}

float readDS18B20Temperature() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

// DH11
#define DHTTYPE DHT11
#define DHTPIN 2
DHT dht(DHTPIN, DHTTYPE);

void beginDHT() {
  dht.begin();
}

float readDHTTemperature() {
  return dht.readTemperature();
}

float readDHTHumidity() {
  return dht.readHumidity();
}


// 16x2 LCD
LiquidCrystal_I2C lcd(0x27,16,2);

void beginLCD() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
}

void setup() {
  // start serial port
  Serial.begin(9600);
  // Start up the library
  // beginDS18B20();
  beginDHT();
  beginLCD();
  // beginScanner();
}

void loop() {
  // Serial.println(readDS18B20Temperature());
  // readI2CAddress();
  lcd.setCursor(0,0);
  lcd.print(readDHTTemperature());
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print(readDHTHumidity());
  lcd.print("%");
  // wait 1 second
  delay(1000);
}
