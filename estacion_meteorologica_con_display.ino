#include <TFT.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>
#include <Adafruit_BMP085.h>
#include "DHT.h"

#define cs   10
#define dc   8
#define rst  9

TFT TFTscreen = TFT(cs, dc, rst);
char tPrint[8];
char hPrint[8];
char pPrint[8];


Adafruit_BMP085 bmp;

#define DHTTYPE DHT22
#define DHTPIN 7
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  /* Initialise the sensor */
  if (!bmp.begin())
  {
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while (1);
  }

  Serial.println(F("DHTxx test!"));

  dht.begin();

  TFTscreen.begin();

  TFTscreen.background(0, 0, 0);

  TFTscreen.stroke(255, 255, 255);
  // set the font size
  TFTscreen.setTextSize(2);
  // write the text to the top left corner of the screen

}

void loop() { // 128px x 160px

  float t = dht.readTemperature();
  float h = dht.readHumidity();
  float p = (bmp.readPressure() / 100);
  float f = dht.readTemperature(true);

  dtostrf(t, 4, 1, tPrint);
  dtostrf(h, 4, 1, hPrint);
  dtostrf(p, 4, 0, pPrint);

  TFTscreen.background(0, 0, 0);
  TFTscreen.stroke(255, 255, 255);
  TFTscreen.setTextSize(2);

  TFTscreen.text("Temperatura ", 5, 5);
  TFTscreen.rect(0, 0, 160, 128);
  TFTscreen.text(tPrint, 5, 25);
  TFTscreen.text("C ", 60, 25);

  TFTscreen.text("Humedad ", 5, 45);
  //TFTscreen.rect(0, 30, 126, 60);
  TFTscreen.text(hPrint, 5, 65);
  TFTscreen.text("% ", 55, 65);

  TFTscreen.text("Presion ", 5, 85);
  // TFTscreen.rect(0, 60, 126, 60);
  TFTscreen.text(pPrint, 5, 105);
  TFTscreen.text("hPa ", 60, 105);

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%   Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print("Pressure = ");
  Serial.print(p);
  Serial.println(" Pa");

  delay(60000);
}
