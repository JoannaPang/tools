
// ToolsV1Dlg.cpp : 实现文件
//



#include "stdafx.h"
#include "ToolsV1.h"
#include "ToolsV1Dlg.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"  
#include "opencv2/nonfree/nonfree.hpp"//SIFT相关  
#include "opencv2/legacy/legacy.hpp"//匹配器相关  
#include <opencv2/nonfree/features2d.hpp>
#include <vector>
#include "OpenCV2CXimage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;
using namespace std;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CToolsV1Dlg 对话框



CToolsV1Dlg::CToolsV1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TOOLSV1_DIALOG, pParent)
	, m_Edit(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CToolsV1Dlg::~CToolsV1Dlg() ///析构函数的函数体
{
	if (m_pImage1 != NULL)  ///将CxImage指针的内存释放
	{
		delete m_pImage1;
		m_pImage1 = NULL;
	}
	if (m_pImage2 != NULL)
	{
		delete m_pImage2;
		m_pImage2 = NULL;
	}
	if (m_pImage3 != NULL)
	{
		delete m_pImage3;
		m_pImage3 = NULL;
	}
}

void CToolsV1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Edit);
}

BEGIN_MESSAGE_MAP(CToolsV1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPENIMAGEA, &CToolsV1Dlg::OnBnClickedOpenimagea)
	ON_BN_CLICKED(IDC_OPENIMAGEB, &CToolsV1Dlg::OnBnClickedOpenimageb)
	ON_BN_CLICKED(IDC_HANDLE, &CToolsV1Dlg::OnBnClickedHandle)
	ON_BN_CLICKED(IDC_COMPUTE, &CToolsV1Dlg::OnBnClickedCompute)
END_MESSAGE_MAP()


// CToolsV1Dlg 消息处理程序

BOOL CToolsV1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	m_pWnd1 = NULL;  ///将指针置为NULL
	m_pWnd2 = NULL;
	m_pWnd3 = NULL;
	m_pImage1 = NULL;
	m_pImage2 = NULL;
	m_pImage3 = NULL;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CToolsV1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CToolsV1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CToolsV1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CToolsV1Dlg::OnBnClickedOpenimagea()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CString str;
	BOOL isOpen = TRUE;        //是否打开(是为打开，否则为保存)    
	CString defaultDir = _T("C:\\");   //默认打开的文件路径，C盘一般都指定有    
	CString fileName = L"test.bmp";         //默认打开的文件名    
	CString filter = L"位图(*.bmp)|*.bmp|jpg(*.jpg)|*.jpg||";   //文件过虑的类型    
	CFileDialog openFileDlg(isOpen, NULL, defaultDir + "\\" + fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	if (result != IDOK) return; //用户可能取消，可能直接关闭对话框

	else if (result == IDOK)
	{
		fileName = openFileDlg.GetPathName();//获取文件路径

		fileName.Replace(L"\\", L"/");
		switch (openFileDlg.m_ofn.nFilterIndex)
		{
		case 1:
			filter = L"bmp";
			break;
		case 2:
			filter = L"jpeg";
		}
		USES_CONVERSION;
		char *file = T2A(fileName);
		char *filterCH = T2A(filter);
		//write_image(Image, filterCH, 0, file);
	}*/



	//打开图片选择对话框  
	LPCTSTR szFilter = _T("BMP(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg|ALLSUPORTFILE(*.*)|*.*||");
	CFileDialog dlgBKFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	CString strBKFileName;
	//如果按下OK键  
	if (dlgBKFile.DoModal() == IDOK)
	{
		//读取视频文件  
		strBKFileName = dlgBKFile.GetPathName();
	}
	else
	{
		return;
	}

	//建立CxImage的类指针  
	CString strExt; //获取文件后缀名  
	int imageType;  //获取图像类型  

	strExt = FindExtension(strBKFileName);
	imageType = FindType(strExt);



	//判断指针是否为空  
	if (m_pImage1 != NULL)
	{
		delete m_pImage1;
		m_pImage1 = NULL;
	}

	//开辟内存  
	m_pImage1 = new CxImage();
	//打开图片  
	m_pImage1->Load(strBKFileName, imageType);

	if (!m_pImage1->IsValid())
	{
		AfxMessageBox(_T("建立图像指针失败!"));
		delete m_pImage1;
		m_pImage1 = NULL;
		return;
	}

	//绘制图像到相应的图像控件上  
	m_pWnd1 = this->GetDlgItem(IDC_IMAGEA); //<span style = "white-space:pre"></span>//这里一定要和picture Control控件的ID对应起来  
	DrawImgOnCtrl(m_pImage1, m_pWnd1);

}


