#include <Arduino.h>
#include <Servo.h>
#include "devices.h"
#include "network.h"
#include "mytime.h"
#include "packet.h"


String ssid = "Guvenc_2.4G"; //"TacticForce";
String pass = "guvenc01";    //"Hes20181920";
String pack;

void setup() 
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("");

  MyDevices::init();
  MyNetwork::init(ssid, pass);

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