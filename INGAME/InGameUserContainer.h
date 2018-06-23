#pragma once
#include "SPeerContainer.h"
#include "InGameUser.h"
#include "SSingleton.h"
#include "SAuthManager.h"

#define USER_LENGTH 50

class InGameUserContainer
	:public SSingleton<InGameUserContainer>
{
public:
	InGameUserContainer();
	~InGameUserContainer();
	void ServerPingCheck(DWORD tick) { m_container.PingCheck(tick); }

	InGameUser* PopWaitUser() { return m_container.PopWaitPeer(); }
	void PushWaitUser(InGameUser* user) { m_container.PushWaitPeer(user); }

	void PushActiveUser(InGameUser* user) { m_container.PushActive(user); }

	InGameUser* Find(int id) { return m_container.Find(id); }
	InGameUser* Find(std::string name) { return m_container.Find([&](InGameUser* puser)->bool {return name == puser->GetName(); }); }

	void DisConnectUser(InGameUser* puser) {
		if (puser == NULL) return;

		puser->ReleaseUser();
		m_container.PopActivePeer(puser);
		m_container.PushWaitPeer(puser);
	}

	bool CheckConnect(std::string name, int id, InGameUser* puser);

	void InvChiperGUID(GUID& id);

private:
	SPeerContainer<InGameUser> m_container;
	InGameUser* m_user[USER_LENGTH];


	SAuth m_auth;
};

