#pragma once
#include "DlgTransferAuto.h"
#include "DlgTransferManual.h"
#include "DlgTransferParamLearn.h"
#include "DlgTransferVisionTrain.h"

// CDlgTransfer �Ի���

class CDlgTransfer : public CDialog
{
	DECLARE_DYNAMIC(CDlgTransfer)

public:
	CDlgTransfer(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTransfer();

// �Ի�������
	enum { IDD = IDD_DLG_TRANSFER };

	void Cancel();				//���ٴ��ڼ��Ӵ���

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomeTabChange(NMHDR *pNMHDR, LRESULT * pResult);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

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
	CD2DCustomeTable				*m_pCustomeTab;
	CDlgTransferAuto					*m_pDlgTransferAuto;
	CDlgTransferManual				*m_pDlgTransferManual;
	CDlgTransferParamLearn		*m_pDlgTransferParaLearn;
	CDlgTransferVisionTrain			*m_pDlgTransferVisTrain;

private:
	CList<CDialog *, CDialog* >	m_listSubWindow;
	CProcessCore							*m_pProCore;	//��������ָ��
};
