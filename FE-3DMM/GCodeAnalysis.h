/////���ཫUg���ɵ�G�����ļ���������λ������
#pragma once
#include <vector>
using namespace std;

class CGCodeAnalysis
{
public:
	CGCodeAnalysis(void);
	~CGCodeAnalysis(void);

	void ReadGCodeFile(CString strFileName);

public:
	vector<CString> m_vecStrGCode;

};

