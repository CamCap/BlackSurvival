#pragma once
#include "ssocket.h"
#include "header.h"

#define SERVER_BUFF_SIZE 1024

class Server
	:public SPeer
{
public:
	DECLARE_ENUM( SERVERTYPE,
		NONE,
		LOGIN,
		MATCH,
		INGAME
	);

public:
	BOOL InitServer(unsigned short id, std::string name, SERVERTYPE type);

	SERVERTYPE GetType() { return m_type; }
	std::string GetName() { return m_name; }
	void OnPingCheck(DWORD tick);

private:
	virtual void PacketProcess(BTZPacket* packet);
public:
	Server();
	virtual ~Server();

private:
	std::string m_name;
	SERVERTYPE m_type;

	DWORD m_tickPing;
};