void CToolsV1Dlg::OnBnClickedOpenimageb()
{
	// TODO: 在此添加控件通知处理程序代码
	/*
	UpdateData(TRUE);
	CxImage image;
	image.Load(_T("pic/pic.jpg"), CXIMAGE_SUPPORT_JPG);

	if (image.IsValid())
	{
		//image.GrayScale();  
		CDC *pDC = GetDC();
		image.Draw(pDC->GetSafeHdc(), CRect(0, 0, 200, 200));

		pDC->DeleteDC();
		image.Save(_T("pic/test.jpg"), CXIMAGE_SUPPORT_JPG);
	}
	UpdateData(FALSE);*/

	//打开图片选择对话框  
	LPCTSTR szFilter = _T("BMP(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg|ALLSUPORTFILE(*.*)|*.*||");
	CFileDialog dlgBKFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	CString strBKFileName;
	//如果按下OK键  
	if (dlgBKFile.DoModal() == IDOK)
	{
		//读取视频文件  
		strBKFileName = dlgBKFile.GetPathName();
	}
	else
	{
		return;
	}

	//建立CxImage的类指针  
	CString strExt; //获取文件后缀名  
	int imageType;  //获取图像类型  

	strExt = FindExtension(strBKFileName);
	imageType = FindType(strExt);



	//判断指针是否为空  
	if (m_pImage2 != NULL)
	{
		delete m_pImage2;
		m_pImage2 = NULL;
	}

	//开辟内存  
	m_pImage2 = new CxImage();
	//打开图片  
	m_pImage2->Load(strBKFileName, imageType);

	if (!m_pImage2->IsValid())
	{
		AfxMessageBox(_T("建立图像指针失败!"));
		delete m_pImage2;
		m_pImage2 = NULL;
		return;
	}

	//绘制图像到相应的图像控件上  
	m_pWnd2 = this->GetDlgItem(IDC_IMAGEB); //<span style = "white-space:pre"></span>//这里一定要和picture Control控件的ID对应起来  
	DrawImgOnCtrl(m_pImage2, m_pWnd2);

}
vector<uchar> buff1;
vector<uchar> buff2;
vector<uchar> buff3;
vector<KeyPoint> keyPoints1;
vector<KeyPoint> keyPoints2;
vector<DMatch> matches; //定义匹配结果变量 
vector<DMatch> goodMatches;
vector<Point2f> obj;
vector<Point2f> scene;

