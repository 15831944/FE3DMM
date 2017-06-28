#pragma once
//#include "afxcmn.h"
#include "DataStructure.h"
#include "kdtree.h"

#define TowBldNum 15
#define TowBldAdf 0.05
// CTowADF 
class /*DS_API_EXPORT*/ CTowBlend
{
public:
	CTowBlend();
	CTowBlend( const TDSVec3DPt& mov_PSet, const TDSVec3DPtNor& fix_PSetN );
	~CTowBlend();

	virtual void Blend( CDSChrom& res_Err )=0;
	

	//���ڽ��������Ƶ���������ƽ�Ƶ�һ��
	void MovePCloud(TDSVec3DPtNor& ptMoving, TDSVec3DPtNor& ptFixed);
	void MovePCloud();

	void KdtreeSearch();
	void CreateKdtree( kdtree *ptree, int *data );
	void SearchNearest( kdtree *ptree );
	void MatrixCross(double x1[3], double x2[3],double y[3]);
	void InverseMatrix6(long double A[6][6], int n, long double B[6][6]);
	void InverseMatrix4(double A[4][4], int n,double B[4][4]);


	double m_blendMatrix[4][4];
	void CalculateBlendMatrix(double blendMatrix[4][4], const double RTMatrix[4][4]);

protected:
	TDSVec3DPt m_ptMoving;	//�ƶ��㼯
	TDSVec3DPtNor m_ptFixed;	//�̶��㼯

	TDSVec3DPtNor m_ptNearest;	//�ƶ��㼯�ڹ̶��㼯�ж�Ӧ�������

public:
	static void SetIterTimes( const int iter_Times ) { m_nIterTimes=iter_Times; }
	static int GetIterTimes() { return m_nIterTimes; }
protected:
	static int m_nIterTimes;
};

class /*DS_API_EXPORT*/ CTowADF
	: public CTowBlend
{
public:
	CTowADF();
	CTowADF( const TDSVec3DPt& mov_PSet, const TDSVec3DPtNor& fix_PSetN );
	~CTowADF();

	virtual void Blend( CDSChrom& res_Err );
	void Blend2( CDSChrom& res_Err );

	void DoADF();
	void DoADF2();
public:
	static void SetAdfCoef( const double coef_Adf ) { Adfmu=coef_Adf; }
	static double GetAdfCoef() { return Adfmu; }
protected:
	static double Adfmu; //ƴ��ϵ��
	//map<int, vector<CDS3DPtNor>> m_mapStorePCloud;	//���ڵ�ǰִ�в����ĸ��ֵ���
	//int m_nMapIndex;	//��¼��������
};

class /*DS_API_EXPORT*/ CTowICP
	: public CTowBlend
{
public:
	CTowICP();
	CTowICP( const TDSVec3DPt& mov_PSet, const TDSVec3DPtNor& fix_PSetN );
	~CTowICP();

	virtual void Blend( CDSChrom& res_Err );

	void DoICP();
};

