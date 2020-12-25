#include <Arduino.h>
#include <Servo.h>
#include "devices.h"
#include "network.h"
#include "mytime.h"
#include "packet.h"

// BEYZA BURAYA beyza_e beyza_y veya hes yaz
#define hes

#ifdef bilal
#define my_ssid "Guvenc_2.4G"
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
  //if (MyTime::isOneSecondPassed()) 
  //{
  //  // float temp = MyDevices::GetTemperature();
  //  // Create Packet
  //  // MyNetwork::SendToAll(packet);
  //}

  // pack = "   ";
  // pack[0] = (uint8_t)operation::UpdateIoTState;
  // pack[1] = device::M_Lamba;
  // pack[2] = ON;
  // MyPacket::Handle(pack);
  // delay(1000);
  // 
  // pack[2] = OFF;
  // MyPacket::Handle(pack);
  // delay(1000);


  MyNetwork::Handle();
  
  // digitalWrite(device::O_Lamba, HIGH);
  // delay(1000);
  // digitalWrite(device::O_Lamba, LOW);
  // delay(100);
  // digitalWrite(device::O_Lamba, HIGH);
  // delay(100);
  // digitalWrite(device::O_Lamba, LOW);
  // delay(100);
  // put your main code here, to run repeatedly:
}