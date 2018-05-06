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
	int GetID() { return m_id; }
private:

	std::string m_nickname;
	bool sex;
};

