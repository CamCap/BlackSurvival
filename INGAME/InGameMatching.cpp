#include "stdafx.h"
#include "InGameMatching.h"


template<> InGameMatching* SSingleton<InGameMatching>::ms_singleton = NULL;

InGameMatching::InGameMatching()
{
	this->CreateMatchingManager(new MatchCompleteBehavior);
}


InGameMatching::~InGameMatching()
{
}
