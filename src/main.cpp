#include <Arduino.h>
#include <Servo.h>
#include "devices.h"
#include "network.h"
#include "mytime.h"
#include "packet.h"

// BEYZA BURAYA beyza_e beyza_y veya hes yaz
#define bilal

#ifdef bilal
#define my_ssid "Guvenc_2.4G"
#define my_pass "guvenc01"
#endif

#ifdef beyza_e
#define my_ssid "ZyXEL_1578"
#define my_pass "34BUYUK42"
#endif

#ifdef beyza_y
#define my_ssid "ZyXEL_1578"
#define my_pass "34BUYUK42"
#endif

#ifdef hes
#define my_ssid "TacticForce"
#define my_pass "Hes20181920"
#endif

String pack;

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("");

  MyDevices::init();
  MyNetwork::init(my_ssid, my_pass);

  digitalWrite(D5, 1);
}

void loop() 
{
  if (MyTime::isOneSecondPassed()) 
  {
    float temp = MyDevices::GetTemperature();
    
    String tmpPck = MyPacket::NewTempPacket(temp);
    
    MyNetwork::SendToAll(tmpPck);
  }

  MyNetwork::Handle();
  
}