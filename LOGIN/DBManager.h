#pragma once
#include "SDBManager.h"
#include "SSingleton.h"

class DBManager
	:public SDBManager, SSingleton<DBManager>
{
public:
	DBManager();
	~DBManager();

	void DBProcess(BTZ_SQL* sql, DWORD wParam, DWORD lParam);
};

