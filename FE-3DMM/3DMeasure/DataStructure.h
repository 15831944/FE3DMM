
#define dll_API _declspec(dllimport)
#ifndef _DATASTRUCTURE_H_
#define _DATASTRUCTURE_H_

//C++标准头文件
#include <fstream>
using std::fstream;
using std::ios;

#include <math.h>

#include <vector>
#include <map>
#include <set>
#include <deque>
#include <list>
#include <hash_map>
#include <hash_set>
#include <string>

using std::vector;
using std::map;
using std::set;
using std::list;
using std::deque;
using std::multimap;
using std::string;
using stdext::hash_map;
using stdext::hash_set;

#include <numeric>
#include <algorithm>

#define DSZeroRange 1.0e-7 //零值表示的范围大小
#define DSCtrlError 1.0e-6  //计算控制精度
#define DSMinusInf -1.0e6  //计算控制精度

#define MAXl 1.0e7           //
#define MINl 1.0e-5          //
#define CVPI  3.141592653589793 
#define MTX_AMT 5000
#define MAX2 10
#define UndoMaxNum 8
#define CAD_ZERO 1.0E-6
#define NC_ZERO	1.0E-3
#define IS_ZERO(x) (fabs(x)<=CAD_ZERO)
#define IS_NCZERO(x) (fabs(x)<=NC_ZERO)
#define IS_BETWEEN(x,min,max) (x<=max && x>=min)

#ifndef DSPI
#define DSPI CV_PI  //PI值定义3.1415926535897932384626433832795
#endif


#define UndoMaxNum 8


typedef vector<int> TDSVecInt;
typedef TDSVecInt::iterator TDSVecIntIt;
typedef TDSVecInt::const_iterator TDSVecIntConIt;

typedef vector<TDSVecInt> TDSVec2Int;
typedef TDSVec2Int::iterator TDSVec2IntIt;
typedef TDSVec2Int::const_iterator TDSVec2IntConIt;

typedef map<int,TDSVecInt> TDSMapIntVecInt;
typedef TDSMapIntVecInt::iterator TDSMapIntVecIntIt;
typedef TDSMapIntVecInt::const_iterator TDSMapIntVecIntConIt;

// template  class DS_API_EXPORT std::allocator<double>;
// template  class DS_API_EXPORT std::vector<double>;
typedef vector<double> TDSVecDou;
typedef TDSVecDou::iterator TDSVecDouIt;
typedef TDSVecDou::const_iterator TDSVecDouConIt;

typedef vector<TDSVecDou> TDSVec2Dou;
typedef TDSVec2Dou::iterator TDSVec2DouIt;
typedef TDSVec2Dou::const_iterator TDSVec2DouConIt;

//template  struct DS_API_EXPORT std::pair<double,int>;
//template  class DS_API_EXPORT std::
//template  class DS_API_EXPORT std::allocator<int>;
//template  class DS_API_EXPORT std::map<double,int>;
typedef map<double,int> TDSMapDouInt;
typedef TDSMapDouInt::iterator TDSMapDouIntIt;
typedef TDSMapDouInt::const_iterator TDSMapDouIntConIt;

typedef set<int> TDSSetInt;
typedef TDSSetInt::iterator TDSSetIntIt;
typedef TDSSetInt::const_iterator TDSSetIntConIt;

typedef vector<TDSSetInt> TDSVecSetInt;
typedef TDSVecSetInt::iterator TDSVecSetIntIt;
typedef TDSVecSetInt::const_iterator TDSVecSetIntConIt;


class CDS3DPt;    
class CDS3DPtNor; 

class CDS3DVec; 

class CDS3DUnVec; 


class CMesh;

typedef vector<CDS3DPt> TDSVec3DPt;
typedef TDSVec3DPt::iterator TDSVec3DPtIt;
typedef TDSVec3DPt::const_iterator TDSVec3DPtConIt;


typedef vector<TDSVec3DPt> TDSVec23DPt; //存储没有法矢的点集
typedef TDSVec23DPt::iterator TDSVec23DPtIt;
typedef TDSVec23DPt::const_iterator TDSVec23DPtConIt;

typedef TDSVec23DPt::reverse_iterator TDSVec23DPtReIt;


typedef vector<CDS3DVec> TDSVec3DVec;
typedef TDSVec3DVec::iterator TDSVec3DVecIt;
typedef TDSVec3DVec::const_iterator TDSVec3DVecConIt;


