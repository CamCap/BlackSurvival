#include "stdafx.h"
#include "User.h"


User::User()
{
	m_peer.m_packetProcess = std::bind(&User::PacketProcess, this, std::placeholders::_1);
}


User::~User()
{
}

void User::PacketProcess(BTZPacket* packet)
{
	switch (packet->packet_id)
	{

	}
}
