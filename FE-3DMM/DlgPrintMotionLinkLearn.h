#pragma once
class CDlgPrintMotionControl;

// CDlgPrintMotionLinkLearn �Ի���

//��λ����ϢX��Y
typedef struct st_PointPos
{
	float fPosX;
	float fPosY;
	st_PointPos()
	{
		fPosX = 0.0;
		fPosY = 0.0;
	}
}PointPos;

//��Ƕ���ϢA��C
typedef struct st_PointAngle
{
	float fAngleA;
	float fAngleC;
	st_PointAngle()
	{
		fAngleA = 0.0;
		fAngleC = 0.0;
	}
}PointAngle;

//ֱ����Ϣ(���˵����Ƕ�)
typedef struct st_StraightLine
{
	PointPos	beginpoint;
	PointPos	endpoint;
	PointAngle	angle;
}StraightLine;


class CDlgPrintMotionLinkLearn : public CDialog
{
	DECLARE_DYNAMIC(CDlgPrintMotionLinkLearn)

public:
	CDlgPrintMotionLinkLearn(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPrintMotionLinkLearn();

// �Ի�������
	enum { IDD = IDD_DLG_PRINT_MOTION_LINES };

	void Cancel();				//���ٴ��ڼ��Ӵ���

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedPrintMLBeginpointBtn();
	afx_msg void OnBnClickedPrintMLEndpointBtn();
	afx_msg void OnBnClickedPrintMLLinklineBtn();
	afx_msg void OnRclickPrintMLLinesList(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnUMLineDelete();
	afx_msg void OnUMLineClear();

private:
	void Release();									//�ͷű�����������new���ڴ�
	void InitDlgCtrl();
	void UpdateLineNum();							//����������


private:
	CProcessCore*				m_pProCore;			//��������ָ��
	CDlgPrintMotionControl*		m_pDlgMotionMain;	//�˶����ƴ���
	CBmpBtn					    m_bmpBtn[3];
	CListCtrl					m_listLines;

	StraightLine				m_straightline;

public:
	vector<StraightLine>		m_vecLine;			//ֱ��vector
	float						m_fPrintLinesSpeed;	//��ӡֱ���ٶ�

};
