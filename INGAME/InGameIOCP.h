#pragma once
#include "SIocp.h"
#include "SSingleton.h"

class InGameIOCP
	:public SSingleton<InGameIOCP>, public SIOCP
{
public:
	InGameIOCP();
	~InGameIOCP();
private:

};

