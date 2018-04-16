#include "stdafx.h"
#include "DBManager.h"
#include "dbDefine.h"

template<> DBManager* SSingleton<DBManager>::ms_singleton = 0;

DBManager::DBManager()
{
	this->ConnectDBMS(DB_HOST, DB_ID, DB_PW);
	this->m_dbProcess = std::bind(&DBManager::DBProcess, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

DBManager::~DBManager()
{
}

void DBManager::DBProcess(BTZ_SQL* sql, DWORD wParam, DWORD lParam)
{
	switch (sql->sql_id)
	{
	default:
		break;
	}
}
