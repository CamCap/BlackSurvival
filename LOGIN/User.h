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
	void ClientJoin(BTZPacket* packet); // �̵��� ��������
	void IsLogin(BTZPacket* packet); // �α��� ��û
	void IsSignUp(BTZPacket* sql); // ȸ������ ��û
	void MoveServer(BTZPacket* packet); // �����̵� ��û
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

