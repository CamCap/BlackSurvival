#pragma once
#include "Packet.h"
#include <Windows.h>
#pragma pack(push, 1)

struct PING_Packet
	:public BTZPacket
{
	bool respon;
};

#define PACKET_ID_PING 0x10000000

struct AUTH_Packet
	:public BTZPacket
{
	int type;
};
#define PACKET_ID_AUTH 0x10000001

#pragma pack(pop)

