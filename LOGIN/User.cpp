#include "stdafx.h"
#include "User.h"
#include "UserContainer.h"
#include "DBManager.h"
#include "dbDefine.h"

User::User()
{
	m_peer.m_packetProcess = std::bind(&User::PacketProcess, std::ref(*this), std::placeholders::_1);
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
	default:
		break;
	}
}

void User::IsLogin(BTZPacket * packet)
{
	LOGIN_REQ_PACKET* req_packet = (LOGIN_REQ_PACKET*)packet;

	if (UserContainer::GetInstance()->CheckConnect(req_packet->id, m_peer.GetId(), this))
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

void User::OnLogin(DWORD sql)
{
	SQL_SIGNIN_ID* result = (SQL_SIGNIN_ID*)sql;

	if (result->res.m_state == SMySqlManager::RES_ENUM::SUCESS)
	{
		LOGIN_RES_PACKET packet;
		packet.packet_id = PACKET_ID_LOGIN_RES;
		packet.packet_size = sizeof(packet);
		m_peer.Send(&packet);
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
		m_peer.Send(&packet);
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

	m_peer.Send(&packet);
}

