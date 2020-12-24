#include <Arduino.h>
#include <Servo.h>
#include "devices.h"
#include "network.h"
#include "mytime.h"
#include "packet.h"


String ssid = "Guvenc_2.4G"; //"TacticForce";
String pass = "guvenc01";    //"Hes20181920";
String pack = "              ";

void setup() 
{
  Serial.begin(115200);
  Serial.println("");

  MyDevices::init();
  MyNetwork::init(ssid, pass);

  digitalWrite(D5, 1);
}

void loop() 
{
  // if (MyTime::isOneSecondPassed()) 
  // {
  //   // float temp = MyDevices::GetTemperature();
  //   // Create Packet
  //   // MyNetwork::SendToAll(packet);
  // }
  pack[0] = operation::UpdateIoTState;
  pack[1] = device::M_Lamba;
  pack[2] = 1;
  
  if (MyPacket::Handle(pack)) Serial.println("BASARILI!");
  
  delay(1000);
  digitalWrite(device::M_Lamba, LOW);
  delay(1000);
  //MyNetwork::Handle();
  //MyPacket::OnUpdateIoTState();
  
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