

#ifndef _TOWOPERATION_H
#define _TOWOPERATION_H

#include "afxcmn.h"
#include "TowProcess.h"
//#include "..\iCloudOpenGL\OpenGLView.h"
//#include " "
//#include <fstream>
//using std::ifstream;
//using std::ofstream;

#define TowChromFile "TOWCHROM"
#define TowChromFileNum 8

class CTowOpt
{
	////////��������
public: 
	//COpenGLView *hdglview;
public:
	//1107
	//void Sethdview(COpenGLView *mviewk){hdglview=mviewk;}
	static void SetMea( const TDSVec23DPt& mea_PSet ); //ͨ���������ݣ����ò�������

	static void ReadMea(); //��ȡ��������
	static void ReadMea( const CString& mea_File ); //��ȡ��������

	static void WriteMea(); //�����������
    static void WriteMea( const CString& mea_File ); //����������Ƶ�ָ�����ļ�
	static inline const TDSVec3DPt& CRefTow1() { return m_TowSet; } //��ȡ��׼����
	static inline const TDSVec23DPt &CRefTow() { return m_TowMea.RefSecSet(); } //��ȡ��������
	static const TDSVecFace  &CRefStl(){return in_TriSet;}
	static inline bool IsTowEmpty() { return m_TowMea.IsEmpty(); }
	static TDSVec3DPt GetTow() { return m_TowMea.GetPSet(); } //��ȡ��������

	static CDS3DPt GetTowCenPt() { return m_TowCenPt; }
	static void GetTowCenPt( double cen_Pt[3] );
	static CDS3DVec GetTowBox() { return CDS3DVec( m_TowMaxPt-m_TowMinPt ); }
	static bool GetTowBox( double box_Vec[3] );
	static void CalTowCenPt();

private:
	
	static CDS3DPt m_TowCenPt,m_TowMaxPt,m_TowMinPt; //�������Ƶ����ĵ�
public:
	static TDSVec3DPt m_TowSet; //��׼���ĵ���
	static CTowMea m_TowMea; //ͭ����������

	///////////��׼����
public:
	//ͨ�������������ñ�׼����
	static void SetStd( const TDSVec23DPt& vec_StdSet ); 
	//ͨ���ļ������ñ�׼����
	static void ReadStdFile( const CString& std_File, const CString& file_Ext ); 
	static void ReadStd();  //���򿪶Ի���
	//��׼���Ƶ��ļ��򿪺�׺
	static CString StdOpenExt(); //�򿪵��ض��ļ�

	//�����׼����
	static void WriteStdFile( CString& path_Name, CString& file_Ext ); 
	static void WriteStd();  //������Ի���
	//��׼���Ƶ��ļ������׺
	static CString StdSaveExt(); //�ض����ļ�����
	
	//������׼���ĵ���
	//static void PoseStd( bool is_mess=true ); 

	//static const TDSVec3DPtNor& CRefStd() { return m_StdSet; }
	//��ȡ��׼�������ĵ�
	static inline CDS3DPt GetStdCenPt() { return m_StdCenPt; }
	static void GetStdCenPt( double cen_Pt[3] );
	//��ȡ��Χ�г���
	static inline CDS3DVec GetStdBox() { return CDS3DVec( m_StdMaxPt-m_StdMinPt ); } 
    static bool GetStdBox( double box_Vec[3] );

	static TDSVec3DPtNor GetStd() { return m_StdSet; } //��ȡ��׼����
	static inline const TDSVec3DPtNor& CRefStd() { return m_StdSet; } //��ȡ��׼����
	static inline bool IsStdEmpty() { return m_StdSet.empty()&&m_StdMea.IsEmpty(); } //�жϱ�׼�����Ƿ�Ϊ��
	
public:
	static inline bool IsMea() { m_IsMea&&(!m_IsStd); }
	static void CalStdCenPt();

public:
	static TDSVec3DPtNor m_StdSet; //��׼���ĵ���
	static CTowMea m_StdMea; //ͨ��������ȡ�ı�׼���ƣ����һ����׼��

	static CDS3DPt m_StdCenPt,m_StdMaxPt,m_StdMinPt;
	static bool m_IsStd;
	static bool m_IsNor;
	static bool m_IsMea;
	static CDS3DPt m_StlCenPt,m_StlMaxPt,m_StlMinPt;

	static TDSVecFace in_TriSet;
public:
	static void ReadStl();
	static void ReadStlFile(const CString& stl_File);
	static bool GetStlBox( double box_Vec[3] );
	static void GetStlCenPt( double cen_Pt[3] );
	static inline CDS3DPt GetStlCenPt() { return m_StlCenPt; }
	static inline CDS3DVec GetStlBox() { return CDS3DVec( m_StlMaxPt-m_StlMinPt ); } 

private:
    static void CalStlCenPt();

	//////������
public:
	//���������ƺͱ�׼���ƶ�����ʱ��ִ�е������Աȣ������ֹ�������true��ʾ����ƴ�������Ϣ��ִ��ʱ��
	static void RunBlend( bool is_BldMess=true ); 
	//�����ڱ�׼����ʱ�����ò������Ƽ����Զ�ִ�����������ֱ�����������Ϣ�������Զ����Ĺ���
	static void RunAll( const TDSVec23DPt& vec_PSet ); 
	//�����ڱ�׼����ʱ����ȡ�ļ��Ĳ������ݣ����Զ�ִ�����������ֱ�����������Ϣ
	static void RunAll( const CString& mea_File ); 
	//�����ļ��ĶԻ��򣬻�ȡ�������Ƶ��ļ��������Զ�ִ�У�ֱ�����������Ϣ
	static void RunAll(); 
	//������׼���ĵ���
	static void PoseStd( bool is_mess=true ); 
	//��ȡ�����Ϣ��
	static const CDSChrom& CRefError() { return m_ErrChrom; } 
	//��ȡ�����Ϣ�ļ�����׺��ͳһΪ"chr"��"CHR"
//	static void ReadError(); 
//	static bool ReadError( const char* chr_File ); 
	//��������Ϣ�ļ�����׺��ͳһΪ"chr"��"CHR"
//	static void WriteError();
//	static bool WriteError( const char* chr_File );
//	static CString ErrorExt(); //����ļ��ĺ�׺����׺��ͳһΪ"chr"��"CHR"
private:
	static CDSChrom m_ErrChrom; //�������Ƶ������Ϣ

public:
	//���ɫ��ͼ��ʾ����
	//static void SetMaxErr();
	static void SetValidErr( const double err_Valid ); //������Ч��Χ Ĭ��Ϊ  avg+2*VAR
	static void SetLimitErr( const double err_Limit );//���ü�����Χ  Ĭ��Ϊ  avg+3*VAR
	static void SetFirTolePerc( const double perc_FirTole ); //������Ч����ݲ��� Ĭ��Ϊ 5%
	static void SetSecTolePerc( const double perc_SecTole ); //���ü�������ݲ���  Ĭ��Ϊ2%
	static void SetSegNum( const int num_Seg ); //����ɫ�׶���
//	static bool IsEligible(); //ͭ���Ƿ�ϸ� 
//	static void UpdateChrom(); //�������ɫ��ͼ

	//���������趨
	//static void SetBldTimes();
	//static void SetBldCoef();

	//static void SetMeaPtNum();
	//static void SetBldPtNum();
};

#endif