#pragma once

#include "SServerContainer.h"
#include "Server.h"

#define SERVER_SIZE 10

class MasterServerContainer
{
public:
	MasterServerContainer();
	~MasterServerContainer();

	void ServerPingCheck(DWORD tick) { m_container.PingCheck(tick); }

private:
	SServerContainer<Server> m_container;
	Server m_server[SERVER_SIZE];
};

