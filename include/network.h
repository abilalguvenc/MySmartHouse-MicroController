#ifndef MYNETWORK_H
#define MYNETWORK_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "packet.h"
#include "types.h"
#include <list>

//#define STATICIP

namespace MyNetwork
{
    WiFiServer server(80);
    WiFiClient client;


    IPAddress local_IP(192, 168, 1, 27);
    IPAddress gateway(192, 168, 1, 1);
    IPAddress subnet(255, 255, 0, 0);

    void init(String ssid, String pass)
    {
        #ifdef STATICIP
            if (!WiFi.config(local_IP, gateway, subnet)) 
            {
                Serial.println("HATA: STA ayari yapilamadi!");
            }
        #endif
        
        WiFi.begin(ssid, pass);
        
        Serial.print("Connecting to WiFi");
        while(WiFi.status()!= WL_CONNECTED)
        {
            delay(1000);
            Serial.print(".");
        }

        Serial.print("\nConnected to '");
        Serial.print(ssid);
        Serial.print("'. Server: ");
        Serial.print(WiFi.localIP());
        Serial.print(":");
        Serial.println(server.port());
        server.begin();
    }

    void Handle()
    {
        if (!MyNetwork::client.connected())
        {
            MyNetwork::client = MyNetwork::server.available();
            if (MyNetwork::client)
                Serial.println("Client baglandi!");
        }
        
        
        if (MyNetwork::client.connected())
        {
            String packet;
            if(MyNetwork::client.available() > 0)
            {
                while(MyNetwork::client.available() > 0)
                {
                    char c = MyNetwork::client.read();
                    if (c=='\n') break;
                    packet += c;
                }

                Serial.print("\nPacket: ");
                for (char c : packet)
                {
                    Serial.print((uint8_t)c);
                    Serial.print(" ");
                }
                Serial.println("");

                if (MyPacket::Handle(packet)) 
                {
                    Serial.println("Kullanici islemi basariyla gerceklestirildi.\n");
                }
                else
                {
                    Serial.println("Kullanicinin gonderdigi paket hatali!\n");
                    //MyNetwork::client.stop();
                }
            }
        }
    }

    void SendToAll(String packet)
    {
        if (MyNetwork::client.connected())
        {
            MyNetwork::client.print(packet);
        }
    }
}

#endif