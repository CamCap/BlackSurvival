#pragma once
#include <map>
#include "Server.h"
#include "container.h"

//인증과 비인증 서버를 어떻게 나눌까..
//일단 암호패킷(인코딩)을 보내서 인증을 하기보다는, 이미 연결된 서버인지를 따지자
class ServerContainer
	:public Container<Server>
{
public:
	static ServerContainer* GetInstance();
	
	void ServerCheckPing(DWORD tickcount);
	bool IsCurrentServer(Server::SERVERTYPE type);
	void AuthServer(Server* server);

	void RemoveAuthServer(int key) { Container<Server>::MapPopBack(key); }
	Server* PopServer() { return Container<Server>::VecPopBack(); }
	void AddAuthServer(int id, Server* server) { this->MapPushBack(id, server); }
	void PushServer(Server* server) { this->VecPushBack(server); }

public:
	ServerContainer();
	~ServerContainer();

private:
	//MAP_SERVER m_mapServer; //비인증서버목록
	//MAP_SERVER m_mapAuthServer; // 인증서버목록

	static ServerContainer* m_instance;
};

