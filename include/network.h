#ifndef MYNETWORK_H
#define MYNETWORK_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "packet.h"

namespace MyNetwork
{
    WiFiServer server(80);
    WiFiClient client;

    void init(String ssid, String pass)
    {
        WiFi.begin(ssid, pass);

        Serial.print("Connecting");
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
                //Serial.write(c);
                }
                
                MyPacket::Handle(packet);
            }
    }
    }
}

#endif