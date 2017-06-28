#pragma once


typedef struct st_Param3DMeasure
{

}Param3DMeasure;


typedef struct st_ParamLaserStrip
{

}ParamLaserStrip;


typedef struct st_ParamPrint
{

}ParamPrint;



/************************************************************************/
/* תӡ�������ݽṹ����
/************************************************************************/

//תӡ��ʽ�������ͱ���
enum enum_TransferType { INITIATIVE = 0, PASSITIVITY };

//תӡ����ߴ�
enum enum_TransferObjectSize{SIZE11 = 0,  SIZE22, SIZE33, SIZE44, SIZE55, SIZE66};

typedef struct st_ParamTransfer
{
	//תӡ����
	struct TRANSFER_OBJECT
	{
		enum_TransferObjectSize      iSize;                         //������С
		double                                       fXToCenter;             //mark����������x����
		double                                       fYToCenter;              //mark����������Y����
	};

	//�Ÿ�ֱ���Ƹ˵�λ��
	struct PUSH_ROD
	{
		double fRod11;
		double fRod12;
		double fRod13;
		double fRod21;
		double fRod22;
		double fRod23;
		double fRod31;
		double fRod32;
		double fRod33;
	};

	//��װλ��
	struct TRANSFER_POSITION
	{
		double fPosX;    //x����
		double fPosY;     //y����
		double fPosA;    //ƫת�Ƕȣ�ȡ��ʱ��Ϊ������
	};


	/*******************************************����****************************************/
	
	//ʵ���趨�Ĳ��������뱣��
	enum_TransferType           TransferType;           //תӡ��ʽ�������򱻶�
	enum_TransferObjectSize TransferSize;             //תӡ����ߴ�
	TRANSFER_OBJECT            iPlaceObject;            //תӡ����
	TRANSFER_POSITION        iPlacePos;                  //תӡλ��


	//�����ͱ�������Ҫ�̶�ѧϰ�Ĳ�������Ҫд���ļ�
	double fXPosPickCamera;               //תӡ����۲�PIλ��X
	double fZPosPickCamera;               //תӡ����۲�PIλ��Z

	double fXPosPickPicker;                 //ʰȡPIʱ��е��λ��X
	double fZPosPickPicker;                 //ʰȡPIʱ��е��λ��Z

	double fXPosPlaceCamera;                //��������۲��е��λ��X
	double fZPosPlaceCamera;                //��������۲��е��λ��Z

	double fXPosViewFourAxle;              //��������۲�����λ��X
	double fYPosViewFourAxle;              //��������۲�����λ��Y

	double fXPosPlacePicker;                  //��װPIʱ��е��X��ѧϰλ��
	double fZPosPlacePicker;                   //��װPIʱ��е��Z��ѧϰλ��

	//�궨�Ĳ�����д����һ��������APPname��
	double fDisPickerCamX;                      //��е�������������������Xƫ��
	double fDisPickerCamY;                      //��е�������������������Yƫ��

	double fPickerToSurfaceCenterX;    //��е�����Ķ�׼��������ʱ������X��λ��
	double fPickerToSurfaceCenterY;     //��е�����Ķ�׼��������ʱ������Y��λ��

	float fDownPixelWidth;                   //תӡ�������һ�����ص�ʵ��������
	float fDownPixelHeight;                  //תӡ�������һ�����ص�ʵ������߶�
	float fUpPixelWidth;                        //תӡ�������һ�����ص�ʵ��������
	float fUpPixelHeight;                      //תӡ�������һ�����ص�ʵ������߶�


/********************�������η������еĲ���*************************/
	
	double fZPosAfterPicker;                 //��е�ֽ�Ĥʰȡ�󣬻ص�һ���̶��߶�
	double fZPosAfterSurfaceLoc;        //���������λ�󣬻�е�ֻص�һ���̶��߶�
	
	//PUSH_ROD RodInit;                        //��е�ֳ�ʼʱ���Ƹ�λ��

	/*����ֵ�����豣��*/
	PUSH_ROD RodStransform;                 //�������ʱ���Ƹ˵�λ��
	double fXPosPlaceFourAxle;               //��װPIʱ����Xλ�ã����ĵ�����
	double fYPosPlaceFourAxle;               //��װPIʱ����Yλ��
	double fAPosPlaceFourAxle;              //��װPIʱA��ת���ɶ�λ��
	double fBPosPlaceFourAxle;               //��װPIʱB��ת���ɶ�λ��

	//double fPositivePressure;         //��ѹ��С
	//double fNegativePressure;      //��ѹ��С
/************************************************************************************************/


/***********************************�������η������в���***************************************/
	double fStaticV;                         //�����ѹ��С
	double fStaticF;                          //�����ѹƵ��

/***********************************************************************************************/


	//���������λ���
	double fXOffsetPick;                       //ʰȡPIʱX�Ჹ��ֵ
	double fYOffsetPick;
	double fAngleOffsetPick;

	//���������λ���
	double fXOffsetPlace;               //���������λ���X
	double fYOffsetPlace;               //���������λ���Y
	double fAngleOffsetPlace;       //���������λ���Ƕ�

	//�ӽ����ȡ����
	double fFullSpeed;                     //�����ٶ�
	double fZSpeed;                         //Z���ٶ�

}ParamTransfer;


typedef struct st_ParamCamera
{
	CString		strCamNameLaser;						//������������
	CString		strCamNameTransUp;					//תӡ���������
	CString		strCamNameTransDown;			//תӡ���������
	CString		strCamNamePrintLoc;					//��ӡ��λ�����
	CString		strCamNamePrintHoriz;				//��ӡƽ�������
	CString		strCamNamePrintAskant;			//��ӡб�������
}ParamCamera;