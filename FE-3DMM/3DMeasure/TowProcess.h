

#ifndef _TOWPROCESS_H
#define _TOWPROCESS_H

#include "DataStructure.h"
//#include "..\DataStructure\DataTopology.h"

#define TowFileLineCharNum 1024
#define TowFileCharNum 32

#define TowFileOrigin "tow"
#define TowFileHead "TOW"
#define TowFileHeadPd "TPD"
#define TowFilePosed "tpd"
#define TowFileStd "tsd"

#define TowLineMinNum 2

#define TowKnnNum 12
#define TowDenoisyCos 0.1
#define TowZeroRange 0.05
#define TowZeroRangeSq 1.0e-4

#define TowStdZeroPerc 0.3

#define TowStdBldMaxAdf 0.5
#define TowStdBldMinAdf 1.0e-4

#define TowSmoothCov 1.0e-5

#define TowStdMaxNum 40000 //��׼���Ƶ�������
#define TowMeaMaxNum 25000 //�������Ƶ�������

#define TowStdMeaRatio 1.732

#define TowSmoothMaxNum 2
#define TowSimpMinRate 1.1
#define TowSimpMaxErr 0.01

class /*DS_API_EXPORT*/ CTowTop
{
public:
	CTowTop();
	~CTowTop();
	CTowTop( const TDSVec23DPt& vec2_SecSet, TDSVec3DPtNor& vec_PSetNor );
	CTowTop( TDSVec3DPtNor& vec_PSetNor );

	void MInfOfPSet( const TDSVec3DPtNor& vec_PSet, CDS3DPt& max_XYZ, CDS3DPt& min_XYZ );
	void CreIndexPSet( const int num_k, const TDSVec3DPtNor& vec_PSet, 
		               TDSVec2Int& vec2_KNNSeq, TDSMapIntVecInt& map_IndexPSet );
	//void SearchKNN( const int num_k, const TDSVec3DPtNor& vec_PSet, 
	//	            TDSVec2Int& vec2_KNN);

	void MInfOfPSet( const TDSVec3DPt& vec_PSet, CDS3DPt& max_XYZ, CDS3DPt& min_XYZ );
	void CreIndexPSet( const int num_k, const TDSVec3DPt& vec_PSet, 
		               TDSVec2Int& vec2_KNNSeq, TDSMapIntVecInt& map_IndexPSet );
	void SearchKNN( const int num_k, const TDSVec3DPt& vec_PSet, 
		            TDSVec2Int& vec2_KNN);

	void CalNor( const int num_k, const TDSVec3DPt& vec_PSet, TDSVec3DPtNor& vec_PSetNor );
	void CalNor( const int num_k, TDSVec3DPtNor& vec_PSetNor );

	void LSFit( const TDSVec3DPt& vec_Pt, double *arr_Nor );
	void LSFitNor( const TDSVec3DPt& vec_Pt, double *arr_Nor, double &surf_var );
};



class /*DS_API_EXPORT*/ CTowPreOpt
{
public:
	CTowPreOpt(void);
	//CTowPreOpt( const char* file_Name );
	~CTowPreOpt(void);

	bool Read( const char* file_Name, string& err_Str );//char*
	bool Read( const char* file_Name, string& err_Str, TDSVec3DPtNor& vec_PSet );
	void SetPSet( const TDSVec23DPt& vec2_PSet );

	void SmoothPSet();
	void SmoothPSet( int num_Simp );
	void SimpPSet();
	void SimpPSet( int num_Simp ); //��������ͭ�����ƽ��о���

	inline bool IsEmpty() const { return m_PSetOrg.empty(); }
	bool IsValid() const { return m_PSet.empty(); }
	int GetPtNum() const { return m_PtNum; }
	TDSVec23DPt GetSecSet() const { return m_PSet; }
	const TDSVec23DPt &RefSecSet() const { return ( m_PSet.empty() ? m_PSetOrg:m_PSet ); }
	TDSVec23DPt GetSecSetOrg() const { return m_PSetOrg; }

	//��ȡ��С��Χ��
	void GetBox( CDS3DPt& box_CenPt, CDS3DPt& box_MinPt, CDS3DPt& box_MaxPt ) const;

	void clear() { m_PSetOrg.clear();m_PSet.clear(); }
protected:
    void Sift();
	void DenoisySec( TDSVec3DPt& vec_Pt );
	void SimpSec( TDSVec3DPt& vec_Pt ); //�����߽��о���
	void SmoothSec( TDSVec3DPt& vec_Pt, bool is_Reverse ); //�����߽��й�˳

protected:
	TDSVec23DPt m_PSetOrg;
	TDSVec23DPt m_PSet;
	int m_PtNum;
	double m_Delta;
	bool m_IsValid;

	//��̬�����ͺ����Ķ���
public:
	static void SetSmoothIter( const int smooth_Iter ) { m_SmoothIter=smooth_Iter; }
	static int GetSmoothIter() { return m_SmoothIter; }
	static void SetSmoothCoef( const double smooth_Coef ) { m_SmoothCov=smooth_Coef; }
	static double GetSmoothCoef() { return m_SmoothCov; }
protected:
	static double m_SmoothCov;
	static int m_SmoothIter;
};

class /*DS_API_EXPORT*/ CTowMea
	: public CTowPreOpt
{
public:
	CTowMea();
	//CTowMea( const char* file_Name );
	~CTowMea();

	//void PreTow( const char* file_Name );
	void PreTow( int num_Simp ); //��˳��ͬʱ���о���
	void StdTow( int num_Simp, TDSVec3DPtNor& vec_PtNor ); //��˳��ͬʱ���о���
	bool Write( const char* file_Name );

	TDSVec3DPt GetPSet() const;
};

class /*DS_API_EXPORT*/ CTowStd
{
public:
	CTowStd();
	~CTowStd();

	//void SetPSet( const char* file_Name, const char* file_Ext );
};

class /*DS_API_EXPORT*/ CTowFile
{
public:
	//�ļ���ȡ
	//��������ʽ��ȡ��tow��ʽ
	//static bool OpenTowFile( const char* tow_Name, TDSVec3DPtNor& out_PCloud );
	//��׼�ļ���std
	static bool OpenTowStdFile( const char* std_Name, TDSVec3DPtNor& out_PCloud );
	//һ���ļ���ȡ������asc��txt��dat��vtx��
	static bool OpenGeneralFile( const char* gen_Name, bool& is_Nor, TDSVec3DPtNor& out_PCloud );
	//igs�ļ���ȡ
	static bool OpenIgsFile( const char* igs_Name, TDSVec3DPtNor& out_PCloud );
	//pcd�ļ���ȡ���������ĸ�ʽ
	//static bool OpenIgsFile( const char* pcd_Name, TDSVec3DPtNor& out_PCloud );

	//�ļ�����
	static bool SaveGeneralFile( const char* gen_Name, const bool sym_Norm, 
		                         const TDSVec3DPtNor& in_PCloud );
	static bool SaveTowStdFile( const char* std_Name, const TDSVec3DPtNor& in_PCloud );
};
#endif