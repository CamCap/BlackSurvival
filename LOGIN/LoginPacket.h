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

struct ERR_PACKET
	:public BTZPacket
{
	DWORD errcode;
};

#define PACKET_ID_ERR 0x29999999

#define ERROR_CONNECT_USER 0x21111111 // 이미 접속한 ID
#define ERROR_DISCONNECT_USER 0x22222222 // 접속이 끊어진 상태
#define ERROR_NO_USER 0x23333333 // 로그인 정보가 잘못됨
#define ERROR_OVERLAP 0x24444444


#pragma pack(pop)