typedef vector<CDS3DUnVec> TDSVec3DUnV;
typedef TDSVec3DUnV::iterator TDSVec3DUnVIt;
typedef TDSVec3DUnV::const_iterator TDSVec3DUnVConIt;



typedef vector<CDS3DPtNor> TDSVec3DPtNor; 
typedef TDSVec3DPtNor::iterator TDSVec3DPtNorIt;
typedef TDSVec3DPtNor::const_iterator TDSVec3DPtNorConIt;


typedef vector<TDSVec3DPtNor> TDSVec23DPtNor; 
typedef TDSVec23DPtNor::iterator TDSVec23DPtNorIt;
typedef TDSVec23DPtNor::const_iterator TDSVec23DPtNorConIt;

typedef vector<CMesh> TDSVecFace;
typedef TDSVecFace::iterator TDSVecFaceIt;
typedef TDSVecFace::const_iterator TDSVecFaceConIt;

class dll_API CDS3DPt 
{	
public:
	//CDS3DPt( const CDS3DPt& pt );
	inline CDS3DPt( double xyz_c[3] )
	{ coord[0]=xyz_c[0]; coord[1]=xyz_c[1]; coord[2]=xyz_c[2]; }
	inline CDS3DPt( double xa=0.0, double yb=0.0, double zc=0.0) 
	{ coord[0]=xa; coord[1]=yb; coord[2]=zc; }

	~CDS3DPt() {}

	CDS3DPt operator + (const CDS3DPt &pt3d); 
	CDS3DPt operator + (const CDS3DVec &vec3d); 
	CDS3DPt operator + (const CDS3DUnVec &uv3d); 
	CDS3DPt operator + ( const double &pc ); 
	CDS3DPt operator - (); 
	CDS3DPt operator - (const CDS3DPt &pt3d);
	CDS3DPt operator - (const CDS3DVec &vec3d); 
	CDS3DPt operator - (const CDS3DUnVec &uv3d); 
	CDS3DPt operator / (const double &dc);  //该点缩放后得到的新点，不推荐使用，尽量用*

	double  operator * (const CDS3DUnVec &uv3d); 
	CDS3DPt operator * (const double &sc);       //该点缩放后得到的新点，推荐使用，尽量不用/
	bool    operator == ( const CDS3DPt &pt3d ); //判断两个点是否为同一个点
	CDS3DPt operator += (const CDS3DPt &pt3d);
	CDS3DPt operator += (const CDS3DVec &vec3d);
	CDS3DPt operator += (const CDS3DUnVec &uv3d); //表示坐标点自身正向平移一个单位向量
	CDS3DPt operator += ( const double &pc ); //表示坐标点自身的三个坐标值同时加上一个常数
	CDS3DPt operator -= (const CDS3DPt &pt3d);
	CDS3DPt operator -= (const CDS3DVec &vec3d);
	CDS3DPt operator -= (const CDS3DUnVec &uv3d); //表示坐标点自身负向平移一个单位向量
	CDS3DPt operator /= (const double &sc);	
	CDS3DPt operator *= (const double &sc);


public:
	inline void setxyz( const int seq, const double newc ) { coord[seq]=newc; }
	inline void setx( const double newc ) { coord[0]=newc; }
	inline void sety( const double newc ) { coord[1]=newc; }
	inline void setz( const double newc ) { coord[2]=newc; }

	inline double& x() { return coord[0]; }
	inline double& y() { return coord[1]; }
	inline double& z() { return coord[2]; }

	inline double x() const { return coord[0]; }
	inline double y() const { return coord[1]; }
	inline double z() const { return coord[2]; }



	double xyz( const int seq ) const { return coord[seq]; }

	double dis0_sq(); //该点到原点距离的平方
	double dis0();    //该点到原点的距离



protected:
	double coord[3];
};

class dll_API CDS3DVec
{
public:
    inline CDS3DVec( double xi=0.0, double yj=0.0, double zk=0.0 )
	{ vec[0]=xi; vec[1]=yj; vec[2]=zk; }

    inline CDS3DVec( const double vec3d[3] )
	{ vec[0]=vec3d[0];vec[1]=vec3d[1];vec[2]=vec3d[2]; }

    inline CDS3DVec( const CDS3DPt& pt3d )
	{ vec[0]=pt3d.x(); vec[1]=pt3d.y(); vec[2]=pt3d.z(); }

