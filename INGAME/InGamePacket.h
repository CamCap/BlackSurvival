#pragma once
#include "Packet.h"

struct MOVE_SERVER_REQ_PACKET // �α��� �������� ��Ī ������ �̵�
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

struct CLIENT_JOIN_PACKET // �ٸ� �������� �ΰ��� ������ �̵�
	:public BTZPacket
{
};

#define PACKET_ID_CLIENT_JOIN 0x30000003


#define ERROR_OVERLAP 0x31111111 // �ߺ��� ����
#define ERROR_SERVER_MOVE_ERROR 0x32222222 //���� �̵��� �߸���