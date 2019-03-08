#include <LiquidCrystal.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

BlynkTimer timer;
WidgetRTC rtc;

char auth[] = "Blynk auth Token";
char ssid[] = "Wi-Fi Name";
char pass[] = "Wi-Fi Password";

LiquidCrystal lcd(D0, D1, D2, D4, D5, D6);

int Relay1;
int Relay2;

void setup()
{
  rtc.begin();
  Serial.begin(9600);
  lcd.begin(16,2);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
  timer.run();
  Relay1 = digitalRead(D3);
  Relay2 = digitalRead(D7);

  
  String currentTime = String(hour()) + ":" + minute() + ":" + second();
  String currentDate = String(day()) + " " + month() + " " + year();
  Serial.print("Current time: ");
  Serial.print(currentTime);
  Serial.print(" ");
  Serial.print(currentDate);
  Serial.println();
  
  Blynk.virtualWrite(V1, currentTime);
  Blynk.virtualWrite(V2, currentDate);
  lcd.setCursor(0,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print(currentTime);

  if(Relay1 == LOW && Relay2== LOW){
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("BUlB-ON");
    lcd.setCursor(9,1);
    lcd.print("Fan-ON");
    delay(1000);    
    
    }

    else if(Relay1 == LOW && Relay2 == HIGH){
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("BUlB-ON");
    lcd.setCursor(9,1);
    lcd.print("Fan-OFF");   
    delay(1000); 
    
    }

    else if(Relay1 == HIGH && Relay2 == LOW){
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("BUlB-OFF");
    lcd.setCursor(9,1);
    lcd.print("Fan-ON");    
    delay(1000);
    }

    if(Relay1 == HIGH && Relay2 == HIGH){
    lcd.setCursor(0,1);
    lcd.print("                 ");
    lcd.setCursor(0,1);
    lcd.print("BUlB-OFF");
    lcd.setCursor(9,1);
    lcd.print("Fan-OFF");  
    delay(1000);  
    
    }
}
