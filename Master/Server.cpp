#include "stdafx.h"
#include "Server.h"
#include "MasterPacket.h"
#include "MasterHeader.h"
#include "SServerContainer.h"

void SServer::PacketProcess(BTZPacket * packet)
{
	switch (packet->packet_id)
	{
	case PACKET_ID_PING:
	{
		//OnPingCheck(GetTickCount());
		m_tickPing = GetTickCount();
	}	break;
	case PACKET_ID_AUTH:
	{
		AUTH_Packet* auth_packet = (AUTH_Packet*)packet;
		m_type = (SERVERTYPE)auth_packet->type;

		if (SServerContainer::GetInstance()->IsCurrentServer(m_type) == false)
		{
			SServerContainer::GetInstance()->AuthServer(this);
		}	
	}	break;
	default:
		break;
	}
}

SServer::SServer()
	:m_type(SERVERTYPE::NONE)
{
	m_id = -1;
}


SServer::~SServer()
{
}
