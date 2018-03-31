#pragma once
#include <map>
#include "Server.h"
#include "SPeerContainer.h"

//������ ������ ������ ��� ������..
//�ϴ� ��ȣ��Ŷ(���ڵ�)�� ������ ������ �ϱ⺸�ٴ�, �̹� ����� ���������� ������
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
	VEC_CONTANINER m_vecRogueServer; // ������ ���� ���

	DWORD m_tickPing;

	static ServerContainer* m_instance;
};

