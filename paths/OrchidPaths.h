/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Gorgeous Bubble, alopex
*     All rights reserved.
*
* @proj     Orchid
* @file		OrchidPaths.h
* @brief	The Orchid C/C++ Component Collection Project.
* @author	alopex
* @version	v1.00a
* @date		2019-10-19
*/
#pragma once

#ifndef __ORCHIDPATHS_H__
#define __ORCHIDPATHS_H__

// Include Orchid Common header files
#include "OrchidCommon.h"

// Export Interfaces
#ifdef ORCHID_EXPORTS
#define ORCHIDPATHS_API __declspec(dllexport)
#else
#define ORCHIDPATHS_API __declspec(dllimport)
#endif

#define ORCHIDPATHS_CALLMETHOD __stdcall

class ORCHIDPATHS_API COrchidPaths
{
public:
	static BOOL ORCHIDPATHS_CALLMETHOD GetModulePathA(const char* szArr, int nSize);
	static BOOL ORCHIDPATHS_CALLMETHOD GetModulePathW(const wchar_t* wszArr, int nSize);
	static BOOL ORCHIDPATHS_CALLMETHOD GetLocalPathA(const char* szArr, int nSize);
	static BOOL ORCHIDPATHS_CALLMETHOD GetLocalPathW(const wchar_t* wszArr, int nSize);
	static BOOL ORCHIDPATHS_CALLMETHOD GetParentPathA(const char* szArr, int nSize, int nDeep);
	static BOOL ORCHIDPATHS_CALLMETHOD GetParentPathW(const wchar_t* wszArr, int nSize, int nDeep);

};

#endif // !__ORCHIDPATHS_H__