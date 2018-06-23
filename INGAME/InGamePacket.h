#pragma once
#include "Packet.h"

struct CLIENT_JOIN_PACKET // �ٸ� �������� �ΰ��� ������ �̵�
	:public BTZPacket
{
	bool server_join;
	GUID user_id;
};

#define PACKET_ID_CLIENT_JOIN 0x30000000


#define ERROR_OVERLAP 0x31111111 // �ߺ��� ����
#define ERROR_SERVER_MOVE_ERROR 0x32222222 //���� �̵��� �߸���