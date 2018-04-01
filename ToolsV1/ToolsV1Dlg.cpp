
// ToolsV1Dlg.cpp : ʵ���ļ�
//



#include "stdafx.h"
#include "ToolsV1.h"
#include "ToolsV1Dlg.h"
#include "afxdialogex.h"
#include "opencv2/opencv.hpp"  
#include "opencv2/nonfree/nonfree.hpp"//SIFT���  
#include "opencv2/legacy/legacy.hpp"//ƥ�������  
#include <opencv2/nonfree/features2d.hpp>
#include <vector>
#include "OpenCV2CXimage.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace cv;
using namespace std;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CToolsV1Dlg �Ի���



CToolsV1Dlg::CToolsV1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TOOLSV1_DIALOG, pParent)
	, m_Edit(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CToolsV1Dlg::~CToolsV1Dlg() ///���������ĺ�����
{
	if (m_pImage1 != NULL)  ///��CxImageָ����ڴ��ͷ�
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


// CToolsV1Dlg ��Ϣ�������

BOOL CToolsV1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	m_pWnd1 = NULL;  ///��ָ����ΪNULL
	m_pWnd2 = NULL;
	m_pWnd3 = NULL;
	m_pImage1 = NULL;
	m_pImage2 = NULL;
	m_pImage3 = NULL;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CToolsV1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CToolsV1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CToolsV1Dlg::OnBnClickedOpenimagea()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*CString str;
	BOOL isOpen = TRUE;        //�Ƿ��(��Ϊ�򿪣�����Ϊ����)    
	CString defaultDir = _T("C:\\");   //Ĭ�ϴ򿪵��ļ�·����C��һ�㶼ָ����    
	CString fileName = L"test.bmp";         //Ĭ�ϴ򿪵��ļ���    
	CString filter = L"λͼ(*.bmp)|*.bmp|jpg(*.jpg)|*.jpg||";   //�ļ����ǵ�����    
	CFileDialog openFileDlg(isOpen, NULL, defaultDir + "\\" + fileName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, NULL);
	INT_PTR result = openFileDlg.DoModal();
	if (result != IDOK) return; //�û�����ȡ��������ֱ�ӹرնԻ���

	else if (result == IDOK)
	{
		fileName = openFileDlg.GetPathName();//��ȡ�ļ�·��

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



	//��ͼƬѡ��Ի���  
	LPCTSTR szFilter = _T("BMP(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg|ALLSUPORTFILE(*.*)|*.*||");
	CFileDialog dlgBKFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	CString strBKFileName;
	//�������OK��  
	if (dlgBKFile.DoModal() == IDOK)
	{
		//��ȡ��Ƶ�ļ�  
		strBKFileName = dlgBKFile.GetPathName();
	}
	else
	{
		return;
	}

	//����CxImage����ָ��  
	CString strExt; //��ȡ�ļ���׺��  
	int imageType;  //��ȡͼ������  

	strExt = FindExtension(strBKFileName);
	imageType = FindType(strExt);



	//�ж�ָ���Ƿ�Ϊ��  
	if (m_pImage1 != NULL)
	{
		delete m_pImage1;
		m_pImage1 = NULL;
	}

	//�����ڴ�  
	m_pImage1 = new CxImage();
	//��ͼƬ  
	m_pImage1->Load(strBKFileName, imageType);

	if (!m_pImage1->IsValid())
	{
		AfxMessageBox(_T("����ͼ��ָ��ʧ��!"));
		delete m_pImage1;
		m_pImage1 = NULL;
		return;
	}

	//����ͼ����Ӧ��ͼ��ؼ���  
	m_pWnd1 = this->GetDlgItem(IDC_IMAGEA); //<span style = "white-space:pre"></span>//����һ��Ҫ��picture Control�ؼ���ID��Ӧ����  
	DrawImgOnCtrl(m_pImage1, m_pWnd1);

}


void CToolsV1Dlg::OnBnClickedOpenimageb()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

	//��ͼƬѡ��Ի���  
	LPCTSTR szFilter = _T("BMP(*.bmp)|*.bmp|JPEG(*.jpg)|*.jpg|ALLSUPORTFILE(*.*)|*.*||");
	CFileDialog dlgBKFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	CString strBKFileName;
	//�������OK��  
	if (dlgBKFile.DoModal() == IDOK)
	{
		//��ȡ��Ƶ�ļ�  
		strBKFileName = dlgBKFile.GetPathName();
	}
	else
	{
		return;
	}

	//����CxImage����ָ��  
	CString strExt; //��ȡ�ļ���׺��  
	int imageType;  //��ȡͼ������  

	strExt = FindExtension(strBKFileName);
	imageType = FindType(strExt);



	//�ж�ָ���Ƿ�Ϊ��  
	if (m_pImage2 != NULL)
	{
		delete m_pImage2;
		m_pImage2 = NULL;
	}

	//�����ڴ�  
	m_pImage2 = new CxImage();
	//��ͼƬ  
	m_pImage2->Load(strBKFileName, imageType);

	if (!m_pImage2->IsValid())
	{
		AfxMessageBox(_T("����ͼ��ָ��ʧ��!"));
		delete m_pImage2;
		m_pImage2 = NULL;
		return;
	}

	//����ͼ����Ӧ��ͼ��ؼ���  
	m_pWnd2 = this->GetDlgItem(IDC_IMAGEB); //<span style = "white-space:pre"></span>//����һ��Ҫ��picture Control�ؼ���ID��Ӧ����  
	DrawImgOnCtrl(m_pImage2, m_pWnd2);

}
vector<uchar> buff1;
vector<uchar> buff2;
vector<uchar> buff3;
vector<KeyPoint> keyPoints1;
vector<KeyPoint> keyPoints2;
vector<DMatch> matches; //����ƥ�������� 
vector<DMatch> goodMatches;
vector<Point2f> obj;
vector<Point2f> scene;

void CToolsV1Dlg::OnBnClickedHandle()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*OpenCV2CXimage o2i;
	IplImage *iplImage1;
	IplImage *iplImage2;
	bool okk1 = o2i.Cximage2IplImage(m_pImage1, &iplImage1); ///��Cximage��ת��ΪIplImage��
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

			//1.SIFT��������ȡ����detect()����    
			///Mat srcImg1 = cvarrToMat(iplImage1);   ///��IplImage��ת��ΪMat��
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
			DenseFeatureDetector siftDetector;//SiftFeatureDetector��SIFT��ı���      

			keyPoints1.clear();
			keyPoints1.clear();
			MessageBox(_T("���Ժ�......"));
			//2.������������(��������)��ȡ����compute()����    
			SiftDescriptorExtractor descriptor;//SiftDescriptorExtractor��SIFT��ı���      
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

			descriptor.compute(srcImg1, keyPoints1, description1);//ע��ԭͼ��������Ҫ��Ӧ����Ҫд��    
			descriptor.compute(srcImg2, keyPoints2, description2);
			///imshow("description1", description1);
			///imshow("description2", description2);
			//3.ʹ�ñ���ƥ�������б���ƥ�䡪��BruteForceMatcher���match()����    
			BruteForceMatcher<L2<float>> matcher;//ʵ��������ƥ����    

			matcher.match(description1, description2, matches);//ʵ��������֮���ƥ��    
			MessageBox(_T("��ʽת����ȷ�����ڼ���......"));
			//4.��ƥ��������ɸѡ������DMatch�ṹ���е�float���ͱ���distance����ɸѡ��    
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
			//5.����ƥ��������drawMatches()    
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
			//ԭͼ�����    
			warpPerspective(srcImg2_copy, srcImg3, H, srcImg2_copy.size());

			///srcImg3�����ս��������д��������
			imwrite("pic/test3.jpg", srcImg3);
			keyPoints1.clear();
			keyPoints2.clear();
			matches.clear();
			goodMatches.clear();
			obj.clear();
			scene.clear();
			/*
			OpenCV2CXimage o2i2;
			IplImage *iplImage3 = &IplImage(srcImg3);//��Mat��ת��ΪIplImage��
			bool okk3 = o2i2.IplImage2Cximage(iplImage3, m_pImage3); //��IplImage��ת��ΪCximage��
			if(okk3)
			{
			//����ͼ����Ӧ��ͼ��ؼ���
			m_pWnd3 = this->GetDlgItem(IDC_IMAGEC); //<span style = "white-space:pre"></span>//����һ��Ҫ��picture Control�ؼ���ID��Ӧ����
			DrawImgOnCtrl(m_pImage3, m_pWnd3);
			}
			else
			{
			MessageBox(_T("ͼ������ת���������⣡"));
			}*/


			imencode(".jpg", srcImg3, buff3);
			CxImage img3(&buff3[0], buff3.size(), CXIMAGE_FORMAT_JPG);

			buff3.clear();
			//�ж�ָ���Ƿ�Ϊ��  
			if (m_pImage3 != NULL)
			{
				delete m_pImage3;
				m_pImage3 = NULL;
			}

			//�����ڴ�  
			m_pImage3 = new CxImage();
			m_pImage3 = &img3;

			if (!m_pImage3->IsValid())
			{
				AfxMessageBox(_T("����ͼ��ָ��ʧ��!"));
				delete m_pImage3;
				m_pImage3 = NULL;
				return;
			}
			//MessageBox(_T("�Ͳ���ʾ�ˣ�"));
			m_pWnd3 = this->GetDlgItem(IDC_IMAGEC);
			DrawImgOnCtrl(m_pImage3, m_pWnd3);
			//MessageBox(_T("�ɹ���ʾ���أ�"));
		}
		else
		{
			MessageBox(_T("��ʽת������ȷ������"));
		}
	}
	else
	{
		MessageBox(_T("�����������ǰ������ͼ��"));
	}
    //MessageBox(_T("�������¶����������𣿿���^0^,�ǳ����ģ�������"));
}
vector<uchar>buff33;

