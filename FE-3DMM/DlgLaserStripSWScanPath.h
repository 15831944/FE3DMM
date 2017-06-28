#pragma once
#include "DlgLaserStripSWScanPathSingleRow.h"
#include "DlgLaserStripSWScanPathMultiRow.h"
class CDlgLaserStripSubWin;


// CDlgLaserStripSWScanPath �Ի���

class CDlgLaserStripSWScanPath : public CDialog
{
	DECLARE_DYNAMIC(CDlgLaserStripSWScanPath)

public:
	CDlgLaserStripSWScanPath(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLaserStripSWScanPath();

// �Ի�������
	enum { IDD = IDD_DLG_LASERSTRIP_SUB_SCANPATH };

	void Cancel();						//���ٴ��ڼ��Ӵ���
	void ApplyScanParamToPathWin();     //Ӧ��ɨ�������·���滮����


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedLaserstripSubSpSinglerowRadio();
	afx_msg void OnBnClickedLaserstripSubSpMultirowRadio();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:  
	void Release();			//�ͷű�����������new���ڴ�
	void ShowSubDlg(INT singlerow, INT multirow);

private:
	CDlgLaserStripSubWin*					m_pDlgLaserStripSubWinMain;	//������SubWin
	CDlgLaserStripSWScanPathSingleRow*		m_pDlgLaserStripSingleRow;  //����·��ɨ���Ӵ���
	CDlgLaserStripSWScanPathMultiRow*		m_pDlgLaserStripMultiRow;   //����·��ɨ���Ӵ���
	
};
