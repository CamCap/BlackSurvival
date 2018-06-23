#include "stdafx.h"
#include "LoginMatching.h"

template<> LoginMatching* SSingleton<LoginMatching>::ms_singleton = NULL;

LoginMatching::LoginMatching()
{
	this->CreateMatchingManager(new MatchRequestBehavior);
}


LoginMatching::~LoginMatching()
{
}
