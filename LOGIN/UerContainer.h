#pragma once
#include "SPeerContainer.h"
#include "User.h"

class UerContainer
{
public:
	UerContainer();
	~UerContainer();

	User* FindUser(int id) { return m_container.Find(id); }

	void PingCheckUsers(DWORD tick) { m_container.PingCheck(tick); }

	void PushUser(User* puser) { m_container.PushActive(puser); }
	void DisConnectUser(User* pUser) {
		if (pUser == NULL) return;
		
		pUser->RelaseUser();
		m_container.PopActivePeer(pUser);
		m_container.PushWaitPeer(pUser);
	}

private:

	SPeerContainer<User> m_container;
};

