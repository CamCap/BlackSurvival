#pragma once
#include <map>
#include "Server.h"
#include "container.h"

//������ ������ ������ ��� ������..
//�ϴ� ��ȣ��Ŷ(���ڵ�)�� ������ ������ �ϱ⺸�ٴ�, �̹� ����� ���������� ������
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
	//MAP_SERVER m_mapServer; //�������������
	//MAP_SERVER m_mapAuthServer; // �����������

	static ServerContainer* m_instance;
};

