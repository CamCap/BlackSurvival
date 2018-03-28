#include <stdio.h>
#include "IOCP.h"
#include "GameMessage.h"
//#pragma commit(lib, "")

int main()
{
	IOCP::GetInstance()->CreateIOCP();
	GameMessageManager::Instnace()->GameMsgLoop(NULL);
}