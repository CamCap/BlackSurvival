#include "stdafx.h"
#include "Server.h"
#include "MasterPacket.h"
#include "MasterHeader.h"
#include "MasterServerContainer.h"

void Server::PacketProcess(BTZPacket * packet)
{

	switch (packet->packet_id)
	{
	case PACKET_ID_PING:
	{
		m_server.OnPingCheck(GetTickCount());
	}	break;
	case PACKET_ID_AUTH:
	{
		AUTH_Packet* auth_packet = (AUTH_Packet*)packet;
	
		if (MasterServerContainer::GetInstance()->IsCurrentServer((SERVERTYPE)auth_packet->type) == false)
		{
			MasterServerContainer::GetInstance()->AuthServer(this);
			m_type = (SERVERTYPE)auth_packet->type;
		}	
	}	break;
	default:
		break;
	}
}

Server::Server()
{
	m_server.m_packetProcess = std::bind(&Server::PacketProcess, std::ref(*this), std::placeholders::_1);
}

Server::~Server()
{
	m_server.ReleaseSocket();
}
