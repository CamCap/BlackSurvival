#include "stdafx.h"
#include "Server.h"
#include "MasterPacket.h"
#include "ServerContainer.h"


BOOL Server::InitServer(unsigned short id, std::string name, SERVERTYPE type)
{
	m_id = id;
	m_name = name;
	m_type = type;

	return 0;
}

void Server::PacketProcess(BTZPacket * packet)
{
	switch (packet->packet_id)
	{
	case PACKET_ID_PING:
		break;
	case PACKET_ID_AUTH:
	{
		AUTH_Packet* auth_packet = (AUTH_Packet*)packet;
		m_type = (SERVERTYPE)auth_packet->type;
		ServerContainer::GetInstance()->AuthServer(this);
	}
		break;
	default:
		break;
	}
}

Server::Server()
	:m_type(SERVERTYPE::NONE)
{
	m_id = -1;
}


Server::~Server()
{
}


