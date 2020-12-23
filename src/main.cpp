#include <Arduino.h>
#include <Servo.h>
#include "devices.h"
#include "network.h"
#include "mytime.h"


String ssid = "G_Misafir_2.4G";
String pass = "misafir01";

void setup() 
{
  Serial.begin(115200);
  Serial.println("");

  MyDevices::init();
  MyNetwork::init(ssid, pass);
}

void loop() 
{
  if (MyTime::isOneSecondPassed()) 
  {
    float temp = MyDevices::GetTemperature();
    // Create Packet
    // MyNetwork::SendToAll(packet);
    Serial.print(" Sicaklik: ");
    Serial.println(temp);
  }

  MyNetwork::Handle();
  

  
  digitalWrite(device::O_Lamba, HIGH);
  delay(1000);
  digitalWrite(device::O_Lamba, LOW);
  delay(100);
  digitalWrite(device::O_Lamba, HIGH);
  delay(100);
  digitalWrite(device::O_Lamba, LOW);
  delay(100);
  // put your main code here, to run repeatedly:
}