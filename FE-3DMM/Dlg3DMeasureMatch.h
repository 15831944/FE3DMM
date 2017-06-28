#pragma once
#include ".\3DMeasure\DataStructure.h"
#include ".\3DMeasure\iCloud3D_Operator.h"
#include ".\3DMeasure\BlendHandle.h"
#include ".\3DMeasure\Calculate.h"
#include ".\3DMeasure\OpenGLView.h"
#include ".\3DMeasure\COpenGL.h"
#include "resource.h"

// CDlg3DMeasureMatch �Ի���

class CDlg3DMeasureMatch : public CDialog
{
	DECLARE_DYNAMIC(CDlg3DMeasureMatch)

public:
	CDlg3DMeasureMatch(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlg3DMeasureMatch();

// �Ի�������
	enum { IDD = IDD_DLG_3DMEASURE_MATCH };

	void Cancel();				//���ٴ��ڼ��Ӵ���
//	void InitDlgCtrl();

public:
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	virtual BOOL OnInitDialog();
public:
	iCloudOperator m_PtOperator;
	TDSVec3DPt m_SetPtTest;
	CDS3DPtNor pt;
	CDS3DPt pt1;
	CEdit m_MatchTimes;
	CEdit m_AdfMu;
	int m_nIterTimes;
	float m_Mu;
	CDSChrom res_Errtemp;
	CHandleADF HandleADF;
	vector<CDS3DPtNor> m_ptMoving;	//�ƶ��㼯
	vector<CDS3DPtNor> m_ptFixed;	//�̶��㼯

	vector<float> mtDist;//�޸���ӵ�3/18
	double given_error;//�û����������
	double rate_given_1;//�û������İٷֱ�
	bool pass_whether_f;//����Ƿ�ͨ��

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	COpenGLView *m_viewOpenGL;
	virtual void PostNcDestroy();
	virtual void OnCancel();
	
private:
	void Release();				//�ͷű�����������new���ڴ�


private:
	CXPGroupBox			m_GB1;
	CXPGroupBox			m_GB2;
	CProcessCore		*m_pProCore;	//��������ָ��
public:
	afx_msg void OnBnClicked3dmeasureMOpenTest();
	afx_msg void OnBnClicked3dmeasureMOpenRef();
	afx_msg void OnBnClicked3dmeasureMBlend();
	afx_msg void OnEnChange3dmeasureMBlendtime();
	afx_msg void OnEnChange3dmeasureMBlendmu();
	afx_msg void OnBnClicked3dmeasureMOnchrom();
	afx_msg void OnBnClicked3dmeasureMOffchrom();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnEnChangenumber();
	afx_msg void OnEnChangedown();
	afx_msg void OnEnChangeup();
	afx_msg void OnEnChangeupon();
	afx_msg void OnEnChangedow();
	afx_msg void OnEnChangegiven();
	afx_msg void OnEnChangeactual();
	afx_msg void OnEnChangegivenpercent();
	afx_msg void OnEnChangewhether();
	afx_msg void OnBnClickedConfirm();
	CString m_sec_number;
	CString m_acceptance_down;
	CString m_minNom;
	CString m_acceptance_up;
	CString m_mea_down;
	CString m_mea_up;
	CString m_mea_dow;
	CString m_error_given;
	CString m_pass_whether;
	CString m_rate_given;
	double m_rate_actual;
};
