#include "stdafx.h"
#include "JetAglientFunction.h"

#if _DEBUGE_VISA
#pragma comment(lib,"visa32.lib")
#endif

CJetAglientFunction::CJetAglientFunction()
{
	m_bIsConn = false;
}


CJetAglientFunction::~CJetAglientFunction()
{
	//�Զ��ر�����
	Disconnect();
}

bool CJetAglientFunction::Connect()
{
	ViString intFName[512];
	ViUInt16 intFType;

	//�ȹر��Ѿ����ӵĺ����´�����
	if (m_bIsConn == true)
	{
		Disconnect();
	}

	//�򿪲���ʼ������Դ������
#if _DEBUGE_VISA
	viOpenDefaultRM(&m_drms);
#endif
	//FullName is USB0::0x0957::0x2C07::MY52814499::0::INSTR,
	//To make this more portable ,use UsbDevice1 Instead
	//�򿪲���ʼ��һָ������Դ�Ự
#if _DEBUGE_VISA
	viOpen(m_drms, 
		   "USB0::0x0957::0x2C07::MY52814499::0::INSTR",
		   VI_NULL, 
		   VI_NULL, 
		   &Function_Generator_33500B);   

	//ȷ��Ĭ�ϵĺ��������������Ƿ���\n���������ﶨ���SCPI�����Ǳ�����\n��β��  
	ViBoolean termDefaultFunction_Generator_33500B = VI_FALSE;
	if ((VI_SUCCESS == viGetAttribute(Function_Generator_33500B, 
									  VI_ATTR_RSRC_CLASS, 
									  intFName))
		&& (0 == strcmp("SOCKET", (ViString)intFName)))
	{
		termDefaultFunction_Generator_33500B = VI_TRUE;
	}
	else if ((VI_SUCCESS == viGetAttribute(Function_Generator_33500B, 
										   VI_ATTR_INTF_TYPE, 
										   &intFType)) 
		&& (intFType == VI_INTF_USB))
	{
		termDefaultFunction_Generator_33500B = VI_TRUE;
	}

	if (VI_TRUE == termDefaultFunction_Generator_33500B)
	{ 
		viSetAttribute(Function_Generator_33500B, 
					   VI_ATTR_TERMCHAR_EN, 
					   termDefaultFunction_Generator_33500B);

		//Ĭ��ΪDC
		//SetDCFunction();
		//SetOffset(0);
		//SetOutput(false);

		 m_bIsConn = true;
	}
	else
	{
		 m_bIsConn = false;
	}
#endif

	return m_bIsConn;
}

bool CJetAglientFunction::Disconnect()
{
	if (m_bIsConn == true)
	{
		//�رյ�ָ����USB�ӿڿ��Ƶĺ���������������
#if _DEBUGE_VISA
		viClose(Function_Generator_33500B);

		//�ر��ܵ���Դ������
		if (VI_SUCCESS == viClose(m_drms))
		{
			m_bIsConn = false;
			return true;
		}
		else
		{
			m_bIsConn = true;
			return false;
		}
#endif
	}

	return true;
}

//���ò���Ϊֱ�����
//offsetΪĬ�ϳ�ʼ��ѹ
void CJetAglientFunction::SetDCMode(double offset/*=0*/)
{
	//DC����
#if _DEBUGE_VISA
	viPrintf(Function_Generator_33500B, ":SOURce:FUNCtion %s\n", "DC");

	//���õ�ѹ��λΪV
	viPrintf(Function_Generator_33500B, ":SOURce:VOLTage:UNIT VPP\n");

	//��ѹ������λ-5~+5V
	viPrintf(Function_Generator_33500B, ":SOURce:VOLTage:LIMit:HIGH %@3lf\n", 5.0); //��������ѹ 
	viPrintf(Function_Generator_33500B, ":SOURce:VOLTage:LIMit:LOW %@3lf\n", -5.0); //��С�����ѹ 
	viPrintf(Function_Generator_33500B, ":SOURce:VOLTage:LIMit:STATe %@1d\n", 1);
#endif
	SetOffset(offset);
}

//���ò���Ϊ����
void CJetAglientFunction::SetACMode()
{
	//��������
#if _DEBUGE_VISA
	viPrintf(Function_Generator_33500B, ":SOURce:FUNCtion %s\n", "SQUare");

	//���õ�ѹ��λΪV
	viPrintf(Function_Generator_33500B, ":SOURce:VOLTage:UNIT VPP\n");

	//��ѹ������λ-5~+5V
	viPrintf(Function_Generator_33500B, ":SOURce:VOLTage:LIMit:HIGH %@3lf\n", 5.0); //��������ѹ 
	viPrintf(Function_Generator_33500B, ":SOURce:VOLTage:LIMit:LOW %@3lf\n", -5.0); //��С�����ѹ 
	viPrintf(Function_Generator_33500B, ":SOURce:VOLTage:LIMit:STATe %@1d\n", 1); 

	//���������������ſ�ģʽ
	viPrintf(Function_Generator_33500B, ":SOURce:BURSt:MODE GATed\n"); 
	viPrintf(Function_Generator_33500B, ":SOURce:BURSt:STATe %@1d\n", 1);

	//�����ش���
	viPrintf(Function_Generator_33500B, ":TRIGger:SLOPe POSitive\n");
#endif
}

//��ѹƫִΪoffset mV����ΧΪ-5000~5000
void CJetAglientFunction::SetOffset( double offset )
{
#if _DEBUGE_VISA
	viPrintf(Function_Generator_33500B, ":SOURce:VOLTage:OFFSet %@3lf mV\n", offset);
#endif
}

//Ƶ��(kHz) 
void CJetAglientFunction::SetFrequency( double freq )
{
#if _DEBUGE_VISA
	viPrintf(Function_Generator_33500B, ":SOURce:FREQuency %@3lf HZ\n", freq);       
#endif
}

//��ֵ,��λΪV
void CJetAglientFunction::SetAmplitude( double amp )
{
#if _DEBUGE_VISA
	viPrintf(Function_Generator_33500B, ":SOURce:VOLTage %@3lf mV\n", amp);
#endif
}

//��������ռ�ձ�,%����
void CJetAglientFunction::SetRatio( double dCycle )
{
#if _DEBUGE_VISA
	viPrintf(Function_Generator_33500B, ":SOURce:FUNCtion:SQUare:DCYCle %@3lf\n", dCycle);
#endif
}

//�Ƿ������ѹ�ź�
void CJetAglientFunction::SetOutput( bool isOutput )
{
#if _DEBUGE_VISA
	viPrintf(Function_Generator_33500B, ":OutPut %@1d\n", isOutput==true ? 1 : 0);
#endif
}

bool CJetAglientFunction::IsDeviceConnect() const
{
	return m_bIsConn;
}