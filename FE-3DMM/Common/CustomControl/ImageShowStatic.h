// StaticDisplayImage.h : header file

#pragma once
#include "MyRectTracker.h"
#include "CvvImage.h"


class CImageShowStatic : public CStatic
{
// Construction
public:
	CImageShowStatic();
	virtual ~CImageShowStatic();

	void SetShowImage(IplImage* pImg);		//����ͼ����ʾ
	void SetDrawRect(bool bFlag);					//���û�����
	void SetDrawTickMark(bool bFlag);			//���û��̶���
	CRect GetTrackerRect();								//�����Ƥ������CRect

protected:
	//{{AFX_MSG(CImageShowStatic)
	// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	DECLARE_MESSAGE_MAP()

private:
	void DrawTickMark(CDC* pDC, int iCenterX, int iCenterY);  //���̶���


private:
	CMyRectTracker m_tracker;
	CPen* m_pYellowPen;
	IplImage* m_iplImage;
	int m_iChangeSizeX;
	int m_iChangeSizeY;
	CRect m_rcInitWin;
	bool m_bIsInit;												//�Ƿ��ʼ����Ƥ��
	bool m_bIsDrawTickMark;							//�Ƿ񻭿̶���
};

