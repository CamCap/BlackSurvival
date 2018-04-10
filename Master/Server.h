#pragma once
#include "ssocket.h"
#include "header.h"


#define SERVER_BUFF_SIZE 1024

class Server
{
public:
	DECLARE_ENUM(SERVERTYPE,
	NONE,
	LOGIN,
	MATCH,
	INGAME);

private:
	void PacketProcess(BTZPacket* packet);
public:
	SERVERTYPE GetType() { return m_type; }
	Server();
	virtual ~Server();

private:
	SServer* m_server;

	SERVERTYPE m_type;
};

