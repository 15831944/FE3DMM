#pragma once
#include "Dlg3DMeasureScan.h"
#include "Dlg3DMeasureMatch.h"

// CDlg3DMeasure �Ի���

class CDlg3DMeasure : public CDialog
{
	DECLARE_DYNAMIC(CDlg3DMeasure)

public:
	CDlg3DMeasure(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg3DMeasure();

// �Ի�������
	enum { IDD = IDD_DLG_3DMEASURE };

	void Cancel();				//���ٴ��ڼ��Ӵ���

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
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
	CDlg3DMeasureScan		*m_pDlg3DMeasureScan;
	CDlg3DMeasureMatch		*m_pDlg3DMeasureMatch;

private:
	CList<CDialog *, CDialog* > m_listSubWindow;

	CProcessCore			*m_pProCore;	//��������ָ��
};
