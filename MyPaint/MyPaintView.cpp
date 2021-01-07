// MyPaintView.cpp : implementation of the CMyPaintView class
//

#include "stdafx.h"
#include "MyPaint.h"

#include "MyPaintDoc.h"
#include "MyPaintView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyPaintView

IMPLEMENT_DYNCREATE(CMyPaintView, CView)

BEGIN_MESSAGE_MAP(CMyPaintView, CView)
	//{{AFX_MSG_MAP(CMyPaintView)
	ON_COMMAND(ID_LINECOLOR, OnLinecolor)
	ON_COMMAND(ID_FILLCOLOR, OnFillcolor)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_COMMAND_RANGE(ID_FREELINE, ID_ELLIPSE, OnChangeTool)
	ON_UPDATE_COMMAND_UI_RANGE(ID_FREELINE, ID_ELLIPSE, OnUpdateChangeTool)
	// Standard printing commands
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyPaintView construction/destruction

CMyPaintView::CMyPaintView()
{
	// TODO: add construction code here
	m_colLine = RGB(0, 0, 0);
	m_colLineXor = RGB(255, 255, 255);
	m_colFill = RGB(255, 255, 255);

	m_nType = ID_FREELINE;
}

CMyPaintView::~CMyPaintView()
{
}

BOOL CMyPaintView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyPaintView drawing

void CMyPaintView::OnDraw(CDC* pDC)
{
	CMyPaintDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CMyPaintView printing

BOOL CMyPaintView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyPaintView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyPaintView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyPaintView diagnostics

#ifdef _DEBUG
void CMyPaintView::AssertValid() const
{
	CView::AssertValid();
}

void CMyPaintView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyPaintDoc* CMyPaintView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyPaintDoc)));
	return (CMyPaintDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyPaintView message handlers

void CMyPaintView::OnLinecolor() 
{
	// TODO: Add your command handler code here
	CColorDialog dlg;
	if(dlg.DoModal() == IDOK)
	{
		m_colLine = dlg.GetColor();
		m_colLineXor = ( RGB ( GetRValue(m_colLine) ^ 255, GetGValue(m_colLine) ^ 255, GetBValue(m_colLine) ^ 255 ) ); 
	}
}

void CMyPaintView::OnFillcolor() 
{
	// TODO: Add your command handler code here
	CColorDialog dlg;
	if(dlg.DoModal() == IDOK)
		m_colFill = dlg.GetColor();
}

void CMyPaintView::OnChangeTool()
{
	m_nType = GetCurrentMessage()->wParam;
}
void CMyPaintView::OnUpdateChangeTool(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(m_nType == (int)pCmdUI->m_nID);
}

void CMyPaintView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// �׸��� ��ǥ�� ���콺 Ŭ���� ��ǥ�� �ʱ�ȭ
	m_pntOld = point;
	m_pntCur = point;

	SetCapture();

	CView::OnLButtonDown(nFlags, point);
}

void CMyPaintView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	// TODO: Add your message handler code here and/or call default
	CClientDC dc(this);
	
	//��� �귯�� �Ӽ��� ����
	CBrush brush, *pOldBrush;
	if(m_nType == ID_RECTANGLE)
	{
		brush.CreateSolidBrush(m_colFill);
		pOldBrush = (CBrush *)dc.SelectObject(brush);
		dc.Rectangle(m_pntOld.x,m_pntOld.y,point.x,point.y);
	}
	else if(m_nType == ID_ELLIPSE)
	{
		brush.CreateSolidBrush(m_colFill);
		pOldBrush = (CBrush *)dc.SelectObject(brush);
		dc.Ellipse(m_pntOld.x,m_pntOld.y,point.x,point.y);
		
	}
	
	
	CView::OnLButtonUp(nFlags, point);
}

void CMyPaintView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(nFlags & MK_LBUTTON) //���� ��ư�� ���� �����϶�
	{
		CClientDC dc(this);

		//��� �귯�� �Ӽ��� ����
		CPen pen,*pOldPen;
		CBrush brush, *pOldBrush;

		if(m_nType == ID_FREELINE) //����� �׸���
		{
			// ������ �������� ���� ����
			pen.CreatePen(PS_SOLID,1,m_colLine);
			// ������ ���� ����
			pOldPen = (CPen *)dc.SelectObject(&pen);
			
			// ���� ��ǥ���� ���� ��ǥ���� ���� �׷��ش�.
			dc.MoveTo(m_pntOld.x,m_pntOld.y);
			dc.LineTo(point.x,point.y);
			
			// ���� ��ǥ�� �����Ѵ�.
			m_pntOld = point;
			dc.SelectObject(pOldPen);

		}	
		else if(m_nType == ID_LINE) // ���� �׸���
		{
			// Xor �� ������ �� ����
			pen.CreatePen(PS_SOLID,1,m_colLineXor);

			// NULL �귯��(���� �귯��) ����
			dc.SelectObject(GetStockObject(NULL_BRUSH));
			
			// �׸��� ��带 XOR ���� ����
			dc.SetROP2(R2_XORPEN);

			// �������� �� ����
			pOldPen = (CPen *)dc.SelectObject(&pen);
			
			// ���� �׸� �����
			dc.MoveTo(m_pntOld.x,m_pntOld.y);
			dc.LineTo(m_pntCur.x,m_pntCur.y);
			
			// �� �׸� �׸���
			dc.MoveTo(m_pntOld.x,m_pntOld.y);
			dc.LineTo(point.x,point.y);
	
			dc.SelectObject(pOldPen);

		}
		else if(m_nType == ID_RECTANGLE)
		{
			// Xor �� ������ �� ����
			pen.CreatePen(PS_SOLID,1,m_colLineXor);

			// NULL �귯��(���� �귯��) ����
			dc.SelectObject(GetStockObject(NULL_BRUSH));

			// �׸��� ��带 XOR ���� ����
			dc.SetROP2(R2_XORPEN);
			
			// �������� �� ����
			pOldPen = (CPen *)dc.SelectObject(&pen);
			
			// ���� �׸� �����
			dc.Rectangle(m_pntOld.x,m_pntOld.y,m_pntCur.x,m_pntCur.y);
			// �� �׸� �׸���	
			dc.Rectangle(m_pntOld.x,m_pntOld.y,point.x,point.y);

			dc.SelectObject(pOldPen);
		}
		else if(m_nType == ID_ELLIPSE)
		{
			pen.CreatePen(PS_SOLID,1,m_colLineXor);
			dc.SelectObject(GetStockObject(NULL_BRUSH));
			dc.SetROP2(R2_XORPEN);
			pOldPen = (CPen *)dc.SelectObject(&pen);

			dc.Ellipse(m_pntOld.x,m_pntOld.y,m_pntCur.x,m_pntCur.y);
			// �� �׸� �׸���		
			dc.Ellipse(m_pntOld.x,m_pntOld.y,point.x,point.y);

			dc.SelectObject(pOldPen);
		}
		
		m_pntCur = point;

	}
	CView::OnMouseMove(nFlags, point);
}

void CMyPaintView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	
	
}

void CMyPaintView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CView::OnPaint() for painting messages
}
