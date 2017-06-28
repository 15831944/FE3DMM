#pragma once
class CDlgLaserStripSubWin;


// CDlgLaserStripSWScanPathMultiRow �Ի���
typedef struct st_ParamMultiScan
{
	double  dScanLen;			//ɨ�賤��
	double	dScanSpace;			//ɨ����
	double  dScanSpeed;			//ɨ���ٶ�
	double	dTransRowSpeed;		//�����ٶ�
	int		nScanNum;			//ɨ�����

	st_ParamMultiScan()
	{
		dScanLen = 0.0;
		dScanSpace = 0.0;
		dScanSpeed = 0.0;
		dTransRowSpeed = 0.0;
		nScanNum = 0;
	}
}ParamMultiScan;


class CDlgLaserStripSWScanPathMultiRow : public CDialog
{
	DECLARE_DYNAMIC(CDlgLaserStripSWScanPathMultiRow)

public:
	CDlgLaserStripSWScanPathMultiRow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLaserStripSWScanPathMultiRow();

// �Ի�������
	enum { IDD = IDD_DLG_LASERSTRIP_SUB_SCANPATH_MultiRow };

	void Cancel();				//���ٴ��ڼ��Ӵ���
	void InitDlgCtrl();
	void ApplyScanParamToMultiPathWin();  //Ӧ��ɨ�����������·�����ô���

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();

public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedLaserstripSubSpMrScanpathsetBtn();


private:
	void Release();				//�ͷű�����������new���ڴ�


private:
	CDlgLaserStripSubWin*		m_pDlgLaserStripSubWinMain;		 //������SubWin
	CBmpBtn						m_bmpBtn[1];
	
};
