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
	BOOL CreateIOCP() { return m_iocp->CreateIOCP(); }
	void CleanUp() { m_iocp->CleanUp(); }


	BOOL RegisterCompletionPort(SOCKET socket, SPeer* context) { return m_iocp->RegisterCompletionPort(socket, context); }
	BOOL GetCompletionStatus(LPDWORD pdwOutBytesTransferred, ULONG_PTR* pOutCompletionKey, WSAOVERLAPPED** pOutOverlapped, \
		int* pErrCode = NULL, DWORD dwWaitingTime = INFINITE) {
		return m_iocp->GetCompletionStatus(pdwOutBytesTransferred, pOutCompletionKey, pOutOverlapped, pErrCode, dwWaitingTime);
	}
	BOOL PostCompletionStatus(DWORD CompleitonKey, DWORD dwBytesTransferred = 0, WSAOVERLAPPED* pOverlapped = NULL) { return m_iocp->PostCompletionStatus(CompleitonKey, dwBytesTransferred, pOverlapped); }
	
	void SetRoutinue(IOCPAccept accept, IOCPWork work, IOCPDisconnect disconnect){
		m_iocp->m_ThreadAccept = accept; m_iocp->m_ThreadWork = work; m_iocp->m_ThreadDisconnect = disconnect;
	}

private:
	SIOCP * m_iocp;
};

