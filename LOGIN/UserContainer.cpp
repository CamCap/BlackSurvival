#include "stdafx.h"
#include "UserContainer.h"


template<> UserContainer* SSingleton<UserContainer>::ms_singleton = 0;

UserContainer::UserContainer()
{
	for (int i = 0; i < USER_LENGTH; i++)
		m_container.PushWaitPeer(&m_user[i]);
}


UserContainer::~UserContainer()
{
}
