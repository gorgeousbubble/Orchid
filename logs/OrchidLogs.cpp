/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Gorgeous Bubble, alopex
*     All rights reserved.
*
* @proj     Orchid
* @file		OrchidLogs.cpp
* @brief	The Orchid C/C++ Component Collection Project.
* @author	alopex
* @version	v1.00a
* @date		2019-10-16
*/
#include "OrchidLogs.h"

#pragma warning(disable : 4996)

using namespace std;

void ORCHIDLOGS_CALLMETHOD COrchidLogs::GetComputerNames()
{
	char *pArr = nullptr;
	DWORD dwSize = MAX_COMPUTERNAME_LENGTH;

	pArr = new char[MAX_COMPUTERNAME_LENGTH + 1];
	memset(pArr, 0, sizeof(pArr));

	::GetComputerNameA(pArr, &dwSize);

	char chLogFile[MAX_PATH] = {0};
	GetLogFilePath(chLogFile, MAX_PATH);

	ofstream fout(chLogFile, ios::app);
	fout.seekp(ios::end);
	fout << "Computer Name: " << pArr << endl;
	fout.close();

	delete[] pArr;
	pArr = nullptr;
}

void ORCHIDLOGS_CALLMETHOD COrchidLogs::GetUserNames()
{
	char *pArr = nullptr;
	DWORD dwSize = MAX_PATH;

	pArr = new char[MAX_PATH + 1];
	memset(pArr, 0, sizeof(pArr));

	::GetUserNameA(pArr, &dwSize);

	char chLogFile[MAX_PATH] = {0};
	GetLogFilePath(chLogFile, MAX_PATH);

	ofstream fout(chLogFile, ios::app);
	fout.seekp(ios::end);
	fout << "User Name: " << pArr << endl;
	fout.close();

	delete[] pArr;
	pArr = nullptr;
}