    CDS3DVec( const CDS3DUnVec& uv3d );

	~CDS3DVec() {}

    inline void setvxyz( const int seq, const double uv ) { vec[seq]=uv; }
	inline void setvx( const double uv ) { vec[0]=uv; }
	inline void setvy( const double uv ) { vec[1]=uv; }
	inline void setvz( const double uv ) { vec[2]=uv; }

	inline double& vx() { return vec[0]; }
	inline double& vy() { return vec[1]; }
	inline double& vz() { return vec[2]; }

	void reverse() { vec[0]=-vec[0]; vec[1]=-vec[1]; vec[2]=-vec[2]; } //将当前向量换为相反的方向

	inline double vx() const { return vec[0]; }
	inline double vy() const { return vec[1]; }
	inline double vz() const { return vec[2]; }
	inline double vxyz( const int seq ) const { return vec[seq]; }

	//inline GLfloat fvx() const { return (GLfloat)vec[0]; }
	//inline GLfloat fvy() const { return (GLfloat)vec[1]; }
	//inline GLfloat fvz() const { return (GLfloat)vec[2]; }
  
   //CDS3DVec  operator overloading  = + - * / ^  ||
	CDS3DVec  operator=( const CDS3DVec& vec3d );
	CDS3DVec  operator+( const CDS3DVec& vec3d );
	CDS3DVec  operator+( const CDS3DUnVec& uv3d );
	CDS3DVec  operator+( const double& pc );
	CDS3DVec  operator-( const CDS3DVec& vec3d );
	CDS3DVec  operator-( const CDS3DUnVec& uv3d );
	CDS3DVec  operator-();
	CDS3DVec  operator^( const CDS3DVec& vec3d );//叉乘
	CDS3DVec  operator^( const CDS3DUnVec& uv3d );//与单位向量的叉乘
	CDS3DVec  operator+=( const CDS3DVec& vec3d );//自身加上一个三维向量
	CDS3DVec  operator+=( const CDS3DUnVec& uv3d );//自身加上一个单位向量
	CDS3DVec  operator+=( const double& pc );//自身三个坐标值同时加上一个常数
	CDS3DVec  operator-=( const CDS3DVec& vec3d );//自身减去一个三维向量
	CDS3DVec  operator-=( const CDS3DUnVec& uv3d );//自身减去一个单位向量
	CDS3DVec  operator^=( const CDS3DVec& vec3d );//自身与一个三维向量叉乘
	CDS3DVec  operator^=( const CDS3DUnVec& uv3d );//自身与一个单位向量叉乘
	double    operator*( const CDS3DVec& vec3d ); //与一个三维向量的点乘，内积
	double    operator*( const CDS3DUnVec& uv3d ); //与一个单位向量的点乘，内积
	//CDS3DVec  operator*( const TDSCVMat& rhmat ); //rhmat可以使3X3的旋转变换矩阵也可以是4X4的齐次矩阵
	CDS3DVec  operator*( const double& sc );
	CDS3DVec  operator/( const double& sc ); 
	//CDS3DVec  operator*=( const TDSCVMat& rhmat );
	CDS3DVec  operator*=( const double& sc );
	CDS3DVec  operator/=( const double& sc ); 
	CDS3DUnVec normalize() const; //将向量单位化得到相应的单位向量
	void opposite(); //将向量变为相反的方向
	double len_sq() const { return vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2]; } //返回向量长度的平方
	double len() const { return sqrt( vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2] ); } //返回向量的长度
private:
    double vec[3];
};

class dll_API CDS3DUnVec //三维单位向量
{
public:
	inline CDS3DUnVec() : is_zero( true ) //默认初始化为零向量
	{ vec[0]=0.0; vec[1]=0.0; vec[2]=0.0; }

	inline CDS3DUnVec( double xi, double yj, double zk=0.0 ) //给定三个实数并单位化
	{
		vec[0]=xi; vec[1]=yj; vec[2]=zk;
		double dlen=sqrt( xi*xi+yj*yj+zk*zk );
		if( !( is_zero=( dlen<DSZeroRange ) ) ) //判断是否为零向量，若为非零向量，则单位化
		{ vec[0]/=dlen; vec[1]/=dlen; vec[2]/=dlen; }  //若还没单位化，则单位化
	}

