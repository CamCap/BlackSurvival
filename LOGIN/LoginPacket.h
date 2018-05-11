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

struct MOVE_SERVER_REQ_PACKET // 로그인 서버에서 매칭 서버로 이동
	:public BTZPacket
{
	DWORD server;
};

#define PACKET_ID_MOVE_SERVER_REQ 0x20000004

struct MOVE_SERVER_RES_PACKET
	:public MOVE_SERVER_REQ_PACKET
{
	char server_ip[8];
	int server_port;
};

#define PACKET_ID_MOVE_SERVER_RES 0x20000005

struct CLIENT_JOIN_PACKET // 다른 서버에서 로그인 서버로 이동
	:public BTZPacket
{
};

#define PACKET_ID_CLIENT_JOIN 0x20000006

#define ERROR_CONNECT_USER 0x21111111 // 이미 접속한 ID
#define ERROR_DISCONNECT_USER 0x22222222 // 접속이 끊어진 상태
#define ERROR_NO_USER 0x23333333 // 로그인 정보가 잘못됨
#define ERROR_OVERLAP 0x24444444
#define ERROR_SERVER_MOVE_ERROR 0x25555555


#pragma pack(pop)


