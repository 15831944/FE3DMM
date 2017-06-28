#pragma once


// CDlgTransferAuto �Ի���

class CDlgTransferAuto : public CDialog
{
	DECLARE_DYNAMIC(CDlgTransferAuto)

public:
	CDlgTransferAuto(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTransferAuto();

// �Ի�������
	enum { IDD = IDD_DLG_TRANSFER_AUTO };

	void Cancel();				//���ٴ��ڼ��Ӵ���
	void InitDlgCtrl();

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedTransferACameraTransUpRadio();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnCancel();

private:
	void Release();																		//�ͷű�����������new���ڴ�
	void InitWindowHandle();													//��ʼ��Pic�ؼ���ʾ����

private:
	CXPGroupBox					m_GB1;
	CXPGroupBox					m_GB2;
	CXPGroupBox					m_GB3;
	CBmpBtn							m_bmpBtn[4];
	CProcessCore					*m_pProCore;							//��������ָ��
	HTuple								m_windowHandle_Pic;			//Pic�ؼ�������Halcon���ھ��
	Size										m_winSize_Pic;							//Pic���ڴ�С
};
