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

struct ERR_PACKET
{
	DWORD errcode;
};

#define PACKET_ID_ERR 0x20000002



#define ERROR_CONNECT_USER 0x900000000
#define ERROR_DISCONNECT_USER 0x90000001
#define ERROR_NO_USER 0x90000002 // 유저가 없음
