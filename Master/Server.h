#pragma once
#include "ssocket.h"
#include "header.h"

#define SERVER_BUFF_SIZE 1024

class MasterServer
{
public:
	enum MASTERSERVERTYPE
	{

	};

public:

	SERVERTYPE GetType() { return m_type; }
	std::string GetName() { return m_name; }
	void OnPingCheck(DWORD tick);

private:
	virtual void PacketProcess(BTZPacket* packet);
public:
	MasterServer();
	virtual ~MasterServer();

private:
	std::string m_name;
	SERVERTYPE m_type;

	DWORD m_tickPing;
};

