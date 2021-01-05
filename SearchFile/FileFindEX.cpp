#include "pch.h"
#include "FileFindEX.h"


CFileFindEX::CFileFindEX()
{
}


CFileFindEX::~CFileFindEX()
{
}

CString CFileFindEX::GetCreationTimeString(CString strTmp)
{
	CString str;
	CTime cTime;

	GetCreationTime(cTime);

	str.Format(_T("%02d%s%02d%s%02d %02d:%02d"), cTime.GetYear(),
		strTmp, cTime.GetMonth(), strTmp, cTime.GetDay(),
		cTime.GetHour(), cTime.GetDay());
	return str;
}

CString CFileFindEX::GetLengthString()
{
	CString str;
	str.Format(_T("%lu"), GetLength());
	return str;
}