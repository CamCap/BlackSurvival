#pragma once
#include "SPeerContainer.h"
#include "User.h"
#include "SSingleton.h"

#define USER_LENGTH 50

class UserContainer
	:public SSingleton<UserContainer>
{
public:
	UserContainer();
	~UserContainer();

	void ServerPingCheck(DWORD tick) { m_container.PingCheck(tick); }

	User* PopWaitServer() { return m_container.PopWaitPeer(); }
	void PushWaitServer(User* server) { m_container.PushWaitPeer(server); }

	void AuthServer(User* server) { m_container.PushActive(server); }

	User* Find(int id) { return m_container.Find(id); }
	
	void DisConnectServer(User* pServer) {
		if (pServer == NULL) return;

		pServer->RelaseUser();
		m_container.PopActivePeer(pServer);
		m_container.PushWaitPeer(pServer);
	}


private:

	SPeerContainer<User> m_container;
	User m_user[USER_LENGTH];
};

