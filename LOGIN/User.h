#pragma once
#include "ssocket.h"
#include "LoginPacket.h"
#include "SAuthManager.h"

struct BTZ_SQL;

class User
	:public SPeer
{
public:
//	int GetID() { return m_peer.GetId(); }
	void PacketProcess(BTZPacket* packet);
	void RelaseUser() { ReleaseSocket(); }
	std::string GetName() { return m_nickname; }

	void OnSendError(DWORD error);

	void OnLogin(DWORD sql);
	void OnSignUp(DWORD sql);

	void SetUserId(GUID id) { memcpy(&m_userid, &id, sizeof(m_userid)); }

protected:
	void ClientJoin(BTZPacket* packet); // 이동에 의한접속
	void IsLogin(BTZPacket* packet); // 로그인 요청
	void IsSignUp(BTZPacket* sql); // 회원가입 요청
	void MoveServer(BTZPacket* packet); // 서버이동 요청
	void MatchRequest(BTZPacket* packet);

//	void UpdateSignInTime(BTZ_SQL* sql);
public:
	User();
	~User();

private:
	std::string m_nickname;
	bool sex;

	GUID m_userid;
};

