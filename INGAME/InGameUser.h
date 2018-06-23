#pragma once
#include "ssocket.h"

class InGameUser
	:public SPeer
{
public:
	InGameUser();
	~InGameUser();
	void PacketProcess(BTZPacket*);
	std::string GetName() { return m_nickname;}
	void ReleaseUser() { m_nickname.clear(); ZeroMemory(&m_guid, sizeof(m_guid)); this->ReleaseSocket(); }

private:

	void Matching (BTZPacket* packet);
	void MoveServer(BTZPacket* type);

private:
	GUID m_guid;
	std::string m_nickname;
	bool sex;
};

