
// FE-3DMMDlg.h : ͷ�ļ�
//

#pragma once
#include "FE-3DMM.h"
#include "DlgLaserStrip.h"
#include "Dlg3DMeasure.h"
#include "DlgTransfer.h"
#include "DlgPrint.h"

#define TIMER_ERROR_STATUS 0xFF          //������ʱ��
#define TIMER_IMAGE_SHOW   0xFF+1		//ͼ����ʾ��ʱ��

// CFE3DMMDlg �Ի���
class CFE3DMMDlg : public CDialogEx
{
// ����
public:
	CFE3DMMDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FE3DMM_DIALOG };

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedMain3dmeasureBtn();
	afx_msg void OnBnClickedMainUgBtn();
	afx_msg void OnBnClickedMainLaserstripBtn();
	afx_msg void OnBnClickedMainTransferBtn();
	afx_msg void OnBnClickedMainPrintBtn();
	afx_msg void OnBnClickedMainExitBtn();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);


// ʵ��
protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

private:
	void Release();														//�ͷű�����������new���ڴ�
	void InitButton();
	void InitErrorStatusEdit();									//��ʼ��������ʾEdit
	void CreateSubDialog();
	void ShowSubDialog(INT measure=SW_HIDE, INT laserstrip=SW_HIDE, INT tranfer=SW_HIDE, INT print=SW_HIDE);
	void ShowUgWnd();											//��ʾUG����
	void CloseUgWnd();											//�ر�UG����
	void RefreshErrorStatus();									//���±���״̬
	void RefreshImageShow();									//����ͼ����ʾ

public:
	CDlgLaserStrip			*m_pDlgLaserStrip;
	CDlg3DMeasure		*m_pDlg3DMeasure;
	CDlgTransfer				*m_pDlgTransfer;
	CDlgPrint					*m_pDlgPrint;

private:
	CBmpBtn					m_bmpBtn[7];
	CProcessCore			*m_pProCore;					//��������ָ��
	CReadOnlyEdit			m_editErrorStatus;			//������ʾEdit
	CString						m_strErrorStatus;				//��������

};
