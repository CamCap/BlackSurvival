#include "stdafx.h"
#include "UserContainer.h"
#include "Shlwapi.h"


template<> UserContainer* SSingleton<UserContainer>::ms_singleton = 0;

UserContainer::UserContainer()
{
	for (int i = 0; i < USER_LENGTH; i++) {
		m_user[i] = new User;
		m_container.PushWaitPeer(m_user[i]);
	}

	char path[MAX_PATH];
//	std::string path;
	GetModuleFileNameA(NULL, path, MAX_PATH);

	PathRemoveFileSpecA(path);
	std::string  file(path);
	file += "\\key.txt";
	m_auth.Set_AES128_CipherKey(file);

	CreateGUIDSerial();
}


UserContainer::~UserContainer()
{
}

bool UserContainer::CheckConnect(std::string name, int id, User * puser)
{
	User* pElement = this->Find(id);

	if (pElement == NULL) return true;
	//중복이 있다는건데...
	
	//중복이 없으면 어쩌지????

	return false;
}

void UserContainer::GiveGUID(GUID& id)
{
	CoCreateGuid(&id);
}

void UserContainer::InvChiperGUID(GUID & id)
{
	unsigned char array_id[4][4];


	memcpy(array_id[0], &id.Data1, sizeof(id.Data1));
	memcpy(array_id[1], &id.Data2, sizeof(id.Data2));
	memcpy(&array_id[1][2], &id.Data3, sizeof(id.Data3));

	char _state[4];
	memcpy(_state, id.Data4, sizeof(_state));
	memcpy(array_id[2], _state, sizeof(_state));

	memcpy(_state, &id.Data4[4], sizeof(_state));
	memcpy(array_id[3], _state, sizeof(_state));

	m_auth.AES128_InvCipher(array_id);

	memcpy(&id.Data1, array_id[0], sizeof(id.Data1));
	memcpy(&id.Data2, array_id[1], sizeof(id.Data2));
	memcpy(&id.Data3, array_id[2], sizeof(id.Data3));
	memcpy(&id.Data4, array_id[3], sizeof(id.Data4));
}

//
//unsigned char XOR_OPERATOR(unsigned char num[], int size)
//{
//	if (size == 0) return num[size] ^= num[size+1];
//
//	size--;
//
//	return XOR_OPERATOR(num, size);
//}


bool UserContainer::AuthAES128(unsigned char id[4][4])
{
	 m_auth.AES128_InvCipher(id);

	 unsigned char result = 0;

	 for (int i = 0; i < 50; i++)
	 {
		 _break:
		 for (int j = 0; j < 4; j++)
		 {
			 for (int k = 0; k < 4; k++)
			 {
				 result ^= id[j][k] ^= m_authSerial[i][j][k];

				 if (result != 0) {
					 i++;
					 goto _break;
				 }
			 }
		 }

		 if (result == 0) return true;
	 }

	return false;
}

void UserContainer::CreateGUIDSerial()
{
	char path[MAX_PATH];
	//	std::string path;
	GetModuleFileNameA(NULL, path, MAX_PATH);

	PathRemoveFileSpecA(path);
	std::string file(path);
	file += "\\guid_serial.txt";

	File guid_file;
	bool result = guid_file(file, std::ios::trunc);

	GUID guid; 
	unsigned char state[4][4];

	for(int i = 0 ; i < 50 ; i++)
	{
		CoCreateGuid(&guid);

		memcpy(state[0], &guid.Data1, sizeof(guid.Data1));
		memcpy(state[1], &guid.Data2, sizeof(guid.Data2));
		memcpy(&state[1][2], &guid.Data3, sizeof(guid.Data3));

		char _state[4];
		memcpy(_state, guid.Data4, sizeof(_state));
		memcpy(state[2], _state, sizeof(_state));

		memcpy(_state, &guid.Data4[4], sizeof(_state));
		memcpy(state[3], _state, sizeof(_state));
	
		guid_file << state;
		guid_file << std::endl<char, std::char_traits<char>>;
	}

	for (int i = 0; i < 50; i++)
	{
		guid_file >> state;

		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				m_authSerial[i][j][k] = state[j][k];
			}
		}
	}
}
