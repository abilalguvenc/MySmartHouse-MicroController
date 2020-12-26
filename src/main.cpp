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

  MyNetwork::init(my_ssid, my_pass);

  MyDevices::init();
  MyDevices::SetDeviceState(device::A_Yangin, ON);

  Serial.println("\nAkilli evim baslatildi!");
}

void loop() 
{
  if (MyTime::isOneSecondPassed()) 
  {    
    MyDevices::UpdateAC();

    String tmpPck = MyPacket::NewTempPacket();
    MyNetwork::SendToAll(tmpPck);

    if (MyDevices::GetAlarm(device::A_Hirsiz))
    {
      Serial.println("ALARM: Hirsiz var!");

      String alertPck = MyPacket::NewAlarmPacket(device::A_Hirsiz);
      MyNetwork::SendToAll(alertPck);
    }
    
    if (MyDevices::GetAlarm(device::A_Yangin))
    {
      Serial.println("ALARM: Yangin var!");
      
      String alertPck = MyPacket::NewAlarmPacket(device::A_Yangin);
      MyNetwork::SendToAll(alertPck);
    }
  }

  MyNetwork::Handle();
  
}