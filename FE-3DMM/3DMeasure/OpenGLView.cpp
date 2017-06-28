// OpenGLDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "OpenGLView.h"
#include "../gl/glut.h"
#include "..\Dlg3DMeasureMatch.h"

// COpenGLView 

IMPLEMENT_DYNCREATE(COpenGLView, CView)

COpenGLView::COpenGLView()
	: m_IsShowErr( false ) 
	, m_IsShowTow( true )
	, m_IsShowStl(true)
	, m_IsShowStd( false )
    , m_IsRotCen( false ) 
	, is_CalcChrom(false)
	, m_fViewAspect( 1.0 )
	, m_BoxMaxSeq( 0 )
{
	m_nViewOpenGL.SetProjectionMode(1);
	m_nViewOpenGL.SetTwoView(false);


	for( int i=0;i<3;++i )
	{
		m_RotCen[i]=0.0;
		m_BoxVec[i]=2.0;
	}
}

COpenGLView::~COpenGLView()
{
}

void COpenGLView::Create2DTextLists()
{
	CFont m_font;
//	GLYPHMETRICSFLOAT agmf[256]; 
	m_font.CreateFont(	-12,                                     // Height Of Font
						0,                                     // Width Of Font
						0,                                     // Angle Of Escapement
						0,                                     // Orientation Angle
						FW_BOLD,                       // Font Weight
						FALSE,                             // Italic
						FALSE,                             // Underline
						FALSE,                             // Strikeout
						ANSI_CHARSET,               // Character Set Identifier
						OUT_TT_PRECIS,             // Output Precision
						CLIP_DEFAULT_PRECIS, // Clipping Precision  �ü�����
						ANTIALIASED_QUALITY,  // Output Quality 
						FF_DONTCARE | DEFAULT_PITCH, // Family And Pitch
						_T("����") );  //T("Arial" �޸�
	m_Font.CreateFont(	-12,                                     // Height Of Font
		0,                                     // Width Of Font
		0,                                     // Angle Of Escapement
		0,                                     // Orientation Angle
		FW_BOLD,                       // Font Weight
		FALSE,                             // Italic
		FALSE,                             // Underline
		FALSE,                             // Strikeout
		ANSI_CHARSET,               // Character Set Identifier
		OUT_TT_PRECIS,             // Output Precision
		CLIP_DEFAULT_PRECIS, // Clipping Precision  �ü�����
		ANTIALIASED_QUALITY,  // Output Quality 
		FF_DONTCARE | DEFAULT_PITCH, // Family And Pitch
		_T("����") );  //T("Arial" �޸�

	CDC* pDC=GetDC();
	CFont* m_pOldFont = pDC->SelectObject(&m_font);

    // create display lists for glyphs 0 through 255 with 0.1 extrusion 
    // and default deviation. The display list numbering starts at 1000 
    // (it could be any number) 
	m_2DTextList = glGenLists(256);


    // create display lists for glyphs 0 through 255 with 0.1 extrusion 
    // and default deviation. The display list numbering starts at 1000 
    // (it could be any number)
	wglUseFontBitmaps(pDC->GetSafeHdc(), 0, 255, m_2DTextList); 


	pDC->SelectObject(m_pOldFont);
}

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MBUTTONDOWN()
	ON_WM_MBUTTONUP()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// COpenGLView ��ͼ

void COpenGLView::OnDraw(CDC* /*pDC*/)
{
	m_nViewOpenGL.OnInitRenderOpenGL();
	SetBase();
	tagCVector fBoxCenter,fBoxSize;
	m_nViewOpenGL.GetBox( fBoxCenter,fBoxSize );	
			if( m_IsShowTow ) ShowTow();//Tow����
		if( m_IsShowStd ) ShowStd();//����std���ƣ�������ʱ����Ҫ�����������ƣ�һ���򿪣�һ������
		if(m_IsShowStl) ShowStl();
		if(m_IsShowErr) ShowChrom();

	
CDlg3DMeasureMatch *pApp=(CDlg3DMeasureMatch *)AfxGetApp( );

	m_nViewOpenGL.SwapBufferOpenGL();
}


