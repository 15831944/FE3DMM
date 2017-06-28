#pragma once
#include "TransferMatrix.h"
#include "ParamData.h"

const double MIN =  0.00001;
const int DIS = 25;   //�Ƹ�֮��ľ��루mm��

typedef struct st_Point
{
public:
	double x;
	double y;
	double z;

	st_Point(double a = 0, double b = 0, double c = 0)
		:x(a), y(b), z(c){}
}SurfacePoint;

class CTransferRotateCal
{
public:
	CTransferRotateCal();
	~CTransferRotateCal(void);

	void Rotate();



	/*
	** @input: ���������Թ�������Ϊ����ϵ������1Ϊx���꣬����2ΪY���꣬����3Ϊ��ת�ĽǶȣ��Ƕ��ƣ�
	** @output: void
	** @function: �趨��װλ������
	*/
	void SetOriginPos(const double&, const double&, const double &);


	/*
	** @input: ����
	** @function: ���Թ�������Ϊԭ�������ϵ��ת�����������̵�����ϵ
	*/
	void TransCoordinate(SurfacePoint & p);


	/*
	** @input: void
	** @output: const std::vector<double>&�Ÿ��Ƹ˵�λ��
	** @function: ���ؾŸ��Ƹ˵�λ��
	*/
	inline const std::vector<double>& CTransferRotateCal::GetRodDisplacement() const
	{ 
		return m_RodDisplacement; 
	}

	inline double GetRotateAngleA() const {return m_fRotateAngleA;}

	inline double GetRotateAngleB() const {return m_fRotateAngleB;}


private:
	/*
	** @����ָ�������ķ�����
	*/
	bool CalNormalVector();    


	bool MatrixOne();                    //�����һ�ֽⷨ����ת����
	bool MatrixThree();                 //��������ֽⷨ����ת����
	bool CalRotateVector();
	bool CalNinePoint();               //����Ÿ�����תǰ������
	bool CalNinePointRotate();   //����Ÿ�����ת�������
	bool CalRodDisplacement();                  //�����Ƹ�λ��



	//private members
private:
	//��װ��ĳ�ʼλ��
	SurfacePoint m_PointCenterOrigin;
	double m_fPosAngleOrigin;

	//��װ����ת���λ��
	SurfacePoint m_PointCenterPlace;

	double m_fRotateAngleA;         //������һ����ת�ĽǶ�
	double m_fRotateAngleB;          //�����ڶ�����ת�ĽǶ�

	std::vector<double> m_Normal;                     //����ʸ��
	std::vector<SurfacePoint> m_NinePoint;                    //�Ÿ�����תǰ������
	std::vector<SurfacePoint> m_NinePointRotate;        //�Ÿ�����ת�������
	std::vector<double> m_RodDisplacement;  //�Ƹ�λ��
	CMatrix m_Matrix;    //��ת����
	
	bool m_bInitFinish;   //�Ƿ��趨��ʼֵ��־��
	CParamData* m_pParamData;
private:
	//�������캯��
	CTransferRotateCal(const CTransferRotateCal&);    //��ʵ�֣���ֹ����
};

