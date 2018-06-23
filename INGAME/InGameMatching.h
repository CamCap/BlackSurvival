#pragma once
#include "SRoomMatch.h"
#include "SSingleton.h"

class InGameMatching
	:public SMatchingManager, public SSingleton<InGameMatching>
{
public:
	InGameMatching();
	~InGameMatching();
};