void ORCHIDLOGS_CALLMETHOD COrchidLogs::GetWindowsVersions()
{
	char *pVision = NULL;
	SYSTEM_INFO Info;
	OSVERSIONINFOEX Os;

	::GetSystemInfo(&Info);
	Os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

	pVision = (char *)"Unknown OperatingSystem";

	if (GetVersionExW((OSVERSIONINFO *)&Os))
	{
		switch (Os.dwMajorVersion)
		{
		case 4:
			switch (Os.dwMinorVersion)
			{
			case 0:
				if (Os.dwPlatformId == VER_PLATFORM_WIN32_NT)
				{
					pVision = (char *)"Microsoft Windows NT 4.0";
				}
				else if (Os.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS)
				{
					pVision = (char *)"Microsoft Windows 95";
				}
				break;
			case 10:
				pVision = (char *)"Microsoft Windows 98";
				break;
			case 90:
				pVision = (char *)"Microsoft Windows Me";
				break;
			}
			break;

		case 5:
			switch (Os.dwMinorVersion)
			{
			case 0:
				pVision = (char *)"Microsoft Windows 2000";
				break;
			case 1:
				pVision = (char *)"Microsoft Windows XP";
				break;

			case 2:
				if (Os.wProductType == VER_NT_WORKSTATION && Info.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
				{
					pVision = (char *)"Microsoft Windows XP Professional x64 Edition";
				}
				else if (GetSystemMetrics(SM_SERVERR2) == 0)
				{
					pVision = (char *)"Microsoft Windows Server 2003";
				}
				else if (GetSystemMetrics(SM_SERVERR2) != 0)
				{
					pVision = (char *)"Microsoft Windows Server 2003 R2";
				}
				break;
			}
			break;

		case 6:
			switch (Os.dwMinorVersion)
			{
			case 0:
				if (Os.wProductType == VER_NT_WORKSTATION)
				{
					pVision = (char *)"Microsoft Windows Vista";
				}
				else
				{
					pVision = (char *)"Microsoft Windows Server 2008";
				}
				break;
			case 1:
				if (Os.wProductType == VER_NT_WORKSTATION)
				{
					pVision = (char *)"Microsoft Windows 7";
				}
				else
				{
					pVision = (char *)"Microsoft Windows Server 2008 R2";
				}
				break;
			case 2:
				if (Os.wProductType == VER_NT_WORKSTATION)
				{
					pVision = (char *)"Microsoft Windows 8";
				}
				else
				{
					pVision = (char *)"Microsoft Windows Server 2012";
				}
				break;
			case 3:
				if (Os.wProductType == VER_NT_WORKSTATION)
				{
					pVision = (char *)"Microsoft Windows 8.1";
				}
				else
				{
					pVision = (char *)"Microsoft Windows Server 2012 R2";
				}
				break;
			}
			break;

		case 10:
			switch (Os.dwMinorVersion)
			{
			case 0:
				if (Os.wProductType == VER_NT_WORKSTATION)
				{
					pVision = (char *)"Microsoft Windows 10";
				}
				else
				{
					pVision = (char *)"Microsoft Windows Server 2016 Technical Preview";
				}
				break;
			}
			break;
		}
	}

	char chLogFile[MAX_PATH] = {0};
	GetLogFilePath(chLogFile, MAX_PATH);

	ofstream fout(chLogFile, ios::app);
	fout.seekp(ios::end);
	fout << "Windows Vision: " << pVision << endl;
	fout.close();
}

void ORCHIDLOGS_CALLMETHOD COrchidLogs::GetLogFilePath(char *pStr, int nSize)
{
	char chLogFilePath[MAX_PATH] = {0};
	char chLogFileName[MAX_PATH] = {0};
	char chLogNameArr[MAX_PATH] = {0};
	char *pTemp = NULL;
	SYSTEMTIME syTime = {0};

	GetLocalTime(&syTime);
	GetModuleFileNameA(NULL, chLogFilePath, sizeof(chLogFilePath));
	pTemp = strrchr(chLogFilePath, '\\');
	if (pTemp != NULL)
	{
		strcpy_s(chLogFileName, pTemp + 1);
		*pTemp = '\0';
	}

	for (pTemp = strrchr(chLogFileName, '.'); pTemp != (chLogFileName + MAX_PATH - 1); ++pTemp)
	{
		*pTemp = '\0';
	}

	_snprintf_s(chLogNameArr, sizeof(chLogNameArr), "\\log\\%s_RuntimeLog_%d_%02d_%02d.log", chLogFileName, syTime.wYear, syTime.wMonth, syTime.wDay);
	strcat_s(chLogFilePath, chLogNameArr);

	memset(pStr, 0, nSize);
	memcpy_s(pStr, nSize, chLogFilePath, strlen(chLogFilePath));
}

void ORCHIDLOGS_CALLMETHOD COrchidLogs::CreateLogFilePath()
{
	char chModuleFilePath[MAX_PATH] = {0};
	char *pModuleName = NULL;
	char *pTemp = NULL;
	int nSize = 0;

	// Get module path
	GetModuleFileNameA(NULL, chModuleFilePath, sizeof(chModuleFilePath));

	// Get module name
	pTemp = strrchr(chModuleFilePath, '\\') + 1;
	nSize = strlen(pTemp) + 1;
	pModuleName = new char[nSize];
	memset(pModuleName, 0, nSize);
	memcpy_s(pModuleName, nSize, pTemp, strlen(pTemp));

	// Delete module surfix
	for (pTemp = strrchr(pModuleName, '.'); pTemp != (pModuleName + nSize - 1); ++pTemp)
	{
		*pTemp = '\0';
	}

	// Get last path
	for (pTemp = strrchr(chModuleFilePath, '\\'); pTemp != &chModuleFilePath[MAX_PATH - 1]; ++pTemp)
	{
		*pTemp = '\0';
	}

	// Get system time now
	char chLogDirArr[MAX_PATH] = {0};
	char chLogNameArr[MAX_PATH] = {0};
	SYSTEMTIME syTime = {0};

	GetLocalTime(&syTime);
	_snprintf_s(chLogDirArr, sizeof(chLogDirArr), "%s\\log", chModuleFilePath);
	_snprintf_s(chLogNameArr, sizeof(chLogNameArr), "%s\\log\\%s_RuntimeLog_%d_%02d_%02d.log", chModuleFilePath, pModuleName, syTime.wYear, syTime.wMonth, syTime.wDay);

	// Check file folder exist
	if (!PathFileExistsA(chLogDirArr))
	{
		CreateDirectoryA(chLogDirArr, NULL);
	}

	// Create log files
	FILE *fp = NULL;

	fopen_s(&fp, chLogNameArr, "w");
	if (fp == NULL)
	{
		CreateDirectoryA(chLogDirArr, NULL);
		fopen_s(&fp, chLogNameArr, "w");
		if (fp == NULL)
		{
			delete[] pModuleName;
			pModuleName = NULL;
			return;
		}
	}

	fclose(fp);

	// Seek log files
	ofstream fout(chLogNameArr, ios::app);
	fout.seekp(ios::end);
	fout << pModuleName << " RuntimeLog File." << endl;
	fout << endl;
	fout << "[INFO]" << endl;
	fout.close();

	delete[] pModuleName;
	pModuleName = NULL;

	GetComputerNames();
	GetUserNames();
	GetWindowsVersions();

	ofstream fout1(chLogNameArr, ios::app);
	fout1.seekp(ios::end);
	fout1 << endl;
	fout1 << "[FORMAT]" << endl;
	fout1 << "Log Format:[Current Time][Process ID][Thread ID]<File,Line>:..." << endl;
	fout1 << endl;
	fout1.close();
}

void ORCHIDLOGS_CALLMETHOD COrchidLogs::Write(LPCSTR file, LONG line, LPCSTR lpcstr, ...)
{
	SYSTEMTIME syCurrentTime = {0};
	DWORD dwProcessID = 0;
	DWORD dwThreadID = 0;

	::GetLocalTime(&syCurrentTime);
	dwProcessID = ::GetCurrentProcessId();
	dwThreadID = ::GetCurrentThreadId();

	char *pflie = const_cast<char *>(file);
	char *pTemp = NULL;

	if (strrchr((char *)pflie, '\\') != NULL)
	{
		pTemp = strrchr((char *)pflie, '\\') + 1;
	}
	else
	{
		pTemp = (char *)pflie;
	}

	char chLogFile[MAX_PATH] = {0};
	char chWriteArr[MAX_PATH] = {0};
	char chParasArr[MAX_PATH] = {0};

	GetLogFilePath(chLogFile, MAX_PATH);

	if (!PathFileExistsA(chLogFile))
	{
		CreateLogFilePath();
	}

	ofstream fout(chLogFile, ios::app);
	fout.seekp(ios::end);

	memset(chWriteArr, 0, sizeof(chWriteArr));
	_snprintf_s(chWriteArr, sizeof(chWriteArr), "[%d-%02d-%02d %02d:%02d:%02d.%03d][%d][%d]<%s Line:%d>:", syCurrentTime.wYear, syCurrentTime.wMonth, syCurrentTime.wDay, syCurrentTime.wHour, syCurrentTime.wMinute, syCurrentTime.wSecond, syCurrentTime.wMilliseconds, dwProcessID, dwThreadID, pTemp, line);
	fout << chWriteArr;

	va_list arg_ptr;

	va_start(arg_ptr, lpcstr);
	memset(chParasArr, 0, sizeof(chParasArr));
	_vsnprintf(chParasArr, sizeof(chParasArr), lpcstr, arg_ptr);
	fout << chParasArr;
	va_end(arg_ptr);

	fout.close();
}

void ORCHIDLOGS_CALLMETHOD COrchidLogs::WriteLine(LPCSTR file, LONG line, LPCSTR lpcstr, ...)
{
	SYSTEMTIME syCurrentTime = {0};
	DWORD dwProcessID = 0;
	DWORD dwThreadID = 0;

	::GetLocalTime(&syCurrentTime);
	dwProcessID = ::GetCurrentProcessId();
	dwThreadID = ::GetCurrentThreadId();

	char *pflie = const_cast<char *>(file);
	char *pTemp = NULL;

	if (strrchr((char *)pflie, '\\') != NULL)
	{
		pTemp = strrchr((char *)pflie, '\\') + 1;
	}
	else
	{
		pTemp = (char *)pflie;
	}

	char chLogFile[MAX_PATH] = {0};
	char chWriteArr[MAX_PATH] = {0};
	char chParasArr[MAX_PATH] = {0};

	GetLogFilePath(chLogFile, MAX_PATH);

	if (!PathFileExistsA(chLogFile))
	{
		CreateLogFilePath();
	}

	ofstream fout(chLogFile, ios::app);
	fout.seekp(ios::end);

	memset(chWriteArr, 0, sizeof(chWriteArr));
	_snprintf_s(chWriteArr, sizeof(chWriteArr), "[%d-%02d-%02d %02d:%02d:%02d.%03d][%d][%d]<%s Line:%d>:", syCurrentTime.wYear, syCurrentTime.wMonth, syCurrentTime.wDay, syCurrentTime.wHour, syCurrentTime.wMinute, syCurrentTime.wSecond, syCurrentTime.wMilliseconds, dwProcessID, dwThreadID, pTemp, line);
	fout << chWriteArr;

	va_list arg_ptr;

	va_start(arg_ptr, lpcstr);
	memset(chParasArr, 0, sizeof(chParasArr));
	_vsnprintf(chParasArr, sizeof(chParasArr), lpcstr, arg_ptr);
	fout << chParasArr << endl;
	va_end(arg_ptr);

	fout.close();
}