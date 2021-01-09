// SocServer.cpp : implementation file
//

#include "stdafx.h"
#include "ChatServer.h"
#include "SocServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSocServer

CSocServer::CSocServer()
{
}

CSocServer::~CSocServer()
{
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CSocServer, CSocket)
	//{{AFX_MSG_MAP(CSocServer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CSocServer member functions

void CSocServer::Init(HWND hWnd)
{
	// ���� ������ ������ �ޱ�
	
	m_hWnd = hWnd;
}
void CSocServer::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// Ŭ���̾�Ʈ�� �����ϸ� ���� �����쿡 ���Ӹ޽���(UM_ACCEPT)�� ������
	Accept(m_socCom);
	SendMessage(m_hWnd, UM_ACCEPT, 0, 0);
	CSocket::OnAccept(nErrorCode);
}

CSocCom* CSocServer::GetAcceptSocCom()
{
	// ��ż����� �����Ѵ�.
	// ��ȯ�Ǵ� ��� ������ Ŭ���̾�Ʈ�� ����ȴ�.
	return &m_socCom;
}
