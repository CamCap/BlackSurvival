#pragma once
#include "ssocket.h"

class MatchUser
	:public SPeer
{
public:
	MatchUser();
	~MatchUser();

	void PacketProcess(BTZPacket* packet);
	void OnSendError(DWORD error);

	std::string GetName() { return m_nickname; }
private:

	void MoveServer(BTZPacket* packet); // �����̵� ��û
	void UserDataMove(BTZPacket* packet);
private:

	std::string m_nickname;
	bool sex;

	GUID m_userid;
};