void CToolsV1Dlg::OnBnClickedHandle()
{
	// TODO: 在此添加控件通知处理程序代码
	/*OpenCV2CXimage o2i;
	IplImage *iplImage1;
	IplImage *iplImage2;
	bool okk1 = o2i.Cximage2IplImage(m_pImage1, &iplImage1); ///从Cximage类转换为IplImage类
	bool okk2 = o2i.Cximage2IplImage(m_pImage2, &iplImage2);*/
	if (m_pImage1 != NULL && m_pImage2 != NULL)
	{
		uint8_t* buf1 = NULL;
		int32_t len1 = 0;
		CxImage cximage1 = *m_pImage1;
		bool okk1 = cximage1.Encode(buf1, len1, CXIMAGE_FORMAT_JPG);

		uint8_t* buf2 = NULL;
		int32_t len2 = 0;
		CxImage cximage2 = *m_pImage2;
		bool okk2 = cximage2.Encode(buf2, len2, CXIMAGE_FORMAT_JPG);

		if (okk1 && okk2)
		{

			//1.SIFT特征点提取——detect()方法    
			///Mat srcImg1 = cvarrToMat(iplImage1);   ///从IplImage类转换为Mat类
			///Mat srcImg2 = cvarrToMat(iplImage2);

			buff1.resize(len1);
			memcpy(&buff1[0], buf1, len1);


			buff2.resize(len2);
			memcpy(&buff2[0], buf2, len2);

			Mat srcImg1;
			Mat srcImg2;
			srcImg1 = imdecode(buff1, 1);
			srcImg2 = imdecode(buff2, 1);

			delete[]buf1;
			delete[]buf2;

			buff1.clear();
			buff2.clear();

			Mat srcImg1_copy = srcImg1;
			Mat srcImg2_copy = srcImg2;
			Mat dstImg1, dstImg2;
			DenseFeatureDetector siftDetector;//SiftFeatureDetector是SIFT类的别名      

			keyPoints1.clear();
			keyPoints1.clear();
			MessageBox(_T("请稍后......"));
			//2.特征点描述符(特征向量)提取——compute()方法    
			SiftDescriptorExtractor descriptor;//SiftDescriptorExtractor是SIFT类的别名      
			Mat description1;
			Mat description2;

			int step = 10; // 10 pixels spacing between kp's  

			for (int i = step; i<srcImg1.rows - step; i += step)
			{
				for (int j = step; j<srcImg1.cols - step; j += step)
				{
					// x,y,radius  
					keyPoints1.push_back(KeyPoint(float(j), float(i), float(step)));
				}
			}

			for (int i = step; i<srcImg2.rows - step; i += step)
			{
				for (int j = step; j<srcImg2.cols - step; j += step)
				{
					// x,y,radius  
					keyPoints2.push_back(KeyPoint(float(j), float(i), float(step)));
				}
			}

			descriptor.compute(srcImg1, keyPoints1, description1);//注意原图和特征点要对应，不要写错    
			descriptor.compute(srcImg2, keyPoints2, description2);
			///imshow("description1", description1);
			///imshow("description2", description2);
			//3.使用暴力匹配器进行暴力匹配——BruteForceMatcher类的match()方法    
			BruteForceMatcher<L2<float>> matcher;//实例化暴力匹配器    

			matcher.match(description1, description2, matches);//实现描述符之间的匹配    
			MessageBox(_T("格式转换正确，正在计算......"));
			//4.对匹配结果进行筛选（依据DMatch结构体中的float类型变量distance进行筛选）    
			float minDistance = 100;
			float maxDistance = 0;
			for (int i = 0; i < matches.size(); i++)
			{
				if (matches[i].distance < minDistance)
					minDistance = matches[i].distance;
				if (matches[i].distance > maxDistance)
					maxDistance = matches[i].distance;
			}
			///cout << "minDistance: " << minDistance << endl;
			///cout << "maxDistance: " << maxDistance << endl;

			for (int i = 0; i < matches.size(); i++)
			{
				if (matches[i].distance < 3 * minDistance)
				{
					goodMatches.push_back(matches[i]);
				}
			}
			//5.绘制匹配结果——drawMatches()    
			Mat dstImg3;
			drawMatches(srcImg1, keyPoints1, srcImg2, keyPoints2, goodMatches, dstImg3);

			for (int i = 0; i < goodMatches.size(); i++)
			{
				obj.push_back(keyPoints1[goodMatches[i].queryIdx].pt);
				scene.push_back(keyPoints2[goodMatches[i].trainIdx].pt);
			}

			Mat H = findHomography(scene, obj, CV_RANSAC);
			Mat srcImg3;

			//Size size(500, 500);  
			//原图像变形    
			warpPerspective(srcImg2_copy, srcImg3, H, srcImg2_copy.size());

			///srcImg3是最终结果，将其写到磁盘上
			imwrite("pic/test3.jpg", srcImg3);
			keyPoints1.clear();
			keyPoints2.clear();
			matches.clear();
			goodMatches.clear();
			obj.clear();
			scene.clear();
			/*
			OpenCV2CXimage o2i2;
			IplImage *iplImage3 = &IplImage(srcImg3);//从Mat类转换为IplImage类
			bool okk3 = o2i2.IplImage2Cximage(iplImage3, m_pImage3); //从IplImage类转换为Cximage类
			if(okk3)
			{
			//绘制图像到相应的图像控件上
			m_pWnd3 = this->GetDlgItem(IDC_IMAGEC); //<span style = "white-space:pre"></span>//这里一定要和picture Control控件的ID对应起来
			DrawImgOnCtrl(m_pImage3, m_pWnd3);
			}
			else
			{
			MessageBox(_T("图像类型转换出现问题！"));
			}*/


			imencode(".jpg", srcImg3, buff3);
			CxImage img3(&buff3[0], buff3.size(), CXIMAGE_FORMAT_JPG);

			buff3.clear();
			//判断指针是否为空  
			if (m_pImage3 != NULL)
			{
				delete m_pImage3;
				m_pImage3 = NULL;
			}

			//开辟内存  
			m_pImage3 = new CxImage();
			m_pImage3 = &img3;

			if (!m_pImage3->IsValid())
			{
				AfxMessageBox(_T("建立图像指针失败!"));
				delete m_pImage3;
				m_pImage3 = NULL;
				return;
			}
			//MessageBox(_T("就差显示了！"));
			m_pWnd3 = this->GetDlgItem(IDC_IMAGEC);
			DrawImgOnCtrl(m_pImage3, m_pWnd3);
			//MessageBox(_T("成功显示了呢！"));
		}
		else
		{
			MessageBox(_T("格式转换不正确！！！"));
		}
	}
	else
	{
		MessageBox(_T("请先输入矫正前的两张图像！"));
	}
    //MessageBox(_T("矫正完事儿啦！开心吗？开心^0^,非常开心！哒哒哒"));
}
vector<uchar>buff33;

