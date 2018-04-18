#pragma once
#include "SDBManager.h"
#include "SSingleton.h"

class DBManager
	:public SSingleton<DBManager>
{
public:
	DBManager();
	~DBManager();

	void DBProcess(BTZ_SQL* sql, DWORD wParam, DWORD lParam);

	bool SingIn(char* id, char pw);
	void SignUp(char* id, char pw, char* nickname, bool sex);

private:
	SDBManager m_db;
};

