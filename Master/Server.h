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

public:
	void PacketProcess(BTZPacket* packet);
public:
	SERVERTYPE GetType() { return m_type; }

	Server();
	virtual ~Server();

	void InitPeer(SOCKET socket, SOCKADDR_IN addr, int userid) { m_server.InitPeer(socket, addr, userid); }
	void InitServer(std::string name) { m_server.SetName(name); }
	BOOL RecvPacket(int DwNumberBytes) { return m_server.RecvPacket(DwNumberBytes); }
	void CheckSendPacket() { m_server.CheckSendPacket(); }
	int GetID() { return m_server.GetId(); }
	void Relase() { m_server.ReleaseSocket(); }

	//SPeer* operator() { return (SPeer*)&m_server; }
	operator SPeer*() { return (SPeer*)&m_server; }
private:
	SServer m_server;

	SERVERTYPE m_type;
};

