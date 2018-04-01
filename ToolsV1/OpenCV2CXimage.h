#pragma once
/*
* 类说明：OpenCV图像与CXimage图像互转
* 用于OpenCV的图像与CXimage图像格式互转进行封装。 OpenCV的图像位数必须是大等于8的整数倍，支持BMP，JPG图像格式；CXimage的图像位数可以是1、2、4、8、16、24，支持BMP，JPG，TIF，PNG，GIF图像格式。
*/

#include "ximage.h"
#include "cv.h"
#include "cxcore.h"
#include "highgui.h"
/*
#ifdef _DEBUG
#pragma comment(lib, "cxcore200d.lib")
#pragma comment(lib, "cv200d.lib")
#pragma comment(lib, "highgui200d.lib")
#else
#pragma comment(lib, "cxcore200.lib")
#pragma comment(lib, "cv200.lib")
#pragma comment(lib, "highgui200.lib")
#endif
*/
class OpenCV2CXimage
{
public:
	OpenCV2CXimage(void);
	~OpenCV2CXimage(void);

	/*
	功能说明: 获取黑点标记的方式
	参数说明:  cxImage 图像处理类
	返回值: 黑点标记
	*/
	static int OpenCV2CXimage::GetBlackColor(CxImage cxImage);

	/*
	功能说明: 获取白点标记的方式
	参数说明:  cxImage 图像处理类
	返回值: 黑点标记
	*/
	static int OpenCV2CXimage::GetWhiteColor(CxImage cxImage);

	/*
	*功能说明：转换Cximage到IplImage(注：由于IplImage结构不支持图像像数非8位格式，所以强制转换成8位整数倍)
	*参数说明：src，表示原始Cximage图像；dst，[out] 表示Opencv图像IplImage结构
	*返回值：bool类型。true，表示成功；flase,表示失败。
	*/
	bool Cximage2IplImage(CxImage *src, IplImage **dst);

	/*
	*功能说明：转换IplImage到Cximage
	*参数说明：src，表示Opencv图像IplImage结构；dst，[out] 表示输出Cximage图像;nBpp,表示输出Cximage图像位数占多少位[一个像数占多少位](1,8,24);
	*返回值：bool类型。true，表示成功；flase,表示失败。
	*/
	bool IplImage2Cximage(IplImage *src, CxImage *dst, long nBpp = 8);

	/*
	*功能说明：图象格式转换
	*参数说明：src，表示输入Cximage图像；dst，[out] 表示输出Cximage图像；imagetype,表示图象类型
	*返回值：bool类型。true，表示成功；flase,表示失败。
	*/
	bool CxImageFormatConvert(CxImage *src, CxImage *dst, long imagetype = CXIMAGE_FORMAT_BMP);

protected:
	RGBQUAD *m_pPal;//调色版
	int m_nPalatteCount;
};