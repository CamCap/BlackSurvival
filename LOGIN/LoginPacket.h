#pragma once
#include "packet.h"

#pragma pack(push, 1)

struct LOGIN_REQ_PACKET
	:public BTZPacket
{
	char id[20];
	char pw[20];
};

#define PACKET_ID_LOGIN_REQ 0x20000000

struct LOGIN_RES_PACKET
	:public BTZPacket
{
	bool IsSucess;
};

#define PACKET_ID_LOGIN_RES 0x20000001


struct SIGNUP_REQ_PACKET
	:public BTZPacket
{
	char id[20];
	char pw[20];
	char nickname[20];
	bool sex;
};

#define PACKET_ID_SIGNUP_REQ 0x20000002

struct SIGNUP_RES_PACKET
	:public BTZPacket
{
	bool IsSucess;
	char message[20];
};
#define PACKET_ID_SIGNUP_RES 0x20000003


struct CLIENT_JOIN_PACKET // 다른 서버에서 로그인 서버로 이동
	:public BTZPacket
{
	bool server_join;
	GUID guid;
};

#define PACKET_ID_CLIENT_JOIN 0x20000006


#define ERROR_NO_USER ERROR_ID + 1 // 로그인 정보가 잘못됨
#define ERROR_OVERLAP ERROR_ID + 2


#pragma pack(pop)


