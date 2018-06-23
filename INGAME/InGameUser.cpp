#include "stdafx.h"
#include "InGameUser.h"
#include <functional>
#include "InGamePacket.h"
#include "InGameUserContainer.h"
#include "InGameMatching.h"

InGameUser::InGameUser()
{
	m_packetProcess = std::bind(&InGameUser::PacketProcess, std::ref(*this), std::placeholders::_1);
}


InGameUser::~InGameUser()
{
}

void InGameUser::PacketProcess(BTZPacket* packet)
{
	switch (packet->packet_id)
	{
	case PACKET_ID_CLIENT_JOIN:
		MoveServer(packet);
		break;
	case PACKET_ID_MATCHING_REQ:
		Matching(packet);
		break;
	default:
		break;
	}
}

void InGameUser::Matching(BTZPacket * packet)
{
	MATCHING_PACKET* match_packet = (MATCHING_PACKET*)packet;

	InGameMatching::GetInstance()->MatchingRequest(*this, match_packet->room_id, match_packet->matchnum);
}

void InGameUser::MoveServer(BTZPacket* packet)
{
	CLIENT_JOIN_PACKET* join_packet = (CLIENT_JOIN_PACKET*)packet;
	//join_packet->server_join
	InGameUserContainer::GetInstance()->InvChiperGUID(join_packet->user_id);

	m_guid = join_packet->user_id;
}
