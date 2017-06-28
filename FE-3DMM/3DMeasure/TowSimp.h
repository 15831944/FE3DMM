#pragma once
//#include "afxcmn.h"
#include "DataStructure.h"


class /*DS_API_EXPORT*/ TowSimpInterData
{
public:
	bool SimpEnterYes;
	bool SimpCancelNo;
	int  SimpNumber;
	TDSVec3DPtNor SimpData;
};

class /*DS_API_EXPORT*/ TowSimpCovEigData
{
public:
	double EigVal;
	CDS3DPt EigVec;
	TowSimpCovEigData(double val,CDS3DPt vec)
	{
		EigVal=val;
		EigVec=vec;
	}
};

class /*DS_API_EXPORT*/ TowSimpBase
{
protected:
	// ���ھ���ĵ��Ƶ��������ֵ
	CDS3DPt PCloud_MaxXYZ;
	// ���ھ���ĵ��Ƶ���С����ֵ
	CDS3DPt PCloud_MinXYZ;
	// ���ھ���ĵ��Ƶ���С��Χ�и��߱߳�
	CDS3DPt PCloud_LXYZ;
public:
	// ������ĵ���
	TDSVec3DPtNor SimpPCloud;
	// ����ǰ����CurrentPCloud�����ݣ����ڸ������ݾ���
	//int SimpOperNum;
protected:
	double DotP3D(const CDS3DPt &p3d1,const CDS3DPt &p3d2);
public:
	TowSimpBase(void);
	TowSimpBase( const TDSVec3DPtNor& in_PCloud );
    TowSimpBase( const TDSVec3DPtNor& in_PCloud, 
		         const CDS3DPt box_MaxPt, const CDS3DPt box_MinPt );
	TowSimpBase(bool SimpInfoJud);
public:
	~TowSimpBase(void);
public:
	void InfOfPSet(const TDSVec3DPt& PSet, CDS3DPt& Max_XYZ, CDS3DPt& Min_XYZ);
	void InfOfPSetNor( const TDSVec3DPtNor& PSet, CDS3DPt& Max_XYZ, CDS3DPt& Min_XYZ );
	bool SimpCreIndexPCloud(double SampleSpace,map<int,TDSVec3DPtNor>& SimpIndexPCloud);
public:
	// ���ڼ��ľ��Ȳ���
	bool SimpUniform_Spacce(double SampleSpace,TDSVec3DPtNor& temp_SimpPCloud);
	// ���ڵ����ľ��Ȳ���
	bool SimpUniform_Number(int SampleNum, TDSVec3DPtNor& temp_SimpPCloud);
public:
	CDS3DPtNor MinPToPSetCenter(const TDSVec3DPtNor PointSet);

	void GetXYZAxisData(const TDSVec3DPtNor& PointSet, TDSVecDou& XData_PSet, TDSVecDou& YData_PSet, TDSVecDou& ZData_PSet);
	
public:
	void GetCenterOfPSet(const TDSVec3DPtNor& PointSet, CDS3DPt& CenterPSet);
	void GetPSetSubCenter(const TDSVec3DPtNor& PointSet, vector<CDS3DPt>& PointSetSubCen);//vector<double> &SqureDistToCen);
public:
	void LeastSquareFit(const vector<CDS3DPt>& PointSetSubCen, vector<TowSimpCovEigData>& EigValAndVec);
	void OCTXYZSpi(const TDSVec3DPtNor& PSet, map<int,TDSVec3DPtNor>& OCTPSet);
	
	
public:
};


/****************************���Ȳ�������������****************************/

class/* DS_API_EXPORT*/ TowSimpUniform:public TowSimpBase
{
public:
	TowSimpUniform();
	TowSimpUniform( const TDSVec3DPtNor& in_PCloud );
	TowSimpUniform( const TDSVec3DPtNor& in_PCloud, 
		            const CDS3DPt box_MaxPt, const CDS3DPt box_MinPt );
	~TowSimpUniform();

	void GridIndexPSet( const double SampleSpace, const TDSVec3DPtNor& PSet, map<int,TDSVec3DPtNor>& IndexPSet );
	bool SimpUniSamBySpacce( const double SampleSpace,TDSVec3DPtNor& temp_SimpPCloud );

	//���ڼ��ľ��Ȳ���	
	bool SimpUniSam_Space( const double SampleSpace,TDSVec3DPtNor& NewPCloud );//���ڼ��Ĳ�������
	//���ڵ����ľ��Ȳ���	
	void CreIndexPSet( const double SampleSpace, vector<int>& IndexOfPSet );//Ϊ���ھ���ĵ��ƴ���դ��������
	int  GridNum( const vector<int>& Grid_P );//ͳ��դ������	
	void GetSpacForNum( const int SamNum, double& SamSpac, vector<int>& IndexOfPSet );//��������������ȡ���ʲ������
	bool SimpUniSam_Number( const int SamNum, TDSVec3DPtNor& NewPCloud );//���ڵ����Ĳ�������

};
/****************************���Ȳ�������������****************************/

/****************************�����������������****************************/
class /*DS_API_EXPORT*/ TowSimpRandom:public TowSimpBase
{
public:
	void RanNumForm(const int CurAllNum, const int CurRanNum, vector<int>& vec_KeepSeq);
	void RanSpiPSet(const TDSVec3DPtNor& PSet, map<int,TDSVec3DPtNor>& map_SpiPSet);
	void RanSamByNum(const int CurRanNum, const TDSVec3DPtNor& PSet, TDSVec3DPtNor& SamPSet);
public:
	bool SimpRanSam(int RanNum, TDSVec3DPtNor& temp_SimpPCloud);
};
/****************************�����������������****************************/

/****************************��ξ�������������****************************/
class/* DS_API_EXPORT*/ TowSimpClusBSP
{
public:
	int pointnum;
	bool fullsym;
	double surfvar;
	TowSimpClusBSP *BSPLeft;
    TowSimpClusBSP *BSPRight;
};

class /*DS_API_EXPORT*/ TowSimpCluster:public TowSimpBase
{
private:
	int NumThr;
	double VarThr;
	TDSVec3DPtNor BSPPCloud;
public:
    TowSimpCluster();
	~TowSimpCluster();
public:
	void BSPLSFInfo(const TDSVec3DPt& PointSetSubCen, CDS3DPt &VecOfMaxEigVal, double &SurfVar, bool varsym=false);
	void BSPLRSpi(const TDSVec3DPtNor& PSet, const TDSVec3DPt& PSetSubCen, const CDS3DPt &SpiDirec,TDSVec3DPtNor& LeftPSet, TDSVec3DPtNor& RightPSet);
	void BSPCreate(const TDSVec3DPtNor& PSet,TowSimpClusBSP *BSP);
	void BSPCreate(const TDSVec3DPtNor& PSet);
	void BSPCreateByNum(const int thr_num, const TDSVec3DPtNor& PSet, map<int,TDSVec3DPtNor>& map_SpiPSet);
	void BSPCreateByVar(const TDSVec3DPtNor& PSet);
	void BSPCreateByVar(const double thr_var, const map<int,TDSVec3DPtNor>& map_SpiPSet, TDSVec3DPtNor& ClusPCloud);
	bool SimpHieClus(const int numthr, const double varthr, TDSVec3DPtNor& ClusPCloud);
};
/****************************��ξ�������������****************************/

/****************************���ʲ�������������****************************/
class /*DS_API_EXPORT*/ TowSimpCurvature:public TowSimpBase
{
public:

};
/****************************���ʲ�������������****************************/
