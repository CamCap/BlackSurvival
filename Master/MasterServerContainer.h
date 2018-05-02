#pragma once

#include "SPeerContainer.h"
#include "Server.h"
#include "SSingleton.h"

#define SERVER_SIZE 10

class MasterServerContainer
	:public SSingleton<MasterServerContainer>
{
public:
	MasterServerContainer();
	~MasterServerContainer();
public:
	void ServerPingCheck(DWORD tick) { m_container.PingCheck(tick); }

	Server* PopWaitServer() { return m_container.PopWaitPeer(); }
	void PushWaitServer(Server* server) {  m_container.PushWaitPeer(server); }

	void AuthServer(Server* server) { m_container.PushActive(server); }

	Server* Find(int id) { return m_container.Find(id); }

	bool IsCurrentServer(Server::SERVERTYPE type) {
		bool result = false;

		m_container.process([&](Server* server)->bool { if (result) return false; return type == server->GetType(); });

		return result;
	}

	void DisConnectServer(Server* pServer) {
		if (pServer == NULL) return;

		pServer->Relase();
		m_container.PopActivePeer(pServer);
		m_container.PushWaitPeer(pServer);
	}

private:
	SPeerContainer<Server> m_container;
	Server* m_server[SERVER_SIZE];
};

