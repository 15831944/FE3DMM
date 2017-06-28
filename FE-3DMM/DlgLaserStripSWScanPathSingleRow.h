#pragma once
class CDlgLaserStripSubWin;


// CDlgLaserStripSWScanPathSingleRow �Ի���
typedef struct st_ParamSingleScan
{
	double  dScanLen;		//ɨ�賤��
	double  dScanSpeed;		//ɨ���ٶ�
	int		nScanNum;		//ɨ�����

	st_ParamSingleScan()
	{
		dScanLen = 0.0;
		dScanSpeed = 0.0;
		nScanNum = 0;
	}
}ParamSingleScan;


class CDlgLaserStripSWScanPathSingleRow : public CDialog
{
	DECLARE_DYNAMIC(CDlgLaserStripSWScanPathSingleRow)

public:
	CDlgLaserStripSWScanPathSingleRow(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLaserStripSWScanPathSingleRow();

// �Ի�������
	enum { IDD = IDD_DLG_LASERSTRIP_SUB_SCANPATH_SingleRow };

	void Cancel();				//���ٴ��ڼ��Ӵ���
	void InitDlgCtrl();
	void ApplyScanParamToSinglePathWin();  //Ӧ��ɨ�����������·�����ô���

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedLaserstripSubSpSrScanpathsetBtn();

private:
	void Release();				//�ͷű�����������new���ڴ�


private:
	CDlgLaserStripSubWin*		m_pDlgLaserStripSubWinMain;		 //������SubWin
	CBmpBtn						m_bmpBtn[1];

};
