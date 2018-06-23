#pragma once
#include "SSingleton.h"
#include "Container.h"
#include "MatchingUser.h"
#include "MatchingHeader.h"
#include "SPeerContainer.h"
#include "SAuthManager.h"
#include <thread>

class Room
{
public:
	MatchUser* Users[MAX_MATCH_USER];
//	unsigned char id[4][4];
	GUID id;

//	template<class Func>
	void Function(int num = MAX_MATCH_USER);
};


class UserMatchingManager
	:public SSingleton<UserMatchingManager>
{
public:
	UserMatchingManager();
	~UserMatchingManager();

	void ServerPingCheck(DWORD tick) { m_waitUsers.PingCheck(tick); }

	MatchUser* PopWaitUser() { return m_waitUsers.PopWaitPeer(); }
	void PushWaitUser(MatchUser* user) { m_waitUsers.PushWaitPeer(user); }
	void PushActiveUser(MatchUser* user) { m_waitUsers.PushActive(user); }

	MatchUser* Find(int id) { return m_waitUsers.Find(id); }
	MatchUser* Find(std::string name) { return m_waitUsers.Find([&](MatchUser* puser)->bool {return name == puser->GetName(); }); }

	void DisConnectUser(MatchUser* user) {
		if (user == NULL) return;

		user->ReleaseSocket();
		m_waitUsers.PopActivePeer(user);
		m_waitUsers.PushWaitPeer(user);
	}

	bool CheckConnect(std::string name, int id, MatchUser* puser);

	////////////////////////////////////////////////////////////////////////////////////

	void GiveGUID(unsigned char id[4][4]);
	void InvChiperGUID(unsigned char id[4][4]) { m_auth.AES128_InvCipher(id); }
	
	/////////////////////////////////////////////////////////////////////////////////////

	void SetMatchNum(int num);

	void SetMatching(MatchUser* puser);
	Room* IsMathching();
	
	///////////////////////////////////////////////////////////////////////


	DWORD WINAPI MatchingLoop(LPVOID pArg);
private:
	void WaitEvent();
	void SetEvent();
	void ResetEvent();


private:
	int matchnum;

	ListContainer<Room> m_roomContainer;
	SPeerContainer<MatchUser> m_waitUsers;
	SAuth m_auth;


	SCriticalSection m_cs;
	HANDLE m_event; // 이벤트 핸들

	std::thread m_threadHandle;
};