void CToolsV1Dlg::OnBnClickedCompute()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_pImage3 != NULL)
	{
		MessageBox(_T("�������أ�"));
		/*uint8_t* buf3 = NULL;
		int32_t len3 = 0;
		CxImage cximage3 = *m_pImage3;
		bool okk3 = cximage3.Encode(buf3, len3, CXIMAGE_FORMAT_JPG);
		if (okk3)
		{
			MessageBox(_T("������ȷ��"));
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
					//at<����>(i,j)���в��������ڻҶ�ͼ
					//img.at<uchar>(i, j) = i + j;
					//at<����>(i,j)���в��������ڻҶ�ͼ
					//img.at<Vec3b>(i, j)[0] = 255;//������ɫͨ�����в���
					//img.at<Vec3b>(i, j)[1] = 255;//������ɫͨ�����в���
					//img.at<Vec3b>(i, j)[2] = 255;//���ں�ɫͨ�����в���

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
			// �����ؼ��е����ݱ��浽��Ӧ�ı���   
			UpdateData(TRUE);

			m_Edit = knum;

			// ���ݸ�������ֵ������Ӧ�Ŀؼ����͵ı༭�����ʾm_editSum��ֵ   
			UpdateData(FALSE);
		/*}
		else
		{
			MessageBox(_T("���벻��ȷ��"));
		}*/
	}
	else
	{
		MessageBox(_T("�����Ҳ�������Ҫ�ĵ�����ͼƬѽ���루1����ȷ�������ǰ������ͼ��;��2��������ͼ����н�����"));
	}
	
}


