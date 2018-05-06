#include "stdafx.h"
#include "InGameUser.h"
#include <functional>

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

	}
}
