/*
*     COPYRIGHT NOTICE
*     Copyright(c) 2017~2019, Gorgeous Bubble, alopex
*     All rights reserved.
*
* @proj     Orchid
* @file		OrchidPaths.cpp
* @brief	The Orchid C/C++ Component Collection Project.
* @author	alopex
* @version	v1.00a
* @date		2019-10-19
*/
#include "OrchidPaths.h"
#include "OrchidConvert.h"

BOOL ORCHIDPATHS_CALLMETHOD COrchidPaths::GetLocalPathA(const char* szArr, int nSize)
{
	char chArr[MAX_PATH] = { 0 };
	char* pTemp = NULL;
	int nArrSize = 0;
	::GetModuleFileNameA(NULL, chArr, MAX_PATH);
	pTemp = strrchr(chArr, '\\');
	if (pTemp != NULL)
	{
		*pTemp = '\0';
	}
	nArrSize = strlen(chArr);
	if (nSize < nArrSize + 1)
	{
		return FALSE;
	}
	memset((void*)szArr, 0, nSize * sizeof(char));
	memcpy_s((void*)szArr, nSize * sizeof(char), chArr, (nArrSize + 1) * sizeof(char));
	return TRUE;
}

BOOL ORCHIDPATHS_CALLMETHOD COrchidPaths::GetLocalPathW(const wchar_t* wszArr, int nSize)
{
	char chArr[MAX_PATH] = { 0 };
	char* pTemp = NULL;
	::GetModuleFileNameA(NULL, chArr, MAX_PATH);
	pTemp = strrchr(chArr, '\\');
	if (pTemp != NULL)
	{
		*pTemp = '\0';
	}
	BOOL bReturn = FALSE;
	bReturn = COrchidConvert::ConvertA2W(chArr, wszArr, nSize);
	if (!bReturn)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL ORCHIDPATHS_CALLMETHOD COrchidPaths::GetParentPathA(const char* szArr, int nSize, int nDeep)
{
	char chArr[MAX_PATH] = { 0 };
	int nArrSize = 0;
	if (nDeep <= 0)
	{
		return FALSE;
	}
	::GetModuleFileNameA(NULL, chArr, MAX_PATH);
	for (int i = 0; i < nDeep; ++i)
	{
		char* pTemp = NULL;
		pTemp = strrchr(chArr, '\\');
		if (pTemp != NULL)
		{
			*pTemp = '\0';
		}
	}
	nArrSize = strlen(chArr);
	if (nSize < nArrSize + 1)
	{
		return FALSE;
	}
	memset((void*)szArr, 0, nSize * sizeof(char));
	memcpy_s((void*)szArr, nSize * sizeof(char), chArr, (nArrSize + 1) * sizeof(char));
	return TRUE;
}

BOOL ORCHIDPATHS_CALLMETHOD COrchidPaths::GetParentPathW(const wchar_t* wszArr, int nSize, int nDeep)
{
	char chArr[MAX_PATH] = { 0 };
	if (nDeep <= 0)
	{
		return FALSE;
	}
	::GetModuleFileNameA(NULL, chArr, MAX_PATH);
	for (int i = 0; i < nDeep; ++i)
	{
		char* pTemp = NULL;
		pTemp = strrchr(chArr, '\\');
		if (pTemp != NULL)
		{
			*pTemp = '\0';
		}
	}
	BOOL bReturn = FALSE;
	bReturn = COrchidConvert::ConvertA2W(chArr, wszArr, nSize);
	if (!bReturn)
	{
		return FALSE;
	}
	return TRUE;
}
