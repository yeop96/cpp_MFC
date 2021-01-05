#pragma once
#include <afx.h>
class CFileFindEX :
	public CFileFind
{
public:
	CFileFindEX(void);
	~CFileFindEX(void);
	CString GetCreationTimeString(CString strTmp = "-");
	CString GetLengthString();
};