void CToolsV1Dlg::OnBnClickedCompute()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_pImage3 != NULL)
	{
		MessageBox(_T("计算着呢！"));
		/*uint8_t* buf3 = NULL;
		int32_t len3 = 0;
		CxImage cximage3 = *m_pImage3;
		bool okk3 = cximage3.Encode(buf3, len3, CXIMAGE_FORMAT_JPG);
		if (okk3)
		{
			MessageBox(_T("编码正确！"));
			buff33.resize(len3);
			memcpy(&buff33[0], buf3, len3);
			Mat srcImg3;
			srcImg3 = imdecode(buff33, 1);*/
		Mat srcImg3 = imread("pic/test3.jpg");

			Mat flag = Mat::zeros(srcImg3.rows, srcImg3.cols, CV_8UC1);
			Mat flag2 = Mat::zeros(srcImg3.rows, srcImg3.cols, CV_8UC1);

			int toothnum = 0;
			int rednum = 0;
			for (int i = 0; i < srcImg3.rows; i++)
			{
				for (int j = 0; j < srcImg3.cols; j++)
				{
					//at<类型>(i,j)进行操作，对于灰度图
					//img.at<uchar>(i, j) = i + j;
					//at<类型>(i,j)进行操作，对于灰度图
					//img.at<Vec3b>(i, j)[0] = 255;//对于蓝色通道进行操作
					//img.at<Vec3b>(i, j)[1] = 255;//对于绿色通道进行操作
					//img.at<Vec3b>(i, j)[2] = 255;//对于红色通道进行操作

					//cout <<(int)img.at<Vec3b>(i,j)[0]<< "  "<< (int)img.at<Vec3b>(i, j)[1] << "  "<<(int)img.at<Vec3b>(i, j)[2] << " |||  ";
					int Bh = srcImg3.at<Vec3b>(i, j)[0];
					int Gh = srcImg3.at<Vec3b>(i, j)[1];
					int Rh = srcImg3.at<Vec3b>(i, j)[2];
					if (Bh >= 100 && Gh >= 100 && Rh >= 80)
					{
						flag.at<uchar>(i, j) = 255;
						toothnum++;
					}
					if (Rh>150 && Rh<160 && Bh<150)
					{
						flag2.at<uchar>(i, j) = 255;
						rednum++;
					}
				}
			}
			//cout << "toothnum=" << toothnum << endl;
			//cout << "rednum=" << rednum << endl;
			double knum = 1.0*rednum / toothnum * 100;
			// 将各控件中的数据保存到相应的变量   
			UpdateData(TRUE);

			m_Edit = knum;

			// 根据各变量的值更新相应的控件。和的编辑框会显示m_editSum的值   
			UpdateData(FALSE);
		/*}
		else
		{
			MessageBox(_T("编码不正确！"));
		}*/
	}
	else
	{
		MessageBox(_T("根本找不到你想要的第三张图片呀！请（1）正确输入矫正前的两张图像;（2）对两张图像进行矫正！"));
	}
	
}


///* 获取文件的扩展名*/
CString CToolsV1Dlg::FindExtension(const CString &name)
{
	int len = name.GetLength();
	int i;
	for (i = len - 1; i >= 0; i--) {
		if (name[i] == '.') {
			return name.Mid(i + 1);
		}
	}
	return CString("");
}

