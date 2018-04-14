#pragma once
#include "SSingleton.h"


class LoginDlg
	:public SSingleton<LoginDlg>
{
public:
	LoginDlg();
	~LoginDlg();
};

