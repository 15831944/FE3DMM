// EditWnd.h : header file
//

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CEditWnd window

class CEditWnd : public CWnd
{
// Construction
public:
	CEditWnd();
	DECLARE_DYNCREATE( CEditWnd )

// Attributes
public:

// Operations
public:
	void GetString(CString &strWnd);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CEditWnd)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CEditWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CEditWnd)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg UINT OnGetDlgCode();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
private:
	int PosFromChar(UINT nChar);		// ͨ��ָ�����ַ������x���λ��
	int CharFromPos(int nPosX);			// ͨ��������x���λ�û����Ӧ���ַ�
	void CutString();					// �����ַ���
	void PasteString();					// ճ���ַ���
	void CopyString();					// �����ַ���
	void MakeBKGround(CDC *pDC, COLORREF clrBegin, COLORREF clrEnd, CRect rect);	// ���ɴ��ڱ���
	CString m_strEdit;		// ��ǰ�������ı���
	CString m_strSelect;	// ��ǰѡ����ı���

	CPoint m_ptCursor;		// ��ǰ����λ�á�
	CPoint m_ptTxtBegin;	// �ı�����ʼλ�á�
	CPoint m_ptFirst;		// ����������ʱ�ĵ�һ��λ�á�
	CPoint m_ptSecond;		// ��굱ǰ��λ�á�

	int m_nCharPos;			// ��ǰ��괦�ڵڼ����ַ��ĺ��棬��0��ʼ������
	int m_nShowChar;		// �ڱ༭���е�һ����ʾ���ַ�����0��ʼ������
	int m_nMaxShowChars;	// �ڱ༭����һ�������ʾ���ַ�����	��
	int m_nSelectBegin;		// ѡ����ַ�����ʼλ�á�
	int m_nSelectEnd;		// ѡ����ַ�����ֹλ�á�

	CBitmap m_BmpBK;		// ����ͼƬ��

	CFont m_TxtFont;		// �ı������塣
	TEXTMETRIC m_tm;		// �ı��������Ϣ��

	CRect	m_rcWnd;		// ���ڵĴ�С��

	bool	m_bLBtDown;		// ���������¡�
	int		m_nShiftBegin;	// shift����һ��ʱ������ڵ��ַ���λ�á�
//extent ����
	CString m_strTitle;		// �༭�����
	CString m_strUnit;		// �༭��λ
	int m_iState;			// ״̬ 0-������1-���գ�2-����3-����
	BOOL m_bBkneedchange;	// �����Ƿ���ˢ��
	struct _BKCOLOR 
	{
		COLORREF clrBegin;
		COLORREF clrEnd;
	};
	_BKCOLOR m_bkcolor0;		// ����������ɫ-����
	_BKCOLOR m_bkcolor1;		// ����������ɫ-����
	_BKCOLOR m_bkcolor2;		// ����������ɫ-����
	_BKCOLOR m_bkcolor3;		// ����������ɫ-����

public:
	void SetTittleUnit(CString title ,CString unit);
	CString GetVal(){
	 return m_strEdit;		// ��ȡ�ı�;
	}
	void SetVal(CString val){
	 m_strEdit = val;		// �����ı�;
	 Invalidate();			// ˢ��
	}
	void Enable(BOOL bable,int state = 0){
	 EnableWindow(bable);		// �����ı�;
	}
	void SetState(int state){
	 m_iState = state;		// �����ı�;
	 m_bBkneedchange = 1;
	 Invalidate();
	}
};