	inline CDS3DUnVec( const double vec3d[3], bool sym_zero ) //给定三个单位化的实数或零向量，则不需要进行单位化
	{ 
		vec[0]=vec3d[0]; vec[1]=vec3d[1]; vec[2]=vec3d[2]; 
		is_zero=sym_zero;
	}

	inline CDS3DUnVec( const double vec3d[3] ) //给定三个实数并单位化，需要判断是否为零向量
	{ 
		vec[0]=vec3d[0]; vec[1]=vec3d[1]; vec[2]=vec3d[2];
		double dlen=sqrt( vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2] );
		if( !( is_zero=( dlen<DSZeroRange ) ) ) //判断是否为零向量，若为非零向量，则单位化
		{ vec[0]/=dlen; vec[1]/=dlen; vec[2]/=dlen; }
	}

	inline CDS3DUnVec( const CDS3DVec& vec3d ) //将三维向量单位化
	{
		vec[0]=vec3d.vx(); vec[1]=vec3d.vy(); vec[2]=vec3d.vz();
		double dlen=sqrt( vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2] );
		if( !( is_zero=( dlen<DSZeroRange ) ) )//判断是否为零向量，若为非零向量，则单位化
		{ vec[0]/=dlen; vec[1]/=dlen; vec[2]/=dlen; }
	}

	~CDS3DUnVec(){}

	//修改单位向量的坐标值，采用以下两个函数
	inline void setuv( const double vec3d[3] ) 
	{
		vec[0]=vec3d[0]; vec[1]=vec3d[1]; vec[2]=vec3d[2];
		double dlen=sqrt( vec[0]*vec[0]+vec[1]*vec[1]+vec[2]*vec[2] );
		if( !( is_zero=( dlen<DSZeroRange ) ) ) //判断是否为零向量，若为非零向量，则单位化
		{ vec[0]/=dlen; vec[1]/=dlen; vec[2]/=dlen; }
	}
	inline void setuv( double xi, double yj, double zk=0.0 ) 
	{
		vec[0]=xi; vec[1]=yj; vec[2]=zk;
		double dlen=sqrt( xi*xi+yj*yj+zk*zk );
		if( !( is_zero=( dlen<DSZeroRange ) ) ) //判断是否为零向量，若为非零向量，则单位化
		{ vec[0]/=dlen; vec[1]/=dlen; vec[2]/=dlen; }  //若还没单位化，则单位化
	}
	//以下4个赋值函数不用(只是为了配合以前写的代码)
	//inline void setuxyz( const int seq, const double uv ) { vec[seq]=uv; }
	//inline void setux( const double uv ) { vec[0]=uv; }
	//inline void setuy( const double uv ) { vec[1]=uv; }
	//inline void setuz( const double uv ) { vec[2]=uv; }
    //以下3个引用函数不用(只是为了配合以前写的代码)
	inline double& ux() { return vec[0]; }
	inline double& uy() { return vec[1]; }
	inline double& uz() { return vec[2]; }
	//以上3个引用函数不用(不能注销，只是为了配合以前写的代码)

	inline double ux() const { return vec[0]; }
	inline double uy() const { return vec[1]; }
	inline double uz() const { return vec[2]; }
	inline double uxyz( const int seq ) const { return vec[seq]; }

	//inline GLfloat fux() const { return (GLfloat)vec[0]; }
	//inline GLfloat fuy() const { return (GLfloat)vec[1]; }
	//inline GLfloat fuz() const { return (GLfloat)vec[2]; }

	inline bool IsZero() const { return is_zero; } //判断该向量是否为0向量

	//CDS3DUnVec  operator overloading  = + - * / ^  ||
	
	CDS3DVec   operator + ( const CDS3DUnVec& uv3d );
	CDS3DVec   operator + ( const CDS3DVec& vec3d );
	CDS3DVec   operator - ( const CDS3DUnVec& uv3d );
	CDS3DVec   operator - ( const CDS3DVec& vec3d );
	CDS3DUnVec operator - ();
	CDS3DVec   operator ^ ( const CDS3DUnVec& uv3d );//与一个单位向量的叉乘
	CDS3DVec   operator ^ ( const CDS3DVec& vec3d );//与一个三维向量的叉乘
	double     operator * ( const CDS3DUnVec& uv3d ); //与一个单位向量的点乘，内积
	double     operator * ( const CDS3DVec& vec3d ); //与一个三维向量的点乘，内积
	//CDS3DUnVec operator * ( const TDSCVMat& rhmat ); //rhmat可以是3X3的旋转变换矩阵也可以是4X4的齐次矩阵
	//CDS3DUnVec operator *= ( const TDSCVMat& rhmat ); //rhmat可以是3X3的旋转变换矩阵也可以是4X4的齐次矩阵
	CDS3DVec   operator * ( const double& sc );
	CDS3DVec   operator / ( const double& sc ); 

	inline void opposite()
	{ vec[0]=-vec[0]; vec[1]=-vec[1]; vec[2]=-vec[2]; }//将单位向量变为相反的方向

