#pragma once
#include <map>
#include "Server.h"
#include "SPeerContainer.h"

//인증과 비인증 서버를 어떻게 나눌까..
//일단 암호패킷(인코딩)을 보내서 인증을 하기보다는, 이미 연결된 서버인지를 따지자
class ServerContainer
	:public SPeerContainer<Server>
{
public:
	static ServerContainer* GetInstance();
	
	void ServerCheckPing(DWORD tickcount);
	bool IsCurrentServer(Server::SERVERTYPE type);
	void AuthServer(Server* server);

	Server* FindServer(int id);

	void RemoveAuthServer(int key) { this->MapPopBack(key); }
	void PushServer(Server* server) { this->VecPushBack(server); }
	void PushRogueServer(Server* server);
	void AddAuthServer(int id, Server* server) { this->MapPushBack(id, server); }
	Server* PopServer() { return (Server*)this->Pop_EmptyPeer(); }
	void PopRogueServer();

private:


public:
	ServerContainer();
	~ServerContainer();

private:
	VEC_CONTANINER m_vecRogueServer; // 비인증 서버 목록

	DWORD m_tickPing;

	static ServerContainer* m_instance;
};

