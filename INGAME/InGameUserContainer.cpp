#include "stdafx.h"
#include "InGameUserContainer.h"


template<> InGameUserContainer* SSingleton<InGameUserContainer>::ms_singleton = 0;

InGameUserContainer::InGameUserContainer()
{
}


InGameUserContainer::~InGameUserContainer()
{
}
