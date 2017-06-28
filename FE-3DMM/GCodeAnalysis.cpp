#include "StdAfx.h"
#include "GCodeAnalysis.h"


CGCodeAnalysis::CGCodeAnalysis(void)
{
}


CGCodeAnalysis::~CGCodeAnalysis(void)
{
}


void CGCodeAnalysis::ReadGCodeFile(CString strFileName)
{
	////ע�⣺��������P����, �ӵ�һ��XYZ��ʼ����������ΪX(P1+..),  Y(P2+..), Z(P3+..)

	CStdioFile file;
	if (!file.Open(strFileName, CFile::modeRead))
	{
		AfxMessageBox("��G�����ļ�ʧ��!");
		return;
	}

	m_vecStrGCode.clear();      

	CString strLine;
	CString strCommandTemp;
	while (file.ReadString(strLine))
	{
		if (strLine.Left(1) != 'N') continue;
		strLine.Delete(0, strLine.Find(' ')+1);  //�Ƚ�N��ͷ��һ���ַ���ɾ֮

		while(strLine.GetLength() != 0)
		{
			if (strLine.Find(' ') == 0)
			{
				strLine.Delete(0, 1);  //����һ���ַ�Ϊ' 'ʱ��ɾ֮
			}
			else if (strLine.Find(' ') > 0)
			{		
				strCommandTemp = strLine.Left(strLine.Find(' '));  //��ȡһ����ʱ����
				m_vecStrGCode.push_back(strCommandTemp);  //ѹջ
				strLine.Delete(0, strLine.Find(' ') + 1);
			}
			else
			{
				m_vecStrGCode.push_back(strLine);
				strLine.Delete(0, strLine.GetLength());
			}
		}	
	}
}
