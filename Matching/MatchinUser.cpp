#include "stdafx.h"
#include "MatchingUser.h"
#include "MatchingPacket.h"
#include "UserMatchingManager.h"

MatchUser::MatchUser()
{
	m_packetProcess = std::bind(&MatchUser::PacketProcess, std::ref(*this), std::placeholders::_1);
	//ZeroMemory(m_userid, sizeof(m_userid));
}


MatchUser::~MatchUser()
{
}

void MatchUser::PacketProcess(BTZPacket * packet)
{
	switch (packet->packet_id)
	{
	case PACKET_ID_MOVE_SERVER: // 서버이동으로 매칭 서버에 접속함
	{
		UserDataMove(packet);
		UserMatchingManager::GetInstance()->SetMatching(this);
	}break;
	case PACKET_ID_MATCHING:
	{

	}break;
	default:
		break;
	}
}

void MatchUser::MoveServer(BTZPacket * packet)
{
}

void MatchUser::UserDataMove(BTZPacket * packet)
{
	MOVE_SERVER_PACKET* move_packet = (MOVE_SERVER_PACKET*)packet;
	m_userid = move_packet->id;
	//다음에 머 추가할 데이터가 있다면...
}

void MatchUser::OnSendError(DWORD error)
{
	ERR_PACKET packet;
	packet.packet_id = PACKET_ID_ERR;
	packet.packet_size = sizeof(packet);
	packet.errcode = error;

	__super::Send(&packet);
}
