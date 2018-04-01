
// ToolsV1Dlg.h : ͷ�ļ�
//

#pragma once


// CToolsV1Dlg �Ի���
class CToolsV1Dlg : public CDialogEx
{
// ����
public:
	CToolsV1Dlg(CWnd* pParent = NULL);	// ��׼���캯��
	~CToolsV1Dlg(); //������������Ҫ��cpp�ļ�����Ӻ�����

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLSV1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ������ʾռ�ȵ�ֻ���༭��
	double m_Edit;
	//��ԭͼ��A
	afx_msg void OnBnClickedOpenimagea();
	//��Ⱦɫ��ͼ��B
	afx_msg void OnBnClickedOpenimageb();
	//����ͼ��A��B�õ�ͼ��C������ʾ
	afx_msg void OnBnClickedHandle();

	CString FindExtension(const CString & name); ///��ȡ�ļ�����չ��

	int FindType(const CString & ext); ///����ͼ����չ����ͼ������

	void DrawImgOnCtrl(CxImage * pImg, CWnd * wndDraw); ///����ͼ����

	CWnd* m_pWnd1;  ///��ʾ����1
	CWnd* m_pWnd2;  ///��ʾ����2
	CWnd* m_pWnd3;  ///��ʾ����3

	CxImage* m_pImage1;  ///<span style="font-family: Arial, Helvetica, sans-serif;">����1</span><span style="font-family: Arial, Helvetica, sans-serif;">ͼ����ʾ���ָ��</span> 
	CxImage* m_pImage2;  ///����2��ʾ��ָ��
	CxImage* m_pImage3;  ///����3��ʾ��ָ��
	
	//����������ռ��
	afx_msg void OnBnClickedCompute();
};
