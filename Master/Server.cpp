#include "stdafx.h"
#include "Server.h"


BOOL Server::InitServer(unsigned short id, std::string name, SERVERTYPE type)
{
	m_id = id;
	m_name = name;
	m_type = type;

	return 0;
}

Server::Server()
	:m_type(SERVERTYPE::NONE)
{
	m_id = -1;
}


Server::~Server()
{
}
