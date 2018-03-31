#include "stdafx.h"
#include "Server.h"
#include "MasterPacket.h"
#include "ServerContainer.h"
#include "MasterHeader.h"


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
	{
		//OnPingCheck(GetTickCount());
		m_tickPing = GetTickCount();
	}	break;
	case PACKET_ID_AUTH:
	{
		AUTH_Packet* auth_packet = (AUTH_Packet*)packet;
		m_type = (SERVERTYPE)auth_packet->type;

		if (ServerContainer::GetInstance()->IsCurrentServer(m_type) == false)
		{
			ServerContainer::GetInstance()->AuthServer(this);
		}	
	}	break;
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


void Server::OnPingCheck(DWORD tick)
{
	if (tick - m_tickPing >= PING_CHECK_TIME)
	{
		m_tickPing = tick;

		if (GetOLType() != IO_NONE)
		{
#ifdef _DEBUG
			char buff[100];
			wsprintfA(buff, "%s No Ping Client disconnect \n", this->SERVERTYPEToString(m_type));
			Log::Instance()->WriteLog("Master", buff);
#endif
			ReleaseSocket();
		}
		else
		{
#ifdef _DEBUG
			char buff[100];
			wsprintfA(buff, "%s No Ping Client NULL Overlapped \n", this->SERVERTYPEToString(m_type));
			Log::Instance()->WriteLog("Master", buff);
#endif
		}
	}
}