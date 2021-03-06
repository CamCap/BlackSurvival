#pragma once
#include "SIOCP.h"
#include "SSingleton.h"

class LoginIOCP
	:public SSingleton<LoginIOCP>
{
public:
	LoginIOCP();
	~LoginIOCP();

	bool CreateIOCP() { return m_iocp.CreateIOCP(LOGIN_SERVER_IP, LOGIN_SERVER_PORT); }
	void CleanUp() { m_iocp.CleanUp(); }


	bool RegisterCompletionPort(SOCKET socket, SPeer* context) { return m_iocp.RegisterCompletionPort(socket, context); }
	bool GetCompletionStatus(LPDWORD pdwOutBytesTransferred, ULONG_PTR* pOutCompletionKey, WSAOVERLAPPED** pOutOverlapped, \
		int* pErrCode = NULL, DWORD dwWaitingTime = INFINITE) {
		return m_iocp.GetCompletionStatus(pdwOutBytesTransferred, pOutCompletionKey, pOutOverlapped, pErrCode, dwWaitingTime);
	}
	bool PostCompletionStatus(DWORD CompleitonKey, DWORD dwBytesTransferred = 0, WSAOVERLAPPED* pOverlapped = NULL) { return m_iocp.PostCompletionStatus(CompleitonKey, dwBytesTransferred, pOverlapped); }

	void SetRoutinue(SIOCP::IOCPAccept accept, SIOCP::IOCPWork work, SIOCP::IOCPDisconnect disconnect) {
		m_iocp.m_RoutinueAccept = accept; m_iocp.m_RoutinueWork = work; m_iocp.m_RoutinueDisconnect = disconnect;
	}
private:
	SIOCP m_iocp;
};