protected:
	double vec[3];
	bool   is_zero;
};

class dll_API CDS3DPtNor : public CDS3DPt, public CDS3DUnVec //带单位法矢的三维点
{
public:
	inline CDS3DPtNor( double xa=0.0, double yb=0.0, double zc=0.0,
		               double xi=0.0, double yj=0.0, double zk=0.0 ) //由6个实数定义带单位法矢的三维点
		: is_selected( FALSE ), CDS3DPt( xa, yb, zc ), CDS3DUnVec( xi, yj, zk ) {}
	
	inline CDS3DPtNor( double pt3d[3], double nor3d[3], bool sym_zero ) //分别定义三维点和对应的单位法矢
		: is_selected( FALSE ), CDS3DPt( pt3d ), CDS3DUnVec( nor3d, sym_zero ) {}

	inline CDS3DPtNor( double pt3d[3], double nor3d[3] ) //分别定义三维点和对应的单位法矢
		: is_selected( FALSE ), CDS3DPt( pt3d ), CDS3DUnVec( nor3d ) {}
	
	inline CDS3DPtNor( double ptnor3d[6] ) //由6个实数定义带单位法矢的三维点
		: is_selected( FALSE ), CDS3DPt( ptnor3d ), CDS3DUnVec( ptnor3d+3 ) {}

	inline CDS3DPtNor( const CDS3DPt& pt3d ) //定义三维点，默认其初始法矢为零向量，待求
		: is_selected( FALSE ), CDS3DPt( pt3d ) {}

    inline CDS3DPtNor( const CDS3DPt& pt3d, const CDS3DUnVec& nor3d ) //通过三维点和单位向量定义带法矢的三维点
		: is_selected( FALSE ), CDS3DPt( pt3d ), CDS3DUnVec( nor3d ) {}

	~CDS3DPtNor() {}

	inline BOOL IsSelected() const { return is_selected; }
	inline void SetSelected( const BOOL sym_sel ) { is_selected=sym_sel; } 
	inline void SetSurfVar(const float surf_var) { surfvar=surf_var; } 
	inline float SurfVar() const { return surfvar; }

	//带法矢的点的坐标变换，平移时坐标点平移，法矢方向不变，旋转变换(齐次变换)时坐标变化，法矢方向也发生改变
	CDS3DPtNor operator + ( const CDS3DVec &vec3d ); //带法矢的坐标点平移，法矢不变
	CDS3DPtNor operator + ( const CDS3DUnVec &uv3d ); //带法矢的坐标点正向平移一个单位向量，坐标点平移，法矢不变
	CDS3DPtNor operator += ( const CDS3DVec &vec3d );//自身坐标点正向平移，法矢不变
	CDS3DPtNor operator += ( const CDS3DUnVec &uv3d ); //自身坐标点正向平移一个单位向量，单位法矢不变
	CDS3DPtNor operator - ( const CDS3DVec &vec3d ); //带法矢的坐标点平移，坐标点平移，法矢不变
	CDS3DPtNor operator - ( const CDS3DUnVec &uv3d ); //带法矢的坐标点负向平移一个单位向量，坐标点平移，法矢不变
	CDS3DPtNor operator -= ( const CDS3DVec &vec3d );//自身坐标点负向平移一个单位向量，法矢不变
	CDS3DPtNor operator -= ( const CDS3DUnVec &uv3d ); //带法矢的坐标点平移一个单位向量，坐标点平移，法矢不变


private:
	BOOL is_selected;
	float surfvar;  //曲面变化量
};



//带颜色信息的点
class dll_API CDS3DPtColor: public CDS3DPtNor
{
public:
	CDS3DPtColor();
    CDS3DPtColor( const CDS3DPtNor& t_PtN );
	~CDS3DPtColor();

