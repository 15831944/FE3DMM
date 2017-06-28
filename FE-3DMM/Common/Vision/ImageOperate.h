#pragma once
#include "HalconCpp.h"
using namespace HalconCpp;
#include "opencv2\opencv.hpp"
using namespace cv;

enum CameraType{LASER_VIEW=0, TRANS_DOWN, TRANS_UP, 
	PRINT_LOCAL, PRINT_HORIZONTAL, PRINT_ASKANT};   //�������

enum MatchMode{NCC=0, Shape};   //ƥ��ģʽ

enum CalibPtNumIndex{Three = 0, Four, Five, Six};   //�궨��������: Three:3*3, Four:4*4, Five:5*5, Six:6*6

typedef struct st_LocRes
{
	bool		 bSuccess;			
	double	 dXPos;
	double	 dYPos;
	double	 dAngle;
	st_LocRes()
	{
		bSuccess = false;
		dXPos = 0.0;
		dYPos = 0.0;
		dAngle = 0.0;
	}
}LocRes;


class CImageOperate
{
public:
	CImageOperate(void);
	~CImageOperate(void);

	void Init(const CameraType &camtype, const int &nImgWid, const int &nImgHei);	//��ʼ��							
	IplImage* HObject2IplImage(HObject &hobj);					//HObject->IplImage

	bool CreateModel(const HObject *phoImg, const CRect &rcRoi, const CString& strModelName = "NULL");	// ����ģ��
	bool LoadModel();																	//����ģ��
	
	void SetMatchMode(const MatchMode &mode);			//����ƥ��ģʽ
	void SetMatchRange(const CRect &rcRoi);						//����ƥ�䷶Χ
	void GenMatchRoiImg(const HObject *phoImg);				//���ɴ�ƥ��Roiͼ��
	bool Match();																			//ģ��ƥ��
	LocRes GetMatchRes();															//���ƥ����
	bool Calibrate(const CRect &rcRoi, const float &fBlackPtCenDis, const float &fBlackPtDiameter,
		const CalibPtNumIndex &enumPtIndex, float &fPixelWid, float &fPixelHei);				//����궨

private:
	double Degree2Rad(float degree){
			return degree*3.14159265/180.0;
	}
	void SetCameraType(const CameraType &camtype);		//�����������
	bool SaveModel(const CString& strModelName = "NULL");																	//�洢ģ��

private:
	int									m_nImgWidth;									//ͼ���
	int									m_nImgHeight;								//ͼ���
	IplImage							*m_pGrayImg;									//�ɼ�ͼ��

	CString							m_strModelPath;								//ģ��·��
	CameraType					m_enumCamType;							//�������
	MatchMode					m_enumMatchMode;						//ƥ��ģʽ
	HTuple							m_hvModelID;									//ģ��
	CRect								m_rcMatchRoi;									//��ƥ��Roi
	HObject							m_hoMatchRoiImg;							//��ƥ��Roiͼ��
	LocRes							m_stLocRes;										//��λ���
};

