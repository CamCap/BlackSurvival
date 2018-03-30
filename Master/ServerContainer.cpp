#include "stdafx.h"
#include "ServerContainer.h"
#include "MasterPacket.h"
#include <algorithm>
#include "MasterHeader.h"

ServerContainer* ServerContainer::m_instance = NULL;
 
ServerContainer::ServerContainer()
	:SPeerContainer<Server>()
{
}


ServerContainer::~ServerContainer()
{
}

ServerContainer* ServerContainer::GetInstance()
{
	if (m_instance == NULL)
		m_instance = new ServerContainer();

	return m_instance;
}

void ServerContainer::ServerCheckPing(DWORD tick)
{
	DWORD cur_tick = ::GetTickCount();
	if (tick - m_tickPing < PING_CHECK_TIME)
		return;


	MAP_CONTANINER::iterator it = m_mapCon.begin();

	Server* _server = NULL;

	for (it; it != m_mapCon.end(); it++)
	{
		_server = it->second;
		if (_server == NULL)
			continue;

		//PING_Packet ping_packet;
		//ping_packet.packet_id = PACKET_ID_PING;
		//ping_packet.packet_size = sizeof(PING_Packet);
		//ping_packet.respon = false;
		//ping_packet.respon_tick = tick;

		_server->OnPingCheck();
	}
}

bool ServerContainer::IsCurrentServer(Server::SERVERTYPE type)
{
	MAP_CONTANINER::iterator it = m_mapCon.begin();

	Server* _server = NULL;

	for (it; it != m_mapCon.end(); it++)
	{
		_server = it->second;
		if (_server == NULL)
			continue;

		Server::SERVERTYPE _type = _server->GetType();

		if (_type == type)
		{
			return true;
		}
	}
	
	return false;
}

void ServerContainer::AuthServer(Server * server)
{
	if (IsCurrentServer(server->GetType()) == false)
	{
		AddAuthServer(server->GetId(), server);
	}
}

Server * ServerContainer::FindServer(int id)
{
	Server * server = FindPeer(id);

	if (server != NULL) return server;

	CSLOCK(m_cs)
	{
		////현재 연결된 유저 목록에서 지우고...
		//V::iterator it;
		VEC_CONTANINER::iterator it = \
			find_if(m_vecRogueServer.begin(), m_vecRogueServer.end(), \
			[&](Server* server)->bool { return id == server->GetId(); } \
		);

		if (it != m_vecRogueServer.end())
			server = *it;
		else
			server = NULL;
	}

	return server;
}

void ServerContainer::PushRogueServer(Server * server)
{
	if (server == NULL) return;

	CSLOCK(m_cs)
	{
		VEC_CONTANINER::iterator it = std::find(m_vecRogueServer.begin(), m_vecRogueServer.end(), server);

		if (it != m_vecRogueServer.end())
			return;

		m_vecRogueServer.push_back(server);
	}
}

void ServerContainer::PopRogueServer()
{
	if (m_vecRogueServer.size() == 0)
	{
		//UnLock();
		return;
	}

	Server* value = NULL;

	CSLOCK(m_cs)
	{
		VEC_CONTANINER::iterator it = m_vecRogueServer.begin();

		value = *it;
		m_vecRogueServer.erase(it);
	}
}



