// wrote this test using the DHT11 sample file and added what I needed from the MCU code and some GFX Adafruit code also 
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library\
// 

#include <Adafruit_GFX.h> // Hardware-specific library
#include <MCUFRIEND_kbv.h>

MCUFRIEND_kbv tft;
#include "DHT.h"

#define DHTPIN 23
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF


// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// work in line numbers.  Font height in ht
int16_t ht = 16, top = 3, line, lines = 1, scroll;
DHT dht(DHTPIN, DHTTYPE);
void setup(){
 
    Serial.println(F("DHT Test!"));
    Serial.begin(9600);
    dht.begin();
    tft.reset();
    uint16_t id = tft.readID();
    tft.begin(id);
    tft.setRotation(45);     //Portrait
    tft.fillScreen(BLACK);
    tft.setTextColor(WHITE);
    tft.fillRect(0, 0, 480, 16, BLUE);
    tft.fillRect(0, 17, 200, 150, RED);
    tft.setTextSize(2);     // System font is 8 pixels.  ht = 8*2=16
    tft.setCursor(100, 0);
    tft.print("The Bickering Pigs Inside Weather Box");
 
    tft.setCursor(30, 0);
    

    tft.setCursor(0,50);
    tft.println("Humidity:");
    tft.setCursor(0,70);
    tft.println("Celcius:");
    tft.setCursor(0,90);
    tft.println("Temprature:");

}


void loop()
{ float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    tft.setCursor(0,180);
    tft.println(F("Failed to read from DHT sensor!"));
    return;
  }else{ // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  tft.setTextColor(WHITE,);
    //TempSensor(); //use this function if you want to print to serial. if screen is not displaying use this to test sensor.
    tft.setCursor(110, (scroll + top) * ht);
    if (++scroll >= lines) scroll = 0;
    tft.vertScroll(top * ht, lines * ht, (scroll) * ht);
    tft.setCursor(140,50);
    tft.println(h);
    tft.setCursor(140,70);
    tft.println(t);
    tft.setCursor(140,90);
    tft.println(f);
    
        
    delay(100);
    
    line++;
   
}}

void TempSensor(void) {
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
  } // Compute heat index in Fahrenheit (the default)
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
}
 
