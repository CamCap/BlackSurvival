#pragma once
#include "packet.h"

struct LOGIN_REQ_PACKET
{
	char id[20];
	char pw[20];
};

#define PACKET_ID_LOGIN_REQ 0x20000000

struct LOGIN_RES_PACKET
{

};

#define PACKET_ID_LOGIN_RES 0x20000001