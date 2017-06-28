#pragma once
#include "DlgLaserStripSubWin.h"

// CDlgLaserStrip �Ի���

class CDlgLaserStrip : public CDialog
{
	DECLARE_DYNAMIC(CDlgLaserStrip)

public:
	CDlgLaserStrip(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLaserStrip();

// �Ի�������
	enum { IDD = IDD_DLG_LASERSTRIP };

	void Cancel();				//���ٴ��ڼ��Ӵ���

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomeTabChange(NMHDR *pNMHDR, LRESULT * pResult);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnCancel();


private:
	void Release();				//�ͷű�����������new���ڴ�
	bool InitCustomeTab();
	void CreateSubWindow();
	void ShowSubWindow(int iIndex);

public:
	CD2DCustomeTable		*m_pCustomeTab;
	CDlgLaserStripSubWin	*m_pDlgLaserStripSubwin;

private:
	CList<CDialog *, CDialog* > m_listSubWindow;

	CProcessCore			*m_pProCore;	//��������ָ��
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
