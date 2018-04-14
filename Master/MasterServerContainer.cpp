#include "stdafx.h"
#include "MasterServerContainer.h"

template<> MasterServerContainer* SSingleton<MasterServerContainer>::ms_singleton = 0;

MasterServerContainer::MasterServerContainer()
	:m_container()
{
	Server* pServer;

	for (int i = 0; i < SERVER_SIZE; i++)
	{
		pServer = &m_server[i];
		m_container.PushServer(pServer);
	}
}


MasterServerContainer::~MasterServerContainer()
{
}
