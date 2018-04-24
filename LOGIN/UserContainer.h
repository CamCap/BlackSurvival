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

	User* PopWaitUser() { return m_container.PopWaitPeer(); }
	void PushWaitUser(User* user) { m_container.PushWaitPeer(user); }

	void AuthUser(User* user) { m_container.PushActive(user); }

	User* Find(int id) { return m_container.Find(id); }
	User* Find(std::string name) { return m_container.Find([&](User* puser)->bool {return name == puser->GetName(); }); }

	void DisConnectUser(User* pServer) {
		if (pServer == NULL) return;

		pServer->RelaseUser();
		m_container.PopActivePeer(pServer);
		m_container.PushWaitPeer(pServer);
	}

	bool CheckConnect(std::string name, int id, User* puser);

private:

	SPeerContainer<User> m_container;
	User* m_user[USER_LENGTH];
};