	void SetColor( const float* arr_RGB );
	float clrr() const { return r; }
	float clrg() const { return g; }
	float clrb() const { return b; }
public:
	float r;
	float g;
	float b;
	float m_distErr;
};

// template  class DS_API_EXPORT std::allocator<CDS3DPtColor>;
// template  class DS_API_EXPORT std::vector<CDS3DPtColor>;
typedef vector<CDS3DPtColor> TDSVec3DPtColor;
typedef TDSVec3DPtColor::iterator TDSVec3DPtColorIt;
typedef TDSVec3DPtColor::const_iterator TDSVec3DPtColorConIt;


//线程间通信传递
/*class DS_API_EXPORT CDSMessage
{
public:
	vector<CDS3DPtNor> src1;
	//vector<CDS3DPtNor> src2;
};*/
class dll_API CDSGeoFea
{
public:
	double xAverage;
	double yAverage;
	double zAverage;

	double xMax, xMin;
	double yMax, yMin;
	double zMax, zMin;

public:
	CDSGeoFea();
	~CDSGeoFea();
};
class dll_API CDSChrom
{
public:
	CDSChrom(BOOL t_flg=FALSE, float t_distMin=0.0, float t_distMax=0.0,
		float t_distAve=0.0, float t_distAvePlus=0.0, float t_distAveMinus=0.0,
		float t_percErrMinus=0.0, float t_percErrZero=0.0);
	~CDSChrom();

	double RangeDist() const { return m_distMax-m_distMin; }
	void MInfDist();
	void InitDist( int t_numDist=0 );
	void SetDist( const TDSVec3DPtNor& vec_MovePSet, const TDSVec3DPtNor& vec_NearPSet );
	void SetDist( const TDSVec3DPt& vec_MovePSet, const TDSVec3DPtNor& vec_NearPSet );
	void SetDist2( const TDSVec3DPt& vec_MovePSet, const TDSVec3DPtNor& vec_NearPSet );
	void SetPtColor();
	void SetFlag( bool t_Flag ) { m_flg=t_Flag; }

	TDSVec3DPtColor& RefPtColor() { return m_ptColor; }
	const TDSVec3DPtColor& RefPtColor() const { return m_ptColor; }
	const TDSVecDou& RefErrRange() const { return m_ErrRange; }
	const TDSVec3DPt& RefClrRange() const { return m_ClrRange; }
	double MaxErr() const { return m_distMax; } //获取最大误差 
	double MinErr() const { return m_distMin; } //获取最小误差 
	double AveErr() const { return m_distAve; } //获取平均误差
	double VarErr() const { return m_distVar; } //获取标准偏差
	inline bool IsErr() const { return m_flg; }
	void Clear() { m_flg=false;m_ptColor.clear();m_dist.clear(); }
	void InitCenter();  //设置中心坐标
	void CalChromColor();

public:
	bool m_flg;
	double m_distMin;
	double m_distMax;
	double m_distAve;
	double m_distVar;
	double m_distAvePlus;
	double m_distAveMinus;
	double m_percErrMinus;
	double m_percErrZero;
	TDSVecDou m_ErrRange;
	TDSVec3DPt m_ClrRange;

	TDSVecDou m_dist;
	TDSVec3DPtColor m_ptColor;
	CDSGeoFea m_GeoFea;//获得数据的中心点、最大最小点
private:
	double m_LowRange;
	int m_SegNum;
};


class dll_API CMesh
{
public:
	inline CMesh(){ is_selected = FALSE; }
	inline CMesh( CDS3DPt a, CDS3DPt b, CDS3DPt c, CDS3DUnVec nor )
	{ m_pt1 = a; m_pt2 = b; m_pt3 = c; m_nor = nor; }

	inline BOOL IsSelected() const { return is_selected; }
	inline void SetSelected( const BOOL sym_sel ) { is_selected = sym_sel; } 

	~CMesh(){}

public:
	CDS3DUnVec getNor(){ return m_nor; }
	CDS3DPtNor getMeshPt1(){ return m_pt1; }

	void setNor(CDS3DUnVec a){ m_nor = a; }

public:
	CDS3DPt m_pt1;
	CDS3DPt m_pt2;
	CDS3DPt m_pt3;
	CDS3DUnVec m_nor;

private:
	BOOL is_selected;
};

#endif _DATASTRUCTURE_H_


