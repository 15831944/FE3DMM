#pragma once
#include "afxwin.h"


// CDlgTransferVisionTrain �Ի���

class CDlgTransferVisionTrain : public CDialog
{
	DECLARE_DYNAMIC(CDlgTransferVisionTrain)

public:
	CDlgTransferVisionTrain(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTransferVisionTrain();

// �Ի�������
	enum { IDD = IDD_DLG_TRANSFER_VISION };
	enum {NCC = 0, SHAPE};
	void Cancel();				//���ٴ��ڼ��Ӵ���
	void InitDlgCtrl();
	
public:
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedTransferVCameraTransUpRadio();
	afx_msg void OnBnClickedTransferVCameraTransDownRadio();
	afx_msg void OnBnClickedTransferVCameraliveCheck();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
	virtual void OnCancel();

private:
	void Release();				//�ͷű�����������new���ڴ�
	void SetTransCameraType(const CameraType camtype);  //����תӡ���������
	void UpdateModelList();
	void InitHalconWindow();

private:
	CXPGroupBox						m_GB1;
	CXPGroupBox						m_GB2;
	CXPGroupBox						m_GB3;
	CBmpBtn								m_bmpBtn[4];
	CComboBox                         m_cComBoxObject;
	CProcessCore						*m_pProCore;						//��������ָ��
	CImageShowStatic				m_staticPicShow;
	CameraType							m_cameratypeTrans;			//תӡ���������
	CImageOperate					m_imgoperTransUp;			//תӡ����ͼ�����
	CImageOperate					m_imgoperTransDown;		//תӡ����ͼ�����
	HTuple                                   m_hvModelWindow;          //��ʾģ��ͼ�񴰿�
	HObject                                 m_hoImageModel;
	CListCtrlCl                              m_cModelList;
	int                                            m_iTransferType; 
	int                                            m_iMatchType;
public:
	afx_msg void OnBnClickedTransferVInitiativeRadio();
	afx_msg void OnBnClickedTransferVPassivityRadio();
	afx_msg void OnBnClickedTransferVCalibrateBtn();
	afx_msg void OnBnClickedTransferVMakemodelBtn();
	afx_msg void OnBnClickedTransferVModeldelBtn();
	afx_msg void OnNMClickTransferVModelList(NMHDR *pNMHDR, LRESULT *pResult);
};
