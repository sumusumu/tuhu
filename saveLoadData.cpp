#include "stdafx.h"
#include "saveLoadData.h"


saveLoadData::saveLoadData()
{
}


saveLoadData::~saveLoadData()
{
}

void saveLoadData::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_F1))
	{
		write();
	}
	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		read();
	}

}

void saveLoadData::write(void)
{
	HANDLE file;

	char str[128] = "������ �����Ե��ϴ� �ɸ�";
	DWORD write;

	file = CreateFile("ġ��ġ��.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);

	WriteFile(file, str, strlen(str), &write, NULL);

	CloseHandle(file);


}

void saveLoadData::read(void)
{
	HANDLE file;

	char str[128];
	DWORD read;

	file = CreateFile("ġ��ġ��.txt", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);

	ReadFile(file, str, strlen(str), &read, NULL);

	CloseHandle(file);

	MessageBox(_hWnd, str, "º!", MB_OK);

}