#pragma once
#include "SRoomMatch.h"
#include "SSingleton.h"

class LoginMatching
	:public SMatchingManager, public SSingleton<LoginMatching>
{
public:
	LoginMatching();
	~LoginMatching();

private:
};

