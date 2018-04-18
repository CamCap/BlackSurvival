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
		//db에 검색해보고 있으면 성공이고 없으면 실패겠지
//		m_peer.Send();
	}
}
