#include <Arduino.h>
#include <Servo.h>
#include "devices.h"
#include "network.h"
#include "mytime.h"
#include "packet.h"

#define beyza_e

#ifdef beyza_e
#define my_ssid "Buyuk"
#define my_pass "34buyuk42"
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
  MyDevices::SetDeviceState(device::A_Hirsiz, ON);
  Serial.println("\nAkilli evim baslatildi!");
}

void loop() 
{
  MyNetwork::Handle();

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
}