// COpenGLView ���

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


BOOL COpenGLView::OnEraseBkgnd(CDC* /*pDC*/)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

// COpenGLView ��Ϣ�������

void COpenGLView::OnDestroy()
{
	CView::OnDestroy();

	m_nViewOpenGL.OnDestroyOpenGL();	
}

int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_nViewOpenGL.OnInitOpenGL(m_hWnd);
	Create2DTextLists();

	return 0;
}

void COpenGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_nViewOpenGL.OnSizeOpenGL(nType, cx, cy);	

    //CRect Rect;
	//GetClientRect(&m_ViewRect);
	m_fViewAspect=1.0;
	if( cx>0 )
	{
		//m_ViewRect.Height()/m_ViewRect.Width();
		m_fViewAspect=(double)cy/(double)cx;
	}
    
}

void COpenGLView::SetBase()
{
	//�������
	glPushMatrix();
	glLoadIdentity();


	double len_x,len_y;

	if( m_fViewAspect>1.0 )
	{
		len_x=m_BoxVec[m_BoxMaxSeq]*1.1;
		len_y=len_x*m_fViewAspect;
	}
	else
	{
		len_y=m_BoxVec[m_BoxMaxSeq]*1.1;
		len_x=len_y/m_fViewAspect;
	}


    glEnable(GL_DEPTH_TEST);
		glBegin(GL_POLYGON);//����� ����
			glColor3d(0.1,  0.0 ,  0.4);//r	OpenGLViewSplit/a
			glVertex3d(len_x, len_y, -1990.0);	
			glColor3d(0.1,  0.0 ,  0.4);//g	
			glVertex3d(-len_x, len_y, -1990.0); 
			glColor3d(0.95, 0.95, 0.95);	//b	
			glVertex3d(-len_x, -len_y, -1990.0); 
			glColor3d(0.95, 0.95, 0.95);	//r	
			glVertex3d(len_x, -len_y, -1990.0); 
		glEnd(); 
	glPopMatrix();
		//�����·�������ϵ

	double len_Axis=0.3*m_BoxVec[m_BoxMaxSeq],len_ReAxis=0.2*m_BoxVec[m_BoxMaxSeq];
	tagCVector scale_Vec(m_nViewOpenGL.GetScaling('o'));
	double scale_xVal=( scale_Vec.x>0.8 ? 1.0:(scale_Vec.x+0.0001) );
	double scale_yVal=( scale_Vec.y>0.8 ? 1.0:(scale_Vec.y+0.0001) );
	double scale_zVal=( scale_Vec.z>0.8 ? 1.0:(scale_Vec.z+0.0001) );

	if (!m_IsRotCen)
	{
		glLineWidth(2.0f);
		glBegin(GL_LINES);
		glColor3d(1.0,0.0,0.0);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(len_Axis/scale_xVal,0.0,0.0);
		glEnd();
		glBegin(GL_LINES);
		glColor3d(0.0,1.0,0.0);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(0.0,len_Axis/scale_yVal,0.0);
		glEnd();
		glBegin(GL_LINES);
		glColor3d(0.0,0.0,1.0);
		glVertex3d(0.0,0.0,0.0);
		glVertex3d(0.0,0.0,len_Axis/scale_zVal);
		glEnd();
		glLineWidth(1.0f);

		glPointSize(3.0);

		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_POINTS);

		glVertex3d(0.0, 0.0, 0.0);

		glEnd();
	}
		

	if( m_IsRotCen )
	{
		glBegin(GL_LINES);
			glColor3d(1.0,0.0,0.0);
			glVertex3d(m_RotCen[0],m_RotCen[1],m_RotCen[2]);
			glVertex3d(m_RotCen[0]+len_ReAxis/scale_xVal,m_RotCen[1],m_RotCen[2]);
		glEnd();

		glBegin(GL_LINES);
			glColor3d(0.0,1.0,0.0);
			glVertex3d(m_RotCen[0],m_RotCen[1],m_RotCen[2]);
			glVertex3d(m_RotCen[0],m_RotCen[1]+len_ReAxis/scale_yVal,m_RotCen[2]);
		glEnd();
		
		glBegin(GL_LINES);
			glColor3d(0.0,0.0,1.0);
			glVertex3d(m_RotCen[0],m_RotCen[1],m_RotCen[2]);
			glVertex3d(m_RotCen[0],m_RotCen[1],m_RotCen[2]+len_ReAxis/scale_zVal);
		glEnd();
		glLineWidth(1.0f);

		glPointSize(3.0);

			glColor3f(1.0, 0.0, 0.0);
			glBegin(GL_POINTS);
			
			glVertex3d(m_RotCen[0],m_RotCen[1],m_RotCen[2]);
			
		glEnd();
	}
}

