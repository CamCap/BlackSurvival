#include "stdafx.h"
#include "DBManager.h"
#include "dbDefine.h"
#include "GameMessage.h"
#include <comdef.h> 

template<> DBManager* SSingleton<DBManager>::ms_singleton = 0;

DBManager::DBManager()
	: m_listRes(10)
{
	m_db.ConnectDBMS((SQLWCHAR*)DB_HOST, (SQLWCHAR*)DB_ID, (SQLWCHAR*)DB_PW);
	m_db.m_dbProcess = std::bind(&DBManager::DBProcess, std::ref(*this), std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
}

DBManager::~DBManager()
{

}

void DBManager::DBProcess(BTZ_SQL* sql, ResSql& res_sql, DWORD error)
{
	switch (sql->sql_id)
	{
	case DM_SIGNUP:
	{
		SignUpProcess(sql, res_sql, error);
	}break;
	case DM_SIGNIN:
	{
		SignInProcess(sql, res_sql, error);
	}break;
	default:
		break;
	}
}

void DBManager::SingIn(char * id, char * pw, DB_CallBack callback)
{
	BTZ_SQL* sql = m_db.PopBtzSql();
	memset(sql, 0, sizeof(BTZ_SQL));
	sql->sql_id = DM_SIGNIN;

//	sprintf_s(sql->query, "select nickname, sex from test_table where id ='%s' && pw ='%s';", id, pw);
	sprintf_s(sql->query, "call sign_in('%s', '%s');", id, pw);
	m_db.PushWaitSql(sql);

	ResDB* res = m_listRes.pop();
	res->callback = callback;
	memcpy(&res->sql, sql, sizeof(BTZ_SQL));
	m_listRes.push(res);
}

void DBManager::SignUp(char * id, char* pw, char* nickname, bool sex, DB_CallBack callback)
{
	BTZ_SQL* sql = m_db.PopBtzSql();
	memset(sql, 0, sizeof(BTZ_SQL));
	sql->sql_id = DM_SIGNUP;
	//sprintf_s(sql->query, "insert into test_table(id,pw,nickname,sex) values('%s', '%s', '%s', %d);", id, pw, nickname, sex);
	sprintf_s(sql->query, "call sign_up('%s', '%s', '%s', %d);", id, pw, nickname, sex);

	m_db.PushWaitSql(sql);

	ResDB* res = m_listRes.pop();
	res->callback = callback;
	memcpy(&res->sql, sql, sizeof(BTZ_SQL));
	m_listRes.push(res);
}


void DBManager::SignUpProcess(BTZ_SQL * sql, ResSql& result, int error)
{
	ResDB* resdb = m_listRes.pop();
	resdb = (resdb->sql.sql_id == sql->sql_id) ? resdb : m_listRes.find([&](ResDB* resdb)->bool {\
		return resdb->sql.sql_id == sql->sql_id; });

	if (error == SQL_ERROR || error < 0)
	{
		GameMessageManager::GetInstance()->SendGameMessage(GM_ERROR, result.m_state, NULL, NULL);
	}
	else if(resdb == NULL)
	{
		m_listRes.push(resdb);
	}

	if (resdb->callback != NULL)
		resdb->callback(error);
}

void DBManager::SignInProcess(BTZ_SQL * sql, ResSql& result, int error)
{
	SQL_SIGNIN_ID* res_sql = (SQL_SIGNIN_ID*)sql;

	ResDB* resdb = m_listRes.pop();
	resdb = (resdb->sql.sql_id == sql->sql_id) ? resdb : m_listRes.find([&](ResDB* resdb)->bool {\
		return resdb->sql.sql_id == sql->sql_id; });

	if (error == SQL_ERROR || error < 0)
	{
		GameMessageManager::GetInstance()->SendGameMessage(GM_ERROR, result.m_state, NULL, NULL);
	}
	else
	{
		strcpy_s(res_sql->res.nickname, result.m_col[0]);
		res_sql->res.sex = result.m_col[1];
	}

	res_sql->res.m_state = error;

	if(resdb->callback != NULL)
		resdb->callback((DWORD)res_sql);
}

