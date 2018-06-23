#include "stdafx.h"
#include "UserMatchingManager.h"
#include "Shlwapi.h"
#include "MatchingPacket.h"

UserMatchingManager::UserMatchingManager()
	:matchnum(MAX_MATCH_USER), m_roomContainer(MAX_MATCH_ROOM)
{
	m_event = CreateEvent(NULL, TRUE, FALSE, NULL);

	m_threadHandle = std::thread([&]() { MatchingLoop(NULL); });
}


UserMatchingManager::~UserMatchingManager()
{
	CloseHandle(m_event); m_event = NULL;

	m_threadHandle.detach();
}

bool UserMatchingManager::CheckConnect(std::string name, int id, MatchUser* puser)
{
	MatchUser* pElement = this->Find(id);

	if (pElement == NULL) return true;

	return false;
}

void UserMatchingManager::GiveGUID(unsigned char id[4][4])
{
	GUID guid;
	CoCreateGuid(&guid);

	memcpy(id[0], &guid.Data1, sizeof(guid.Data1));
	memcpy(id[1], &guid.Data2, sizeof(guid.Data2));
	memcpy(&id[1][2], &guid.Data3, sizeof(guid.Data3));

	char _state[4];
	memcpy(_state, guid.Data4, sizeof(_state));
	memcpy(id[2], _state, sizeof(_state));

	memcpy(_state, &guid.Data4[4], sizeof(_state));
	memcpy(id[3], _state, sizeof(_state));
}

//////////////////////////////////////////////////////////////////

void UserMatchingManager::SetMatching(MatchUser* puser)
{
}


void UserMatchingManager::SetMatchNum(int num)
{
	this->matchnum = num;
}

//////////////////////////////////////////////////

void Room::Function(int num)
{
	MATCHING_PACKET packet;

	packet.packet_id = PACKET_ID_MATCHING;
	packet.packet_size = sizeof(packet);

	CoCreateGuid(&packet.room_id);

	for (int i = 0; i < num; i++)
	{
		Users[i]->Send(&packet);
	}
}


///////////////////////////////////////////////////////////


void UserMatchingManager::WaitEvent()
{
	if (m_event != NULL)
		WaitForSingleObject(m_event, 100); // 1/1000초만큼 대기
}

void UserMatchingManager::SetEvent()
{
	if (m_event != NULL)
		::SetEvent(m_event); // signal 상태로 변경
}

void UserMatchingManager::ResetEvent()
{
	if (m_event != NULL)
		::ResetEvent(m_event); // non-signal 상태로 변경
}

Room* UserMatchingManager::IsMathching()
{
	while (1)
	{
		if (m_waitUsers.ActivePeerNum() > matchnum) // 들어오자마자 검사하는 꼴이군..이건 별로 좋지않은 것같은데..
			break;
		else
		{
			ResetEvent();
			WaitEvent();
		}
	}

	Room* room = m_roomContainer.pop();

	if (room == NULL)
	{
		room = new Room;
		m_roomContainer.push(room);
	}

	return room;
}

DWORD WINAPI UserMatchingManager::MatchingLoop(LPVOID pArg)
{
	Room* room = NULL;

	while (1)
	{
		if ((room = UserMatchingManager::GetInstance()->IsMathching()) != NULL)
		{
			if (room == NULL) continue;

			for (int i = 0; i < matchnum; i++)
				room->Users[i] = UserMatchingManager::GetInstance()->m_waitUsers.PopActivePeer();

			room->Function(this->matchnum);

			UserMatchingManager::GetInstance()->m_roomContainer.push(room);
		}
	}

	ExitThread(0);

	return 0;
}
