#pragma once

#include "SMySqlManager.h"

#define DB_HOST L"N_BlackSurvival"
#define DB_ID L"n_sin"
#define DB_PW L"sky59835"

struct SQL_SIGNIN_RES
{
	char nickname[20];
	bool sex;

	int m_state;
};

struct SQL_SIGNIN_ID
	:public BTZ_SQL
{
	char id[20];
	char pw[20];

	SQL_SIGNIN_RES res;
};

#define DM_SIGNUP WM_USER + 1000
#define DM_SIGNIN WM_USER + 1001