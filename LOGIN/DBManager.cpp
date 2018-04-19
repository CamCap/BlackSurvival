#include "stdafx.h"
#include "DBManager.h"
#include "dbDefine.h"

template<> DBManager* SSingleton<DBManager>::ms_singleton = 0;

DBManager::DBManager()
{
	m_db.ConnectDBMS(DB_HOST, DB_ID, DB_PW);
	m_db.m_dbProcess = std::bind(&DBManager::DBProcess, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

DBManager::~DBManager()
{
}

void DBManager::DBProcess(BTZ_SQL* sql, DWORD wParam, DWORD lParam)
{
	switch (sql->sql_id)
	{
	case DM_SIGNUP:
	{
	}break;
	default:
		break;
	}
}

void DBManager::SignUp(char * id, char pw, char* nickname, bool sex)
{
	BTZ_SQL* sql = m_db.PopBtzSql();
	sql->sql_id = DM_SIGNUP;
	sprintf_s(sql->query, "insert into test_table value('%s', '%s', '%s', %d)", id, pw, nickname, sex);
	m_db.PushWaitSql(sql);

}
