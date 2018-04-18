#pragma once

#include "SMySqlManager.h"

#define DB_HOST "127.0.0.1"
#define DB_ID "n_sin"
#define DB_PW "sky59835"

struct SQL_CHECK_ID_RES
{
	char nickname[20];
	bool sex;
	char lasttime[20];
};

struct SQL_CHECK_ID
	:public BTZ_SQL
{
	char id[20];
	char pw[20];

	SQL_CHECK_ID_RES res;
};

#define DM_SIGNUP WM_USER + 1000
#define DM_SGININ WM_USER + 1001