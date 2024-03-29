/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Gorgeous Bubble, alopex
*     All rights reserved.
*
* @proj     Orchid
* @file		OrchidLogs.h
* @brief	The Orchid C/C++ Component Collection Project.
* @author	alopex
* @version	v1.00a
* @date		2019-10-16
*/
#pragma once

#ifndef __ORCHIDLOGS_H__
#define __ORCHIDLOGS_H__

// Include Orchid Common header files
#include "OrchidCommon.h"

// Export Interfaces
#ifdef ORCHID_EXPORTS
#define ORCHIDLOGS_API __declspec(dllexport)
#else
#define ORCHIDLOGS_API __declspec(dllimport)
#endif

#define ORCHIDLOGS_CALLMETHOD __stdcall

class ORCHIDLOGS_API COrchidLogs
{
private:
	static void ORCHIDLOGS_CALLMETHOD GetComputerNames();
	static void ORCHIDLOGS_CALLMETHOD GetUserNames();
	static void ORCHIDLOGS_CALLMETHOD GetWindowsVersions();

protected:
	static void ORCHIDLOGS_CALLMETHOD GetLogFilePath(char *pStr, int nSize);
	static void ORCHIDLOGS_CALLMETHOD CreateLogFilePath();

public:
	static void ORCHIDLOGS_CALLMETHOD Write(LPCSTR file, LONG line, LPCSTR lpcstr, ...);
	static void ORCHIDLOGS_CALLMETHOD WriteLine(LPCSTR file, LONG line, LPCSTR lpcstr, ...);
};

#endif // !__ORCHIDLOGS_H__
