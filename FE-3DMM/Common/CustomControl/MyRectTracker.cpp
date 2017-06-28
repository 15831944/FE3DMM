// MyRectTracker.cpp: implementation of the CMyRectTracker class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MyRectTracker.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyRectTracker::CMyRectTracker()
{
	m_bEnable = FALSE;
}

CMyRectTracker::~CMyRectTracker()
{

}


/***************************************************************** 
** ��������: Initial()
** �������: 
		rect
		maxRect
** ��    ��: ��
** ��������: ��ʼ��
** �� �� ��: ���ľ�
** Version : 1.0 
******************************************************************/
void CMyRectTracker::Initial(RECT& rect, RECT &maxRect)
{
	m_rect = rect;
	m_rectOld = m_rect;
	m_nHandleSize = 10;
	m_maxRect = maxRect;
}

/***************************************************************** 
** ��������: AdjustRect()
** �������: 
		nHandle
		lpRect
** ��    ��: ��
** ��������: 
** �� �� ��: ���ľ�
** Version : 1.0 
******************************************************************/
void CMyRectTracker::AdjustRect(int nHandle, LPRECT lpRect)
{
	if (nHandle == this->hitBottomRight)
	{	
		int disx = lpRect->right - m_rectOld.right;
		int disy = lpRect->bottom - m_rectOld.bottom;
		int dis = _MaX(disx, disy);
		lpRect->bottom = m_rectOld.bottom + dis;
		lpRect->right = m_rectOld.right + dis;
		lpRect->left = m_rectOld.left - dis;
		lpRect->top = m_rectOld.top - dis;
	}
	else if (nHandle == this->hitTopLeft)
	{
		int disx = lpRect->left - m_rectOld.left;
		int disy = lpRect->top - m_rectOld.top;
		int dis = _MaX(disx, disy);
		lpRect->bottom = m_rectOld.bottom - dis;
		lpRect->right = m_rectOld.right - dis;
		lpRect->left = m_rectOld.left + dis;
		lpRect->top = m_rectOld.top + dis;		
	}
	else if (nHandle == this->hitTopRight)
	{
		int disx = lpRect->right-m_rectOld.right;
		int disy = m_rectOld.top-lpRect->top;
		int dis = _MaX(disx, disy);
		lpRect->bottom = m_rectOld.bottom + dis;
		lpRect->right = m_rectOld.right + dis;
		lpRect->left = m_rectOld.left-dis;
		lpRect->top = m_rectOld.top-dis;	
	}
	else if (nHandle == this->hitBottomLeft)
	{
		int disx = m_rectOld.left - lpRect->left;
		int disy = lpRect->bottom - m_rectOld.bottom;
		int dis = _MaX(disx, disy);
		lpRect->bottom = m_rectOld.bottom + dis;
		lpRect->right = m_rectOld.right + dis;
		lpRect->left = m_rectOld.left - dis;
		lpRect->top = m_rectOld.top - dis;
	}
	else if (nHandle == this->hitBottom)
	{
		int disy = lpRect->bottom - m_rectOld.bottom;
		lpRect->bottom = m_rectOld.bottom + disy;
		lpRect->top = m_rectOld.top - disy;
	}
	else if (nHandle == this->hitLeft)
	{
		int disx = m_rectOld.left - lpRect->left;
		lpRect->right = m_rectOld.right + disx;
		lpRect->left = m_rectOld.left - disx;

	}
	else if (nHandle == this->hitRight)
	{
		int disx = m_rectOld.right - lpRect->right;
		lpRect->right = m_rectOld.right - disx;
		lpRect->left = m_rectOld.left + disx;
	}
	else if (nHandle == this->hitTop)
	{
		int disy = lpRect->top - m_rectOld.top;
		lpRect->bottom = m_rectOld.bottom - disy;
		lpRect->top = m_rectOld.top + disy;
	}
	else
	{
		*lpRect = m_rectOld;
	}
	
	if (((lpRect->bottom - lpRect->top) > m_maxRect.Height()) || ((lpRect->right - lpRect->left) > m_maxRect.Width()))
	{
		lpRect->bottom = m_maxRect.bottom;
		lpRect->left = 0;
		lpRect->top = 0;
		lpRect->right = m_maxRect.right;
	}	
}

/***************************************************************** 
** ��������: OnChangedRect()
** �������: 
		rectOld
** ��    ��: ��
** ��������: 
** �� �� ��: ���ľ�
** Version : 1.0
******************************************************************/
void CMyRectTracker::OnChangedRect(const CRect& rectOld)
{
	m_rectOld = rectOld;
}

/***************************************************************** 
** ��������: DrawRect()
** �������: 
		pDC
** ��    ��: ��
** ��������: 
** �� �� ��: ���ľ�
** Version : 1.0
******************************************************************/
void CMyRectTracker::DrawRect(CDC* pDC)
{
	if (m_bEnable)
	{
		pDC->MoveTo(CPoint(m_rect.left, m_rect.top));
		pDC->LineTo(CPoint(m_rect.right, m_rect.top));
		pDC->LineTo(CPoint(m_rect.right, m_rect.bottom));
		pDC->LineTo(CPoint(m_rect.left, m_rect.bottom));
		pDC->LineTo(CPoint(m_rect.left, m_rect.top));		
	}
}

/***************************************************************** 
** ��������: Track()
** �������: 
		pWnd			--
		point
		bAllowInvert
		pWndClipTo
** ��    ��: ��
** ��������: 
** �� �� ��: ���ľ�
** Version : 1.0 
******************************************************************/
BOOL CMyRectTracker::Track(CWnd* pWnd, CPoint point, BOOL bAllowInvert, CWnd* pWndClipTo)
{
	if (m_bEnable)
	{
		return CRectTracker::Track(pWnd, point, bAllowInvert, pWndClipTo);
	}
	else 
		return FALSE;
}

/***************************************************************** 
** ��������: Enable()
** �������: 
		bEnable		--��־λ
** ��    ��: ��
** ��������: 
** �� �� ��: ���ľ�
** Version : 1.0
******************************************************************/
void CMyRectTracker::Enable(BOOL bEnable)
{
	m_bEnable = bEnable;
}
