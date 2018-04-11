#include "stdafx.h"
#include "MasterServerContainer.h"


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
