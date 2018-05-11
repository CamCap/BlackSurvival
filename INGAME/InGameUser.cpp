#include "stdafx.h"
#include "InGameUser.h"
#include <functional>
#include "InGamePacket.h"

InGameUser::InGameUser()
{
	m_packetProcess = std::bind(&InGameUser::PacketProcess, std::ref(*this), std::placeholders::_1);
}


InGameUser::~InGameUser()
{
}

void InGameUser::PacketProcess(BTZPacket* packet)
{
	switch (packet->packet_id)
	{
	case PACKET_ID_CLIENT_JOIN:
		break;
	default:
		break;
	}
}

void InGameUser::MoveServer(DWORD type)
{
}
