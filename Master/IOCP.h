#pragma once
#include "SIOCP.h"
#include "SSingleton.h"

class IOCP
	:public SSingleton<IOCP>
{
public:
	IOCP();
	~IOCP();

public:
	bool CreateIOCP() { return m_iocp->CreateIOCP(); }
	void CleanUp() { m_iocp->CleanUp(); }


	bool RegisterCompletionPort(SOCKET socket, SPeer* context) { return m_iocp->RegisterCompletionPort(socket, context); }
	bool GetCompletionStatus(LPDWORD pdwOutBytesTransferred, ULONG_PTR* pOutCompletionKey, WSAOVERLAPPED** pOutOverlapped, \
		int* pErrCode = NULL, DWORD dwWaitingTime = INFINITE) {
		return m_iocp->GetCompletionStatus(pdwOutBytesTransferred, pOutCompletionKey, pOutOverlapped, pErrCode, dwWaitingTime);
	}
	bool PostCompletionStatus(DWORD CompleitonKey, DWORD dwBytesTransferred = 0, WSAOVERLAPPED* pOverlapped = NULL) { return m_iocp->PostCompletionStatus(CompleitonKey, dwBytesTransferred, pOverlapped); }
	
	void SetRoutinue(IOCPAccept accept, IOCPWork work, IOCPDisconnect disconnect){
		m_iocp->m_RoutinueAccept = accept; m_iocp->m_RoutinueWork = work; m_iocp->m_RoutinueDisconnect = disconnect;
	}

private:
	SIOCP * m_iocp;
};

