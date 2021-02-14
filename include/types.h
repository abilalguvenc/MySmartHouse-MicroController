#ifndef MYTYPES_H
#define MYTYPES_H

#define OFF false
#define ON true

enum device : int
{
  O_Lamba,
  O_Pencere,
  O_Klima,

  Y_Lamba,
  Y_Pencere,

  M_Lamba,
  M_Kettle,

  A_Hirsiz,
  A_Yangin,
  S_Termometre
};

enum device_pin : int
{
  PO_Lamba    = D0,
  PO_Pencere  = D1,
  PO_Klima_H  = D2,
  PO_Klima_C  = D3,

  // PY_Lamba    = D5,
  PY_Pencere  = D6,

  PM_Lamba    = D5,
  PM_Kettle   = D8,

  PS_Hareket  = D7,
  PS_Sicaklik = D4,

  P_None      = 99
};

bool isDeviceValid(device dev)
{
  bool res = false;
  switch(dev)
  {
    case device::O_Lamba:
    case device::O_Pencere:
    case device::O_Klima:

    case device::Y_Lamba:
    case device::Y_Pencere:

    case device::M_Lamba:
    case device::M_Kettle:
    
    case device::A_Hirsiz:
    case device::A_Yangin:
      res = true;
      break;
    default:
      res = false;
  }
  return res;
}

device_pin getDevicePin(device dev)
{
  switch (dev)
  {
    case device::O_Lamba:
      return device_pin::PO_Lamba;
    case device::O_Pencere:
      return device_pin::PO_Pencere;
    // case device::Y_Lamba:
    //   return device_pin::PY_Lamba;
    case device::M_Lamba:
      return device_pin::PM_Lamba;
    case device::M_Kettle:
      return device_pin::PM_Kettle;
    default:
      return device_pin::P_None;
  }
  return device_pin::P_None;
}

inline bool isBool(uint8_t val)
{
  return val == (uint8_t)0x1 || val == (uint8_t)0x0;
}

enum operation : uint8_t
{
  Login = 0,          // opcode + username (str) + password (str)
  UpdateDevice,       // opcode + deviceId (byte) + newstate (bool) + temperature (int)
  UpdateValue,        // opcode + 
  LoginResult,        // opcode + success (bool) ? iotstates[n] (bool[n]) : null
  Alert,              // opcode + alertid (byte) + alertstate (bool)
};

#endif