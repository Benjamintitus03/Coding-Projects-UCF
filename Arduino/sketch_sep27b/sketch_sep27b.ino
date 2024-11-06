#include <DHT.h>

#define DHTTYPE DHT11

#define dht_PIN 4
#define IR_PIN 12
#define LEDPIN 13


dht dht(dht_PIN, DHTTYPE);

void setup() {
  dht.begin();
  pinMode(IR_PIN, INPUT);
  pinMode(LEDPIN, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  float humidity = dht.readHumidity();
  float temp = dht.convertCtoF(dht.readTemperature(true, true));
  
  if(digitalRead(IR_PIN) == LOW){
    digitalWrite(LEADPIN, HIGH);
    delay(10);
  }
  else{
    digitalWrite(LEDPIN, HIGH);
    delay(10);
  }

   Serial.print("Humidity: ")
   Serial.print(humidity);
   Serial.print("\n");
   Serial.print("Temperature: ");
   Serial.print(tempt);
   Serial.print("\n");

   delay(500);
}