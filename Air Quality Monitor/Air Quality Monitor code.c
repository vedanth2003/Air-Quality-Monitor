#define BLYNK_TEMPLATE_ID "TMPLYKUVkcfs"
#define BLYNK_DEVICE_NAME "air pole vitap"
#define BLYNK_AUTH_TOKEN "qDBfBe9FrRHGUCXCdxspCiNlFlo-Z1CJ"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "AQM";
char pass[] = "123456789";
//------------------------------------ pins
#define DHTPIN D3
//------------------------------------
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
#define buz D6
int SW1=0;
BLYNK_CONNECTED()
{
 Blynk.syncVirtual(V0);
 }
float h,t;
void setup()
{
 // Debug console
 Serial.begin(9600);
 Blynk.begin(auth, ssid, pass);
 pinMode(buz,OUTPUT);
 digitalWrite(buz,LOW);
 dht.begin();
 lcd.begin();
 lcd.backlight();
 lcd.print(" WELCOME TO ");
 lcd.setCursor(0, 1);
 lcd.print(" VIT-AP ");
 delay(3000);
 lcd.clear();
}
int mq135,rmq135;
void loop()
{
 Blynk.run();

 rmq135 = analogRead(A0);
 mq135 = map(rmq135,180,1023,0,1000);

 h = dht.readHumidity();
 t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 Blynk.virtualWrite(V1, t);
 Blynk.virtualWrite(V2, h);
 Blynk.virtualWrite(V3, mq135);

 Serial.print("MQ135:");
 Serial.println(mq135);

 temp();
 delay(2000);
 lcd.clear();
 gas();
 delay(2000);
 lcd.clear();
 if(mq135>=300)
 {
 digitalWrite(buz,HIGH);
 delay(1000);
 }
 else
 {
 digitalWrite(buz,LOW);
 }
}
void temp()
{
 lcd.setCursor(0, 0);
 lcd.print("Temp: ");
 lcd.print(t);
 lcd.print(" ^C");
 Serial.println(t);
 lcd.setCursor(0, 1);
 lcd.print("Humi: ");
 lcd.print(h);
 lcd.print(" %");
 Serial.println(h);
 }
void gas()
{
 lcd.setCursor(0, 0);
 lcd.print("AIR QLY: ");
 lcd.print(mq135);
 lcd.print(" PPM");
 }
 