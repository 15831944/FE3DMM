#pragma once


// CDlgInitialize �Ի���

class CDlgInitialize : public CDialog
{
	DECLARE_DYNAMIC(CDlgInitialize)

public:
	CDlgInitialize(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInitialize();

// �Ի�������
	enum { IDD = IDD_DLG_INITIALIZE };

	void Cancel();				//���ٴ��ڼ��Ӵ���
	void InitFinish();			//��ʼ�����
	void InitExit();			//��ʼ���˳�

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnCancel();

private:
	void Release();				//�ͷű�����������new���ڴ�
	void InitProgress();
	void InitEdit();


public:
	CGradientProgressCtrl	m_progressInit;
	CCustomEdit				m_editInit;
	
};
