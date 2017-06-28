#pragma once
#include "DlgPrintMotionControl.h"
#include "DlgPrintParamAdjust.h"
#include "DlgPrintPrintOperate.h"

// CDlgPrint �Ի���

class CDlgPrint : public CDialog
{
	DECLARE_DYNAMIC(CDlgPrint)

public:
	CDlgPrint(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPrint();

// �Ի�������
	enum { IDD = IDD_DLG_PRINT };

	void Cancel();				//���ٴ��ڼ��Ӵ���

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomeTabChange(NMHDR *pNMHDR, LRESULT * pResult);


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();


private:
	void Release();				//�ͷű�����������new���ڴ�
	bool InitCustomeTab();
	void CreateSubWindow();
	void ShowSubWindow(int iIndex);

public:
	CD2DCustomeTable		*m_pCustomeTab;
	CDlgPrintParamAdjust	*m_pDlgPrintParamAdjust;
	CDlgPrintMotionControl	*m_pDlgPrintMotionControl;
	CDlgPrintPrintOperate	*m_pDlgPrintPrintOperate;

private:
	CList<CDialog *, CDialog* > m_listSubWindow;

	CProcessCore			*m_pProCore;	//��������ָ��
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
