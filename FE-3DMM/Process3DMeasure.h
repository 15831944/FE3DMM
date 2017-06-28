#pragma once
class CFE3DMMDlg;
class CParamData;

class CProcess3DMeasure
{
public:
	CProcess3DMeasure(void);
	~CProcess3DMeasure(void);

	void SetMainDlgPointer(CFE3DMMDlg* pDlg);		//����������ָ��
	void Init();
	void Release();
	void Home();									//����
	void TransferPara();							//����λ�����ݲ���	
	void SetParamData(CParamData* pData);			//�������ò�����ָ�� 

private:
	CFE3DMMDlg*				m_pMainDlg;				//���Ի���ָ��
	CParamData*				m_pParamData;			//���ò�����ָ��

	
};