///*获取图像扩展名的图像类型*/
int CToolsV1Dlg::FindType(const CString &ext)
{
	int type = 0;
	if (ext == "bmp")                   type = CXIMAGE_FORMAT_BMP;
#if CXIMAGE_SUPPORT_JPG  
	else if (ext == "jpg" || ext == "jpeg")   type = CXIMAGE_FORMAT_JPG;
#endif  
#if CXIMAGE_SUPPORT_JPG  
	else if (ext == "JPG" || ext == "JPEG")   type = CXIMAGE_FORMAT_JPG;
#endif  
#if CXIMAGE_SUPPORT_GIF  
	else if (ext == "gif")              type = CXIMAGE_FORMAT_GIF;
#endif  
#if CXIMAGE_SUPPORT_PNG  
	else if (ext == "png")              type = CXIMAGE_FORMAT_PNG;
#endif  
#if CXIMAGE_SUPPORT_MNG  
	else if (ext == "mng" || ext == "jng")    type = CXIMAGE_FORMAT_MNG;
#endif  
#if CXIMAGE_SUPPORT_ICO  
	else if (ext == "ico")              type = CXIMAGE_FORMAT_ICO;
#endif  
#if CXIMAGE_SUPPORT_TIF  
	else if (ext == "tiff" || ext == "tif")   type = CXIMAGE_FORMAT_TIF;
#endif  
#if CXIMAGE_SUPPORT_TGA  
	else if (ext == "tga")                type = CXIMAGE_FORMAT_TGA;
#endif  
#if CXIMAGE_SUPPORT_PCX  
	else if (ext == "pcx")                type = CXIMAGE_FORMAT_PCX;
#endif  
#if CXIMAGE_SUPPORT_WBMP  
	else if (ext == "wbmp")               type = CXIMAGE_FORMAT_WBMP;
#endif  
#if CXIMAGE_SUPPORT_WMF  
	else if (ext == "wmf" || ext == "emf")    type = CXIMAGE_FORMAT_WMF;
#endif  
#if CXIMAGE_SUPPORT_J2K  
	else if (ext == "j2k" || ext == "jp2")    type = CXIMAGE_FORMAT_J2K;
#endif  
#if CXIMAGE_SUPPORT_JBG  
	else if (ext == "jbg")                type = CXIMAGE_FORMAT_JBG;
#endif  
#if CXIMAGE_SUPPORT_JP2  
	else if (ext == "jp2" || ext == "j2k")    type = CXIMAGE_FORMAT_JP2;
#endif  
#if CXIMAGE_SUPPORT_JPC  
	else if (ext == "jpc" || ext == "j2c")    type = CXIMAGE_FORMAT_JPC;
#endif  
#if CXIMAGE_SUPPORT_PGX  
	else if (ext == "pgx")                type = CXIMAGE_FORMAT_PGX;
#endif  
#if CXIMAGE_SUPPORT_RAS  
	else if (ext == "ras")                type = CXIMAGE_FORMAT_RAS;
#endif  
#if CXIMAGE_SUPPORT_PNM  
	else if (ext == "pnm" || ext == "pgm" || ext == "ppm") type = CXIMAGE_FORMAT_PNM;
#endif  
	else type = CXIMAGE_FORMAT_UNKNOWN;

	return type;
}

///绘制图像函数  
void CToolsV1Dlg::DrawImgOnCtrl(CxImage* pImg, CWnd* wndDraw)
{
	int nImgWidth, nImgHeight;  //图像的长宽  
	CRect rectWndDraw;         //绘图窗口的矩形  
	CRect rectDispaly;         //图像显示区域  

							   //获取图像的长宽  
	nImgWidth = pImg->GetWidth();
	nImgHeight = pImg->GetHeight();

	//获取绘制窗口的长宽  
	wndDraw->GetClientRect(&rectWndDraw);

	//根据图像和绘制区域的比例绘制图像  
	CDC* pDC;
	pDC = wndDraw->GetDC();   //获取窗口句柄  

	pDC->FillSolidRect(rectWndDraw, RGB(0, 0, 0));

	//绘制图像到窗口区域  
	float xRadio, yRadio;
	float fRadio;
	xRadio = (float)rectWndDraw.Width() / (float)nImgWidth;
	yRadio = (float)rectWndDraw.Height() / (float)nImgHeight;
	if (xRadio >= yRadio)
		fRadio = yRadio;
	else
		fRadio = xRadio;

	//计算图像显示的位置  
	rectDispaly.left = int((rectWndDraw.Width() - nImgWidth * fRadio) / 2) + rectWndDraw.left;
	rectDispaly.top = int((rectWndDraw.Height() - nImgHeight * fRadio) / 2) + rectWndDraw.top;
	rectDispaly.right = int(rectDispaly.left + nImgWidth * fRadio);
	rectDispaly.bottom = int(rectDispaly.top + nImgHeight * fRadio);

	pImg->Draw(pDC->GetSafeHdc(), rectDispaly);
}


