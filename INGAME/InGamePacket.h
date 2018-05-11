#pragma once
#include "Packet.h"

struct MOVE_SERVER_REQ_PACKET // 로그인 서버에서 매칭 서버로 이동
	:public BTZPacket
{
	DWORD server;
};

#define PACKET_ID_MOVE_SERVER_REQ 0x30000001

struct MOVE_SERVER_RES_PACKET
	:public MOVE_SERVER_REQ_PACKET
{
	char server_ip[8];
	int server_port;
};

#define PACKET_ID_MOVE_SERVER_RES 0x30000002

struct CLIENT_JOIN_PACKET // 다른 서버에서 인게임 서버로 이동
	:public BTZPacket
{
};

#define PACKET_ID_CLIENT_JOIN 0x30000003


#define ERROR_OVERLAP 0x31111111 // 중복된 유저
#define ERROR_SERVER_MOVE_ERROR 0x32222222 //서버 이동이 잘못됨