///* ��ȡ�ļ�����չ��*/
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

///*��ȡͼ����չ����ͼ������*/
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

///����ͼ����  
void CToolsV1Dlg::DrawImgOnCtrl(CxImage* pImg, CWnd* wndDraw)
{
	int nImgWidth, nImgHeight;  //ͼ��ĳ���  
	CRect rectWndDraw;         //��ͼ���ڵľ���  
	CRect rectDispaly;         //ͼ����ʾ����  

							   //��ȡͼ��ĳ���  
	nImgWidth = pImg->GetWidth();
	nImgHeight = pImg->GetHeight();

	//��ȡ���ƴ��ڵĳ���  
	wndDraw->GetClientRect(&rectWndDraw);

	//����ͼ��ͻ�������ı�������ͼ��  
	CDC* pDC;
	pDC = wndDraw->GetDC();   //��ȡ���ھ��  

	pDC->FillSolidRect(rectWndDraw, RGB(0, 0, 0));

	//����ͼ�񵽴�������  
	float xRadio, yRadio;
	float fRadio;
	xRadio = (float)rectWndDraw.Width() / (float)nImgWidth;
	yRadio = (float)rectWndDraw.Height() / (float)nImgHeight;
	if (xRadio >= yRadio)
		fRadio = yRadio;
	else
		fRadio = xRadio;

	//����ͼ����ʾ��λ��  
	rectDispaly.left = int((rectWndDraw.Width() - nImgWidth * fRadio) / 2) + rectWndDraw.left;
	rectDispaly.top = int((rectWndDraw.Height() - nImgHeight * fRadio) / 2) + rectWndDraw.top;
	rectDispaly.right = int(rectDispaly.left + nImgWidth * fRadio);
	rectDispaly.bottom = int(rectDispaly.top + nImgHeight * fRadio);

	pImg->Draw(pDC->GetSafeHdc(), rectDispaly);
}


