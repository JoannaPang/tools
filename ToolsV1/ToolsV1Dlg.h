
// ToolsV1Dlg.h : 头文件
//

#pragma once


// CToolsV1Dlg 对话框
class CToolsV1Dlg : public CDialogEx
{
// 构造
public:
	CToolsV1Dlg(CWnd* pParent = NULL);	// 标准构造函数
	~CToolsV1Dlg(); //析构函数，需要在cpp文件中添加函数体

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TOOLSV1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 用于显示占比的只读编辑框
	double m_Edit;
	//打开原图像A
	afx_msg void OnBnClickedOpenimagea();
	//打开染色后图像B
	afx_msg void OnBnClickedOpenimageb();
	//处理图像A，B得到图像C，并显示
	afx_msg void OnBnClickedHandle();

	CString FindExtension(const CString & name); ///获取文件的扩展名

	int FindType(const CString & ext); ///绘制图像扩展名的图像类型

	void DrawImgOnCtrl(CxImage * pImg, CWnd * wndDraw); ///绘制图像函数

	CWnd* m_pWnd1;  ///显示窗口1
	CWnd* m_pWnd2;  ///显示窗口2
	CWnd* m_pWnd3;  ///显示窗口3

	CxImage* m_pImage1;  ///<span style="font-family: Arial, Helvetica, sans-serif;">窗口1</span><span style="font-family: Arial, Helvetica, sans-serif;">图像显示类库指针</span> 
	CxImage* m_pImage2;  ///窗口2显示类指针
	CxImage* m_pImage3;  ///窗口3显示类指针
	
	//计算牙菌斑占比
	afx_msg void OnBnClickedCompute();
};