int COpenGLView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//return 0;
	return CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
}

void COpenGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	this->SetFocus();
	m_nViewOpenGL.OnLButtonDown(nFlags,point);
	Invalidate();
	CView::OnLButtonDown(nFlags, point);
}

void COpenGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_nViewOpenGL.OnLButtonUp(nFlags,point);
	Invalidate();
	CView::OnLButtonUp(nFlags, point);
}

void COpenGLView::OnMButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	this->SetFocus();
	m_nViewOpenGL.OnMButtonDown(nFlags, point);
	Invalidate();

	CView::OnMButtonDown(nFlags, point);
}

void COpenGLView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_nViewOpenGL.OnMButtonUp(nFlags, point);
	Invalidate(FALSE);

	CView::OnMButtonUp(nFlags, point);
}

void COpenGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_nViewOpenGL.OnMouseMove(nFlags,point);
	Invalidate(FALSE);
	CView::OnMouseMove(nFlags, point);
}

BOOL COpenGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_nViewOpenGL.OnMouseWheel(nFlags, zDelta, pt);
	Invalidate(FALSE);
	glEnable(GL_NORMALIZE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void COpenGLView::ShowStd()
{
	if( m_TowOpt.IsStdEmpty() ) return ;

	const TDSVec3DPtNor &std_PSet( m_TowOpt.CRefStd() );

	glPointSize(2.0);
	TDSVec3DPtNorConIt pn_it;
	glBegin(GL_POINTS);
	for ( pn_it = std_PSet.begin() ; pn_it != std_PSet.end() ; ++pn_it )
	{
			glColor3d(0.8f, 0.8f, 0.8f);		//�����ʾ��ɫ
		glVertex3d(pn_it->x() , pn_it->y() ,pn_it->z());
	}
	glEnd();
	
}
void COpenGLView::ShowStl()
{
    const TDSVecFace &stl_PSet(m_TowOpt.CRefStl());
	if(stl_PSet.empty()){return;}
	CDS3DPt temp ;
	TDSVecFaceConIt pn_it;
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f,0.0f,0.0f);
	for ( pn_it = stl_PSet.begin() ; pn_it != stl_PSet.end() ; ++pn_it )
	{
		glColor3f(1.0f, 0.0f, 0.0f );
		glNormal3f(pn_it->m_nor.ux(),pn_it->m_nor.uy(),pn_it->m_nor.uz());
		glVertex3f(pn_it->m_pt1.x(),pn_it->m_pt1.y(),pn_it->m_pt1.z());
		glNormal3f(pn_it->m_nor.ux(),pn_it->m_nor.uy(),pn_it->m_nor.uz());
		glVertex3f(pn_it->m_pt2.x(),pn_it->m_pt2.y(),pn_it->m_pt2.z());
		glNormal3f(pn_it->m_nor.ux(),pn_it->m_nor.uy(),pn_it->m_nor.uz());
		glVertex3f(pn_it->m_pt3.x(),pn_it->m_pt3.y(),pn_it->m_pt3.z());
	}
	glEnd();

}
void COpenGLView::ShowTow()
{
	if( m_TowOpt.CRefTow1().empty() ) return ;

	const TDSVec3DPt &tow_SecSet( m_TowOpt.CRefTow1() );

	glPointSize(2.0);
	TDSVec3DPtConIt pn_it;
	glBegin(GL_POINTS);
	glColor3f(0.0f, 1.0f, 0.0f );	
	glPointSize(2.0);
		for ( pn_it = tow_SecSet.begin() ; pn_it != tow_SecSet.end() ; ++pn_it )
		{
			glVertex3d(pn_it->x() , pn_it->y() ,pn_it->z());
		}
	glEnd();
}
void COpenGLView::DrawCNString(const char* str)
{ 
	int len=0, i=0; 
	wchar_t * wstring; 
	HDC hDC=wglGetCurrentDC();
	GLuint list=glGenLists( 1 ); 
	for( i=0; str[i]!='\0'; i++ ) 
	{ 
		if ( IsDBCSLeadByte( str[i] )) 
			i++; 
		len++; 
	} 
	wstring=(wchar_t*)malloc((len+1)*sizeof(wchar_t)); 
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, str, -1, wstring, len ); 
	wstring[len]=L'\0';
	for( i=0; i<len; i++ ) 
	{ 
		wglUseFontBitmapsW( hDC, wstring[i], 1, list );  
		glCallList( list ); 
	} 
	free( wstring ); 
	glDeleteLists( list, 1 );
}
void COpenGLView::SelectFont(int size, int charset, const char* face) 
{  
	HFONT hFont = CreateFontA(size, 0, 0, 0, FW_MEDIUM, 0, 0, 0,  
		charset, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,  
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, face);  
	HFONT hOldFont = (HFONT)SelectObject(wglGetCurrentDC(), hFont);
	DeleteObject(hOldFont);
}
//ɫ��
void COpenGLView::ShowChrom()
{
	//ɫ�׻���������Ϣ,��������������ֵ����Ϊȫ�ֱ������������Ѿ�������
	//int m_nCol=13;
	int m_nDec=4; //С��λ��
	int nCol = m_nCol;  //��ɫ����
	int nColHalf = (nCol-1)/2;
	int decimal = m_nDec;  //С��λ��
	double deta, deta1, deta2;  //��ͬ����ɫ�仯��
	double UpSub, DownSub;  //ɫ���ϡ��²���ÿ���Ĳ�ֵ
	double AllRange = m_maxCri - m_minCri;  //ɫ�׵���ֵ��
	double UpEdge = m_maxCri - m_maxNom;  //ɫ���ϲ���ֵ��
	double DownEdge = m_minNom - m_minCri;  //ɫ���²���ֵ��
	double CentEdge = m_maxNom - m_minNom;  //ɫ���м�ֵ��
	CString dist;  //������ʾ������

	deta = 0.8/(double)nColHalf;  //���ò�ͬ����ɫ�仯��
	deta1 = 0.6/(double)nColHalf;
	deta2 = 1/(double)nColHalf;

	UpSub = UpEdge/(double)(nColHalf);  //ɫ���ϲ���ÿ���Ĳ�ֵ
	DownSub = DownEdge/(double)(nColHalf);  //ɫ���²���ÿ���Ĳ�ֵ

	//ɫ����ʾ������Ϣ
	double width = 3.6;  //ɫ����ʾ�Ŀ��Ϊ1.8
	double height = 60.0;  //ɫ����ʾ���ܳ���Ϊ30

	GLdouble glLeftGap = 1.0;  //����ɫ����߾�����߽����1.0
	GLdouble glLeft = -50.0+glLeftGap, glTop = 30.0;  //����ɫ�����Ͻ�����15.0
	GLdouble glGapY = width/10;  //ɫ��ÿ���ľ���
	GLdouble glTextGap = 1.0;  //��ʾ���־�ɫ���Ҳ�ľ���0.5

	double CenSubShape = (CentEdge)/AllRange*height; //�м�ģ��ĳ���
	double UpSubShape = ((UpEdge/AllRange*height)/nColHalf)-width/10;  //ɫ���ϲ���ÿ������ʾ����
	double DownSubShape = ((DownEdge/AllRange*height)/nColHalf)-width/10;//ɫ���²���ÿ������ʾ����
	GLdouble glRight = glLeft+width;
	GLdouble glLeftText = glRight+glTextGap;  //���ֵ���ʾλ��----ˮƽ����

	float mMatrix[16]={0.0};  //�����εı任����

	/*********************************** ����ɫ����״ͼ *************************************/
	//����ɫ����״ͼ��С��λ��
	CString strDecNum = "%.4f";  //ɫ����״ͼС��λ��

	glPushMatrix();
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -5.0f);

	//int nColHalf_1=nColHalf-1;
	//���ƽ���ɫ�飨�ϲ��֣�
	for(double i=0.0; i<nColHalf; i++)
	{
		glBegin(GL_POLYGON);//�������˳���ܱ䣡������POLYGON���Ķ����
		//OpenGLҪ��ָ�������������������glBegin����֮��  
        //glEnd����֮ǰ������ָ���Ķ��㽫�����ԣ�������glBegin��ָ�����ʹ����Щ��  
        //GL_POLYGON��ʾ������Σ��ɵ����ӳɶ���Σ�
		glColor3f(1, 0+deta*(i+1), 0);  //����ÿ��ɫ�����ɫ
		glVertex2f(glRight, (glTop-UpSubShape*(i+1)-i*glGapY));  //X����1.8��Y����0.2
		glColor3f(1, 0+deta*i, 0);
		glVertex2f(glRight,(glTop-(UpSubShape+glGapY)*i));
		glColor3f(1, 0+deta*i, 0);
		glVertex2f(glLeft,(glTop-(UpSubShape+glGapY)*i));
		glColor3f(1, 0+deta*(i+1), 0);  
		glVertex2f(glLeft, (glTop-UpSubShape*(i+1)-i*glGapY));  
		glEnd();
	}
	DrawCNString(" ");
	//���ɫ���Ե����֣��ϲ��֣�
	for(double i=0.0; i<(nColHalf); i++)
	{
		SelectFont(12, GB2312_CHARSET, "����_GB2312"); 
		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2f(glLeftText, (glTop-(UpSubShape+glGapY)*i));//�����ַ���ʼλ��
		dist.Format(strDecNum, m_maxCri-UpSub*i);//ʹ���κ���ʽתΪ�ַ���
		DrawCNString(dist);
	}
	
	//������ɫɫ�飨�м䲿�֣�                                    
	glBegin(GL_POLYGON);
	glColor3f(0, 1, 0);
	glVertex2f(glRight,(glTop-(UpSubShape+glGapY)*(nColHalf)-CenSubShape));
	glColor3f(0, 1, 0);
	glVertex2f(glRight,(glTop-(UpSubShape+glGapY)*(nColHalf)));
	glColor3f(0, 1, 0);
	glVertex2f(glLeft, (glTop-(UpSubShape+glGapY)*(nColHalf)));
	glColor3f(0, 1, 0);
	glVertex2f(glLeft, (glTop-(UpSubShape+glGapY)*(nColHalf)-CenSubShape));
	glEnd();

	
	//�����ɫɫ���Ե����֣��м䲿�֣�  �ڿ��ǵ������������ʾɫ�׻���������һ�����룬���м䲿����ʾ���ִ���ȡ����
	SelectFont(12, GB2312_CHARSET, "����_GB2312"); 
	glColor3f(0.0f,0.0f,0.0f);
	glRasterPos2f(glLeftText, (glTop-(UpSubShape+glGapY)*(nColHalf)));
	dist.Format(strDecNum, m_maxNom);
	DrawCNString(dist);

	glColor3f(0.0f,0.0f,0.0f);
	glRasterPos2f(glLeftText, (glTop-(UpSubShape+glGapY)*(nColHalf)-CenSubShape));
	dist.Format(strDecNum, m_minNom);
	DrawCNString(dist);
	
	for(double i=0.0; i<nColHalf; i++)//���ƽ���ɫ�飨�²��֣�
	{
		glBegin(GL_POLYGON);
		glColor3f(0.6-deta1*(i+1), 1-deta2*(i+1), 1);
		glVertex2f(glRight, (glTop-(UpSubShape+glGapY)*(nColHalf)-CenSubShape-(i+1)*(DownSubShape+glGapY)));

		glColor3f(0.6-deta1*(i), 1-deta2*(i), 1);
		glVertex2f(glRight, (glTop-(UpSubShape+glGapY)*(nColHalf)-CenSubShape-(i+1)*glGapY-DownSubShape*i));

		glColor3f(0.6-deta1*(i), 1-deta2*(i), 1);
		glVertex2f(glLeft, (glTop-(UpSubShape+glGapY)*(nColHalf)-CenSubShape-(i+1)*glGapY-DownSubShape*i));

		glColor3f(0.6-deta1*(i+1), 1-deta2*(i+1), 1);
		glVertex2f(glLeft, (glTop-(UpSubShape+glGapY)*(nColHalf)-CenSubShape-(i+1)*(DownSubShape+glGapY)));
		glEnd();
	}
	//���ɫ���Ե����֣��²��֣�
	for(double i=0.0;i<(nColHalf);i++)
	{
		SelectFont(12, GB2312_CHARSET, "����_GB2312"); 
		glColor3f(0.0f, 0.0f, 0.0f);
		glRasterPos2f(glLeftText,  (glTop-(UpSubShape+glGapY)*(nColHalf)-CenSubShape-(i+1)*(DownSubShape+glGapY)));
		dist.Format(strDecNum, (m_minNom-DownSub*i-DownSub));
		DrawCNString(dist);
	}
	glPopMatrix();

	/**********************************************/
	if(is_CalcChrom)
	{
		float detaCol, detaUp, detaDown;
		UpEdge = m_maxCri - m_maxNom;
		DownEdge = m_minNom - m_minCri;
		detaUp = UpEdge/(m_nCol/2-1);
		detaDown = DownEdge/(m_nCol/2-1);
		detaCol = (float)2.0/(float)m_nCol;

		if (!(newPtChrom.m_ptColor.empty()))
		{
			vector<CDS3DPtColor>::iterator iter;
			for (iter = newPtChrom.m_ptColor.begin(); iter != newPtChrom.m_ptColor.end(); ++iter)
			{
				float r = 0, g = 0, b = 0;
				//���λ������ֵ��Χ֮��
				if ((m_maxNom<iter->m_distErr) && (iter->m_distErr<m_maxCri))
				{
					for(int i=0; i<m_nCol/2; i++)
					{
						if ((m_maxCri-detaUp*(i+1)<iter->m_distErr) && (iter->m_distErr<m_maxCri-detaUp*i))
						{ r = 1;g = detaCol*1;b = 0; }
					}
				}
				//���λ������ֵ��Χ֮��
				else if ((m_minCri<iter->m_distErr) && (iter->m_distErr<m_minNom))
				{
					for(int i=0; i<m_nCol/2; i++)
					{
						if ((m_minCri+detaDown*i<iter->m_distErr) && (iter->m_distErr<m_minCri+detaDown*(i+1)))
						{ r = 0.6-detaCol*(i+1);g = 1-detaCol*(i+1);b = 1; }
					}
				}
				//���λ������ֵ��Χ֮��
				else if ((m_minNom<iter->m_distErr) && (iter->m_distErr<m_maxNom)) { r = 0;g = 1;b = 0; }
				//���С����С�ٽ�ֵ
				else if (iter->m_distErr< m_minCri) { r = 0;g = 1;b = 1; }
				//�����������ٽ�ֵ
				else if (iter->m_distErr > m_maxCri) { r = 1;g = 0;b = 0; }
				//�洢�������ɫ�ĵ�
				iter->r = r;
				iter->g = g;
				iter->b = b;
			}
		}
		is_CalcChrom = FALSE;
	}

    /**********************************************/

	//���Ƶ���
	vector<CDS3DPtColor>::iterator iter;
	glBegin(GL_POINTS);
	for (iter = newPtChrom.m_ptColor.begin(); iter != newPtChrom.m_ptColor.end(); ++iter)
	{
		if (iter->IsSelected()){glColor3f(0.0 , 1.0, 0.0 );}  //ѡ�е����ʾ��ɫ����ɫ��
		else{glColor3f(iter->r , iter->g, iter->b );}  

		glNormal3f(iter->ux(), iter->ux(), iter->ux());
		glVertex3f(iter->x() , iter->y() ,iter->z());
	}
	glEnd();
}
void COpenGLView::UpdatePCloud( bool is_std )
{
	bool is_box;
	if( is_tow )
	{
		m_TowOpt.GetTowCenPt( m_RotCen );
		is_box=m_TowOpt.GetTowBox( m_BoxVec );
		is_tow=FALSE;
	}
	else if( is_std )
	{
		m_TowOpt.GetStdCenPt( m_RotCen );
		is_box=m_TowOpt.GetStdBox( m_BoxVec );
	}
	else
	{
        m_TowOpt.GetStlCenPt(m_RotCen);
		is_box=m_TowOpt.GetStlBox(m_BoxVec);
	}

	
	m_BoxMaxSeq=0;
	m_BoxVec[0]*=0.5;
	for( int i=1;i<3;++i ) 
	{
		m_BoxVec[i]*=0.5;
		if( m_BoxVec[i]>m_BoxVec[m_BoxMaxSeq] ) m_BoxMaxSeq=i;
	}
 
	m_nViewOpenGL.SetBox( tagCVector( (float)m_RotCen[0], (float)m_RotCen[1], (float)m_RotCen[2] ), 
		tagCVector( (float)m_BoxVec[m_BoxMaxSeq], (float)m_BoxVec[m_BoxMaxSeq], (float)m_BoxVec[m_BoxMaxSeq] ) );

	m_IsRotCen=true;

	Invalidate();
}



