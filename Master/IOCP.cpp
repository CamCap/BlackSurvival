#include "stdafx.h"
#include "IOCP.h"


IOCP::IOCP()
{
	m_iocp = new SIOCP;
}


IOCP::~IOCP()
{
	SAFE_DELETE(m_iocp);
}
