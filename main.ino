/*
 * DHT_To_RGB
 *
 * Created: 10/3/2015 
 * Author: HyDz
 * 
 * Color 2 RGB leds according to temperature and humidity.
 * HSV to RGB code from /** From http://www.cs.rit.edu/~ncs/color/t_convert.html
 */ 
 
 #include "DHT.h"

DHT dht;

const int DHTpin = 7; // Pin analogique du DHT

const int RedPinTemp = 3; // Pin de la diodes RGB Pour la température
const int GreenPinTemp = 5; //
const int BluePinTemp = 6;

const int RedPinHum = 9; // Pin de la diodes RGB Pour l'humidité
const int GreenPinHum = 10; //
const int BluePinHum = 11;

const int lowTempBlue = 12; // Valeur min correspond au bleu
const int highTempRed = 35; // Valeur max correspond au rouge

const int lowHumBlue = 30; // Valeur min correspond au bleu
const int highHumRed = 85; // Valeur max correspond au rouge

int Temp;
int Hum;

void setup()
{
 pinMode(RedPinTemp, OUTPUT);
 pinMode(BluePinTemp, OUTPUT);
 pinMode(GreenPinTemp, OUTPUT);
 
 pinMode(RedPinHum, OUTPUT);
 pinMode(BluePinHum, OUTPUT);
 pinMode(GreenPinHum, OUTPUT);

 dht.setup(DHTpin); // data pin du DHT
}


void loop()
{
  delay(dht.getMinimumSamplingPeriod());

  float humidite = dht.getHumidity();
  float temperature = dht.getTemperature();
  
  Temp = constrain(temperature, lowTempBlue, highTempRed);
  int tem = map(Temp, lowTempBlue, highTempRed, 240, 0); // map LumVal vers HSV
  
  float rt, gt, bt;
  HSVtoRGB(&rt, &gt, &bt, tem, 1,1); // HSV to RGB 
  
  Hum = constrain(humidite, lowHumBlue, highHumRed);
  int hme = map(Hum, lowHumBlue, highHumRed, 240, 0); // map LumVal vers HSV
  
  float rh, gh, bh;
  HSVtoRGB(&rh, &gh, &bh, hme, 1,1); // HSV to RGB 
  
  analogWrite(RedPinTemp, rt * 255);
  analogWrite(GreenPinTemp, gt * 255);
  analogWrite(BluePinTemp, bt * 255);
  
  // Leds à cathode commune
  analogWrite(RedPinHum, rh * 255);
  analogWrite(GreenPinHum, gh * 255);
  analogWrite(BluePinHum, bh * 255); 
 
}



/** From http://www.cs.rit.edu/~ncs/color/t_convert.html */
void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v ) {
  int i;
  float f, p, q, t;
  if( s == 0 ) {
    // achromatic (grey)
    *r = *g = *b = v;
    return;
  }
  h /= 60;          // sector 0 to 5
  i = floor( h );
  f = h - i;            // factorial part of h
  p = v * ( 1 - s );
  q = v * ( 1 - s * f );
  t = v * ( 1 - s * ( 1 - f ) );
  switch( i ) {
  case 0:
    *r = v;
    *g = t;
    *b = p;
    break;
  case 1:
    *r = q;
    *g = v;
    *b = p;
    break;
  case 2:
    *r = p;
    *g = v;
    *b = t;
    break;
  case 3:
    *r = p;
    *g = q;
    *b = v;
    break;
  case 4:
    *r = t;
    *g = p;
    *b = v;
    break;
  default:      // case 5:
    *r = v;
    *g = p;
    *b = q;
    break;
  }
}
