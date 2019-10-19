/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Gorgeous Bubble, alopex
*     All rights reserved.
*
* @proj     Orchid
* @file		OrchidConvert.h
* @brief	The Orchid C/C++ Component Collection Project.
* @author	alopex
* @version	v1.00a
* @date		2019-10-19
*/
#pragma once

#ifndef __ORCHIDCONVERT_H__
#define __ORCHIDCONVERT_H__

// Include Orchid Common header files
#include "OrchidCommon.h"

// Export Interfaces
#ifdef ORCHID_EXPORTS
#define ORCHIDCONVERT_API __declspec(dllexport)
#else
#define ORCHIDCONVERT_API __declspec(dllimport)
#endif

#define ORCHIDCONVERT_CALLMETHOD __stdcall

class ORCHIDCONVERT_API COrchidConvert
{
public:
	static BOOL ORCHIDCONVERT_CALLMETHOD ConvertA2W(const char* szArr, const wchar_t* wszArr, int nSize);
	static BOOL ORCHIDCONVERT_CALLMETHOD ConvertW2A(const wchar_t* wszArr, const char* szArr, int nSize);

};

#endif // !__ORCHIDCONVERT_H__