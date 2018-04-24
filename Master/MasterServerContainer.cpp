#include "stdafx.h"
#include "MasterServerContainer.h"

template<> MasterServerContainer* SSingleton<MasterServerContainer>::ms_singleton = 0;

MasterServerContainer::MasterServerContainer()
	:m_container()
{
	for (int i = 0; i < SERVER_SIZE; i++) {
		m_server[i] = new Server;
		m_container.PushWaitPeer(m_server[i]);
	}
}


MasterServerContainer::~MasterServerContainer()
{
}
