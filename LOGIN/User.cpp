#include "stdafx.h"
#include "User.h"
#include "UserContainer.h"
#include "DBManager.h"
#include "dbDefine.h"
#include "LoginMatching.h"
#include "LoginDlg.h"

User::User()
{
	m_packetProcess = std::bind(&User::PacketProcess, std::ref(*this), std::placeholders::_1);
	//ZeroMemory(m_userid, sizeof(m_userid));
}


User::~User()
{
}

void User::PacketProcess(BTZPacket* packet)
{
	switch (packet->packet_id)
	{
	case PACKET_ID_LOGIN_REQ:
		IsLogin(packet);
		break;
	case PACKET_ID_SIGNUP_REQ:
		IsSignUp(packet);
		break;
	case PACKET_ID_MOVE_SERVER_REQ:
		MoveServer(packet);
		break;
	case PACKET_ID_CLIENT_JOIN: // 로그인 서버에 이동으로 접속했는가, 최초접속했는가?
		ClientJoin(packet);
		break;
	case PACKET_ID_MATCHING_REQ: //매칭 신청
		break;
	case PACKET_ID_MATCHING_RES:
		break;
	default:
		break;
	}
}

void User::ClientJoin(BTZPacket * packet)
{
	CLIENT_JOIN_PACKET* join_packet = (CLIENT_JOIN_PACKET*)packet;

	if (join_packet->server_join) // 서버 이동으로 옴
	{
		UserContainer::GetInstance()->InvChiperGUID(join_packet->guid);
	}
	else // 최초 접속
	{
		UserContainer::GetInstance()->GiveGUID(this->m_userid);
		memcpy(&join_packet->guid, &m_userid, sizeof(m_userid));
		Send(join_packet);
	}
}

void User::IsLogin(BTZPacket * packet)
{
	LOGIN_REQ_PACKET* req_packet = (LOGIN_REQ_PACKET*)packet;

	if (UserContainer::GetInstance()->CheckConnect(req_packet->id, __super::GetID(), this))
	{
		OnSendError(ERROR_CONNECT_USER);
	}
	else
	{
		DBManager::GetInstance()->SingIn(req_packet->id, req_packet->pw, \
			[&](DWORD result) {OnLogin(result); });
	}
}

void User::IsSignUp(BTZPacket * packet)
{
	SIGNUP_REQ_PACKET* req_packet = (SIGNUP_REQ_PACKET*)packet;

	DBManager::GetInstance()->SignUp(req_packet->id, req_packet->pw, req_packet->nickname, req_packet->sex,\
		[&](DWORD result) {OnSignUp(result); });
}

void User::MoveServer(BTZPacket* packet)
{
	MOVE_SERVER_REQ_PACKET* move_packet = (MOVE_SERVER_REQ_PACKET*)packet;

	if (move_packet->server != INGAME_SERVER) // 나중에 매칭 서버로 바꿀 것
	{
		this->OnSendError(ERROR_SERVER_MOVE_ERROR);
		return;
	}

	MOVE_SERVER_RES_PACKET res_packet;
	res_packet.packet_id = PACKET_ID_MOVE_SERVER_RES;
	res_packet.packet_size = sizeof(res_packet);
	res_packet.server = move_packet->server;
	strcpy_s(res_packet.server_ip, INGAME_SERVER_IP);
	res_packet.server_port = INGAME_SERVER_PORT;

	__super::Send(&res_packet);
}

void User::MatchRequest(BTZPacket * packet)
{
	MATCHING_COMPLETE* match_packet = (MATCHING_COMPLETE*)packet;

	LoginMatching::GetInstance()->MatchingRequest(*this);
	LoginMatching::GetInstance()->SetMatchNum(LoginDlg::GetInstance()->GetMatchNum());
}

void User::OnLogin(DWORD sql)
{
	SQL_SIGNIN_ID* result = (SQL_SIGNIN_ID*)sql;

	if (result->res.m_state == SMySqlManager::RES_ENUM::SUCESS)
	{
		LOGIN_RES_PACKET packet;
		packet.packet_id = PACKET_ID_LOGIN_RES;
		packet.packet_size = sizeof(packet);
		__super::Send(&packet);
	}
	else
	{
		OnSendError(ERROR_NO_USER);
	}

}

void User::OnSignUp(DWORD result)
{
	if (result == SMySqlManager::RES_ENUM::SUCESS)
	{
		SIGNUP_RES_PACKET packet;
		packet.packet_id = PACKET_ID_SIGNUP_RES;
		packet.packet_size = sizeof(packet);
		packet.IsSucess = result;
		__super::Send(&packet);
	}
	else if(result == SMySqlManager::RES_ENUM::OVERLAP_VALUE)
	{
		OnSendError(ERROR_OVERLAP); // 회원가입 정보가 잘못됨
	}
	else
	{

	}
}

void User::OnSendError(DWORD error)
{
	ERR_PACKET packet;
	packet.packet_id = PACKET_ID_ERR;
	packet.packet_size = sizeof(packet);
	packet.errcode = error;

	__super::Send(&packet);
}

