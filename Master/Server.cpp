#include "stdafx.h"
#include "Server.h"
#include "MasterPacket.h"
#include "MasterHeader.h"
#include "SServerContainer.h"

void Server::PacketProcess(BTZPacket * packet)
{
	switch (packet->packet_id)
	{
	case PACKET_ID_PING:
	{
		if (m_server == NULL) break;
		m_server->OnPingCheck(GetTickCount());
	}	break;
	case PACKET_ID_AUTH:
	{
		AUTH_Packet* auth_packet = (AUTH_Packet*)packet;
	
		if (SServerContainer::GetInstance()->IsCurrentServer((SServer::SERVERTYPE)auth_packet->type) == false)
		{
			SServerContainer::GetInstance()->AuthServer(m_server);
			m_type = (SERVERTYPE)auth_packet->type;
		}	
	}	break;
	default:
		break;
	}
}

Server::Server()
{
	m_server = new SServer();
	m_server-> = PacketProcess;
}

Server::~Server()
{
	SAFE_DELETE(m_server);
}
