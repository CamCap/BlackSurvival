#include "stdafx.h"
#include "User.h"
#include "UserContainer.h"
#include "DBManager.h"

User::User()
{
	m_peer.m_packetProcess = std::bind(&User::PacketProcess, this, std::placeholders::_1);
}


User::~User()
{
}

void User::PacketProcess(BTZPacket* packet)
{
	switch (packet->packet_id)
	{
	case PACKET_ID_LOGIN_REQ:
		OnLogin(packet);
		break;
	default:
		break;
	}
}

void User::OnLogin(BTZPacket * packet)
{
	LOGIN_REQ_PACKET* req_packet = (LOGIN_REQ_PACKET*)packet;

	if (UserContainer::GetInstance()->CheckConnect(req_packet->id, m_peer.GetId(), this))
	{
		OnSendError(ERROR_CONNECT_USER);
	}
	else
	{
		DBManager::GetInstance()->
		//db�� �˻��غ��� ������ �����̰� ������ ���а���
//		m_peer.Send();
	}
}
