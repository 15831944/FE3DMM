#pragma once
#include "afxwin.h"


// CDlgTransferManualNew �Ի���

class CDlgTransferManualNew : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTransferManualNew)

public:
	CDlgTransferManualNew(CProcessCore* pProCore, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTransferManualNew();
// �Ի�������
	enum { IDD = IDD_DLG_TRANSFER_M_NEW };


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()

public:
	BOOL FileExist(const CString FileName) const;

private:
	void Release();
	void InitCtrl();

public:
	afx_msg void OnBnClickedTransferMNOkBtn();
	afx_msg void OnBnClickedTransferMNCancelBtn();
	virtual BOOL OnInitDialog();
	CComboBox m_cComBoxPISize;

private:
	CProcessCore     *m_pProCore;      //��������ָ��
};
