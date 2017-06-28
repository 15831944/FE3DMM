#pragma once
#include "ProcessCore.h"
#include "afxwin.h"
#include "afxcmn.h"
// CDlgTransferParamCoordCalib �Ի���

class CDlgTransferParamLearn;

struct PickCamOffset
{
	double fOffsetX;    //��е���������������X����ƫ��
	double fOffsetY;     //��е���������������Y����ƫ��
};

class CDlgTransferParamCoordCalib : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTransferParamCoordCalib)

public:
	CDlgTransferParamCoordCalib(CProcessCore* pProCore,CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTransferParamCoordCalib();
	void Cancel();
	void InitCtrl();

protected:
	virtual void OnCancel();
	virtual void PostNcDestroy();
	void Release();
// �Ի�������
	enum { IDD = IDD_DLG_TRANSFER_P_COORDCALIB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

private:
	void SetParentWnd();
	DECLARE_MESSAGE_MAP()

private:
	CProcessCore* m_pProCore;
	CDlgTransferParamLearn* m_pParent;

	double m_fTransferPickPosX;     //���ʱתӡ���Xλ��
	double m_fTransCamPosX;         //תӡ����۲�λ��X

	std::vector<PickCamOffset> m_vecOffset;

	//���ռ����ƽ��ƫ����
	double m_fOffsetX;   
	double m_fOffsetY;

	BOOL LocateCircle(const HObject* hoImage, const double &, const double&);   //��λԲ��

public:
	CBmpBtn m_bmpBtn[6];
	static int m_iPressCount;
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnBnClickedTransferPCSavecenterBtn();
	afx_msg void OnBnClickedTransferPCClibBtn();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedTransferPCCalibpickercamBtn();
};
