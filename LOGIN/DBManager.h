#pragma once
#include "SDBManager.h"
#include "SSingleton.h"

class DBManager
	:public SSingleton<DBManager>
{
	using DB_CallBack = std::function<void(DWORD)>;

	struct ResDB
	{
		BTZ_SQL sql;
		DB_CallBack callback;
	};

public:
	DBManager();
	~DBManager();

	void DBProcess(BTZ_SQL* sql, ResSql& res_sql, DWORD error);

	void SingIn(char* id, char* pw, DB_CallBack callback);
	void SignUp(char* id, char* pw, char* nickname, bool sex, DB_CallBack callback = NULL);
	//void Update
protected:
	void SignUpProcess(BTZ_SQL* sql, ResSql& res_sql, int error);
	void SignInProcess(BTZ_SQL* sql, ResSql& res_sql, int error);

private:
	SDBManager m_db;

	ListContainer<ResDB> m_listRes;
};

