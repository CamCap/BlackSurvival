#pragma once
#include "ssocket.h"
#include "LoginPacket.h"

struct BTZ_SQL;

class User
{
public:
	void InitPeer(SOCKET socket, SOCKADDR_IN addr, int userid) { m_peer.InitPeer(socket, addr, userid); }
	BOOL RecvPacket(int DwNumberBytes) { return m_peer.RecvPacket(DwNumberBytes); }
	void CheckSendPacket() { m_peer.CheckSendPacket(); }
	int GetID() { return m_peer.GetId(); }
	void PacketProcess(BTZPacket* packet);
	void RelaseUser() { m_peer.ReleaseSocket(); }
	std::string GetName() { return m_nickname; }

	void OnSendError(DWORD error);

	void OnLogin(DWORD sql);
	void OnSignUp(DWORD sql);

protected:
	void ClientJoin(BTZPacket* packet); // 이동에 의한접속
	void IsLogin(BTZPacket* packet); // 로그인 요청
	void IsSignUp(BTZPacket* sql); // 회원가입 요청
	void MoveServer(BTZPacket* packet); // 서버이동 요청

//	void UpdateSignInTime(BTZ_SQL* sql);
public:
	User();
	~User();

private:
	SPeer m_peer;

	std::string m_nickname;
	bool sex;

};

