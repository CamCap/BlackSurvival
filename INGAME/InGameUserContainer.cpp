#include "stdafx.h"
#include "InGameUserContainer.h"


template<> InGameUserContainer* SSingleton<InGameUserContainer>::ms_singleton = 0;

InGameUserContainer::InGameUserContainer()
{
}


InGameUserContainer::~InGameUserContainer()
{
}

bool InGameUserContainer::CheckConnect(std::string name, int id, InGameUser * puser)
{
	return false;
}

void InGameUserContainer::InvChiperGUID(GUID & id)
{
}
