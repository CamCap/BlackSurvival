#pragma once
#include "Packet.h"
#include <Windows.h>
#pragma pack(push, 1)

struct PING_Packet
	:public BTZPacket
{
	bool respon;
	DWORD respon_tick;
};

#define PACKET_ID_PING 0x10000000

#pragma pack(pop)