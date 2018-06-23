#pragma once
#include "Packet.h"

struct CLIENT_JOIN_PACKET // 다른 서버에서 인게임 서버로 이동
	:public BTZPacket
{
	bool server_join;
	GUID user_id;
};

#define PACKET_ID_CLIENT_JOIN 0x30000000


#define ERROR_OVERLAP 0x31111111 // 중복된 유저
#define ERROR_SERVER_MOVE_ERROR 0x32222222 //서버 이동이 잘못됨