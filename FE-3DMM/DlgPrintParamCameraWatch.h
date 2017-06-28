#pragma once
class CDlgPrintParamAdjust;

// CDlgPrintParamCameraWatch �Ի���

class CDlgPrintParamCameraWatch : public CDialog
{
	DECLARE_DYNAMIC(CDlgPrintParamCameraWatch)

public:
	CDlgPrintParamCameraWatch(CProcessCore* pProCore = NULL, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPrintParamCameraWatch();

// �Ի�������
	enum { IDD = IDD_DLG_PRINT_PARAM_CAMERAWATCH };

	void Cancel();				//���ٴ��ڼ��Ӵ���

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
	virtual void OnCancel();
	virtual void PostNcDestroy();

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedPrintPaCameraFilenameBtn();
	afx_msg void OnBnClickedPrintPaCameraPhotoBtn();
	afx_msg void OnBnClickedPrintPaCameraVideoBtn();
	afx_msg void OnBnClickedPrintPaCameraTickmarkBtn();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL PreTranslateMessage(MSG* pMsg);

private:
	void Release();			//�ͷű�����������new���ڴ�
	void InitDlgCtrl();


private:
	CDlgPrintParamAdjust*		m_pDlgParamMain;				//�������ڴ���
	CBmpBtn								m_bmpBtn[4];
	CProcessCore						*m_pProCore;						//��������ָ��
	CImageShowStatic				m_staticPicShow;
	bool										m_bDrawTickMark;				//�Ƿ񻭿̶�
	bool										m_bWriteVideo;					//�Ƿ�д��Ƶ
	CString									m_strFileName;					//ͼƬ����Ƶ�ļ�������
	CString									m_strStorePath;					//�ļ��洢·��
	CString									m_strPhotoAllPath;				//��Ƭ�ļ�ȫ·��
	CString									m_strVideoAllPath;				//��Ƶ�ļ�ȫ·��
	VideoWriter							m_videoWriter;					//д��Ƶ
	CImageOperate					m_imageoperate;				//ͼ�����
};
