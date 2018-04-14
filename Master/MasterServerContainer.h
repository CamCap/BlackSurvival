#pragma once

#include "SServerContainer.h"
#include "Server.h"
#include "SSingleton.h"

#define SERVER_SIZE 10

class MasterServerContainer
	:public SSingleton<MasterServerContainer>
{
public:
	MasterServerContainer();
	~MasterServerContainer();

	void ServerPingCheck(DWORD tick) { m_container.PingCheck(tick); }

	Server* PopServer() { return m_container.PopServer(); }
	void PushServer(Server* server) { m_container.PushServer(server); }

	void AuthServer(Server* server) { m_container.PushAuthServer(server); }

	Server* FindServer(int id) { return m_container.FindServer(id); }

	bool IsCurrentServer(Server::SERVERTYPE type) {
		bool result = false;

		m_container.process([&](Server* server)->bool { if (result) return false; return type == server->GetType(); });

		return result;
	}


private:
	SServerContainer<Server> m_container;
	Server m_server[SERVER_SIZE];
};

