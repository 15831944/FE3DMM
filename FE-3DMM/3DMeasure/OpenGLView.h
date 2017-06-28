#pragma once
#include "COpenGL.h"
//#include "..\iCloudCuM\DataStructure.h"
#include "TowOperation.h"

// COpenGLView ��ͼ
//#define tagColor
//class CTowOpt;
#define  OpenGLViewSplit 3.0

class COpenGLView : public CView
{
	DECLARE_DYNCREATE(COpenGLView)

public:
	COpenGLView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~COpenGLView();
	BOOL is_tow;
	BOOL is_CalcChrom;
	//CTowOpt GetTowOpt() const { return m_TowOpt; }
	void DrawCNString(const char *str);  //��������
	void SelectFont(int size, int charset, const char *face);
	CTowOpt &RefTowOpt() { return m_TowOpt; }
	const CTowOpt &RefTowOpt() const { return m_TowOpt; }
	
	//������ͼ�����û��޸Ĳ�������Ҫ���øú���������ͼ�����������
	void UpdateView() { Invalidate(); }
	//���µ��ƣ�true���±�׼���ƻ����ɫ��ͼ��false���²�������
	void UpdatePCloud(bool is_std ); 
	//��ԭ�������ơ���׼������ʾ��ʼλ��
	void RecoveryPCloud(  );
    //���������ʾ�ı�־����ȡ����ļ�chr��ִ��ƴ�Ϻ�����Ϊtrue��
	//����ʾ����ͭ�����׼ͭ��������Ϊfalse
   void SetShowErrSym( bool is_err=true )   //�����޸�
	{ m_IsShowErr=is_err;
	} 
	//�Ƿ���ʾͭ������
	void SetShowTowSym( bool is_tow=true ) { m_IsShowTow=is_tow; }
	//�Ƿ���ʾ��׼����
	void SetShowStdSym( bool is_std=true ) { m_IsShowStd=is_std; }
    //�Ƿ���ʾstl�ļ�
	void SetShowStlSy(bool is_stl=true){m_IsShowStl=is_stl;}
	//�жϵ�ǰ��ͼ�Ƿ���ʾ���
	bool IsShowErr() const { return m_IsShowErr; }
	//�жϵ�ǰ��ͼ�Ƿ���ʾͭ������
	bool IsShowTow() const { return m_IsShowTow; }
	//�жϵ�ǰ��ͼ�Ƿ���ʾ��׼����
	bool IsShowStd() const { return m_IsShowStd; }
    //�жϵ�ǰ��ͼ�Ƿ���ʾstl�ļ�
	bool IsShowStl() const { return m_IsShowStl; }

public:
	CFont m_Font;
	CDSChrom newPtChrom;
	int m_nCol;
	double m_maxCri;double m_maxNom;double m_minNom;double m_minCri;
		//int m_nCol=13;ֻ�о�̬�����������ݳ�Ա�ſ��������г�ʼ��,����Ӧ���ڹ��캯���и�ֵ
	//int m_maxCri=2;int m_maxNom=0.3;int m_minNom=-0.3;int m_minCri=-2;
private:
	bool ShowError( bool is_showerr=true );
	void ShowStd();
	void ShowTow();
	void ShowStl();
	void ShowChrom();
	void drawCNString( const char * str ); 
private:
    COpenGL m_nViewOpenGL;
	CTowOpt m_TowOpt;

	void Create2DTextLists();

	GLuint m_2DTextList;
	bool m_IsShowErr;
	bool m_IsShowTow; //�Ƿ���ʾ��������
	bool m_IsShowStd; //�Ƿ���ʾ��׼����
	bool m_IsShowStl;

	//��ͼ����ؿ���
	bool m_IsRotCen;
	double m_RotCen[3],m_BoxVec[3];
	int m_BoxMaxSeq;
	
    double m_fViewAspect;


public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void SetBase();
public:
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
public:
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};


