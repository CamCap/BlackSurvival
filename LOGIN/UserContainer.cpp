#include "stdafx.h"
#include "UserContainer.h"


template<> UserContainer* SSingleton<UserContainer>::ms_singleton = 0;

UserContainer::UserContainer()
{
	for (int i = 0; i < USER_LENGTH; i++) {
		m_user[i] = new User;
		m_container.PushWaitPeer(m_user[i]);
	}
}


UserContainer::~UserContainer()
{
}

bool UserContainer::CheckConnect(std::string name, int id, User * puser)
{
	User* pElement = this->Find(id);

	if (pElement == NULL) return true;
	//�ߺ��� �ִٴ°ǵ�...
	
	//�ߺ��� ������ ��¼��????

	return false;
}
