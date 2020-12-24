#ifndef MYPACKET_H
#define MYPACKET_H

#include <Arduino.h>
#include "devices.h"
#include "types.h"

namespace MyPacket
{
    // class Packet 
    // {
    //     String packet;
    //     int index;

    //     void init(int size)
    //     {
    //         // packet.resize(size);
    //         packet = "";
    //         index = 0;
    //     }
    // }
    bool OnUpdateIoTState(String packet, int index)
    {
        if(packet.length() < 2) 
        {
            Serial.println("HATA: Hatali paket boyutu!");
            return false;
        }

        device dev = (device)packet[index++];

        if (!isDeviceValid(dev))
        {
            Serial.print("HATA: ");
            Serial.print(dev);
            Serial.println(" isimli cihaz bulunamadi!");
            return false;
        }

        digitalWrite(dev, (uint8_t)packet[index++] == 1);
        return true;
    }

    bool Handle(String packet)
    {
        int index = 0;
        bool result = true;
        operation op = (operation)packet[index++];


        switch (op)
        {
        case operation::Login:
            
            break;

        case operation::UpdateIoTState:
            return OnUpdateIoTState(packet, index);
            break;

        case operation::UpdateValue:

            break;

        case operation::UpdateState:

            break;

        default:
            result = false;
            break;
        }
        return result;
    }
}

#endif