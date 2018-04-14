#include "stdafx.h"
#include "IOCP.h"

template<> IOCP* SSingleton<IOCP>::ms_singleton = 0;

IOCP::IOCP()
{
	m_iocp = new SIOCP;
}


IOCP::~IOCP()
{
	SAFE_DELETE(m_iocp);
}
