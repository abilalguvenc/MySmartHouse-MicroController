// #ifndef MYPACKET_H
// #define MYPACKET_H

// #include <Arduino.h>
// #include "devices.h"
// #include "types.h"

// namespace MyPacket
// {
//     bool OnUpdateIoTState(String packet, int index)
//     {
//         device dev = (device)packet[index++];
//         Serial.print("Device: ");
//         Serial.println(dev);
//         return false;
//     }

//     bool Handle(String packet)
//     {
//         int index = 0;
//         bool result = true;
//         operation op = (operation)packet[index++];


//         switch (op)
//         {
//         case operation::Login:
            
//             break;

//         case operation::UpdateIoTState:
//             return OnUpdateIoTState(packet, index);
//             break;

//         case operation::UpdateValue:

//             break;

//         case operation::UpdateState:

//             break;

//         default:
//             result = false;
//             break;
//         }
//         return result;
//     }
// }

// #endif