#pragma once
#include "Packet.h"

#pragma pack(push, 1)

struct MATCHING_PACKET
	:public BTZPacket
{
public:
	GUID room_id;
};

#define PACKET_ID_MATCHING 0x40000000


#pragma pack(pop)