void COpenGLView::RecoveryPCloud()
{
	tagCVector recipscale_Vec(tagCVector(1.0,1.0,1.0) );  //���Ÿ�ԭ   �����޸�
	m_nViewOpenGL.SetScaling('o',recipscale_Vec);

   tagCVector reciptranslate_Vec(tagCVector(0.0,0.0,0.0) );  //ƽ�Ƹ�ԭ
	m_nViewOpenGL.SetTranslate('o',reciptranslate_Vec);

	tagCVector rotate_Vec(m_nViewOpenGL.GetScaling('o'));  //��ת��ԭ
	tagCVector recip_Rotate_Vec(tagCVector(0.001f,0.001f,0.001f) );
	m_nViewOpenGL.SetRotateCenter('o',recip_Rotate_Vec);
	 GLdouble matrix4[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}};
	m_nViewOpenGL.SetRotate ('o',matrix4);

	Invalidate();
}


void COpenGLView::drawCNString( const char * str )
{ 
	int len=0, i=0; 
	wchar_t * wstring; 
	for( i=0; str[i]!='\0'; i++ ) 
	{ 
		if( IsDBCSLeadByte( str[i] )) 
			i++; 
		len++; 
	} 

	wstring=(wchar_t*)malloc((len+1)*sizeof(wchar_t)); 
	MultiByteToWideChar( CP_ACP
		, MB_PRECOMPOSED, str, -1, wstring, len ); 
	wstring[len]=L'\0';
	GLuint list=glGenLists( 1 );
	CDC* pDC=GetDC();
	for( i=0; i<len; i++ ) 
	{ 
		CFont* m_pOldFont = pDC->SelectObject(&m_Font);
		
		wglUseFontBitmapsW( pDC->GetSafeHdc(), wstring[i], 1, list );
		pDC->SelectObject(m_pOldFont);
		glCallList( list );
		
	} 
	free( wstring ); 
	glDeleteLists( list, 1 ); 
}





