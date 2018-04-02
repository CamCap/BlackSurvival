#pragma once
#include "ssocket.h"
#include "header.h"

#define SERVER_BUFF_SIZE 1024

class MasterServer
{
public:
	union MASTERSERVERTYPE
	{
		SServer::SERVERTYPE server;
		union MASTERSERVER
		{

		};
	};

public:

	std::string GetName() { return m_name; }

private:
	virtual void PacketProcess(BTZPacket* packet);
public:
	MasterServer();
	virtual ~MasterServer();

private:
	std::string m_name;

	DWORD m_tickPing;
};

