#pragma once

#include "JetAirPressurePort.h"

//ģ������������ MA_0_20: 0-20mA, MA_4_20: 4-20mA, V_0_5: 0-5V, V_0_10: 0-10V
enum AnalogType{ EMPTY_TYPE = -1, MA_0_20,  MA_4_20, V_0_5, V_0_10};

class CJetAirPressureSet
{
public:
	CJetAirPressureSet(void);
	virtual ~CJetAirPressureSet(void);

public:
	BOOL Init(unsigned long xPort,//���ں�
		      unsigned long xBabd = 9600,//������
			  unsigned char xDataSize = 8, //����λ
		      unsigned char xParity = 0, //У��λ
		      unsigned char xStopBit = 0);//ֹͣλ

	BOOL UnInit();
	BOOL SetAnalogInputType(int type);				//����ģ������������ 0: 0-20mA, 1: 4-20mA, 2: 0-5V, 3: 0-10V
	BOOL WriteData(int channel, float voltage);  //��ģ������channel���ͨ��дֵ, channel=0:3
	BOOL ReadData(int channel, float *pVal);		//��ģ������channel����ͨ����ȡֵ, channel=0:3
		
private:
	BOOL CheckConnect();
	BOOL WriteData(unsigned char regLoc_H, unsigned char regLoc_L, float val, AnalogType analogtype);      //�򱣴�Ĵ���дֵ
	BOOL ReadData(unsigned char regLoc_H, unsigned char regLoc_L, float *pVal, AnalogType analogtype);	  //��ȡ����Ĵ�����ֵ
	unsigned short CalcCrcFast(unsigned char* puchMsg, unsigned short usDataLen);

private:
	CJetAirPressurePort m_comm;
	AnalogType m_enumAnalogType;     //ģ������������
};

