#pragma once
/*
* ��˵����OpenCVͼ����CXimageͼ��ת
* ����OpenCV��ͼ����CXimageͼ���ʽ��ת���з�װ�� OpenCV��ͼ��λ�������Ǵ����8����������֧��BMP��JPGͼ���ʽ��CXimage��ͼ��λ��������1��2��4��8��16��24��֧��BMP��JPG��TIF��PNG��GIFͼ���ʽ��
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
	����˵��: ��ȡ�ڵ��ǵķ�ʽ
	����˵��:  cxImage ͼ������
	����ֵ: �ڵ���
	*/
	static int OpenCV2CXimage::GetBlackColor(CxImage cxImage);

	/*
	����˵��: ��ȡ�׵��ǵķ�ʽ
	����˵��:  cxImage ͼ������
	����ֵ: �ڵ���
	*/
	static int OpenCV2CXimage::GetWhiteColor(CxImage cxImage);

	/*
	*����˵����ת��Cximage��IplImage(ע������IplImage�ṹ��֧��ͼ��������8λ��ʽ������ǿ��ת����8λ������)
	*����˵����src����ʾԭʼCximageͼ��dst��[out] ��ʾOpencvͼ��IplImage�ṹ
	*����ֵ��bool���͡�true����ʾ�ɹ���flase,��ʾʧ�ܡ�
	*/
	bool Cximage2IplImage(CxImage *src, IplImage **dst);

	/*
	*����˵����ת��IplImage��Cximage
	*����˵����src����ʾOpencvͼ��IplImage�ṹ��dst��[out] ��ʾ���Cximageͼ��;nBpp,��ʾ���Cximageͼ��λ��ռ����λ[һ������ռ����λ](1,8,24);
	*����ֵ��bool���͡�true����ʾ�ɹ���flase,��ʾʧ�ܡ�
	*/
	bool IplImage2Cximage(IplImage *src, CxImage *dst, long nBpp = 8);

	/*
	*����˵����ͼ���ʽת��
	*����˵����src����ʾ����Cximageͼ��dst��[out] ��ʾ���Cximageͼ��imagetype,��ʾͼ������
	*����ֵ��bool���͡�true����ʾ�ɹ���flase,��ʾʧ�ܡ�
	*/
	bool CxImageFormatConvert(CxImage *src, CxImage *dst, long imagetype = CXIMAGE_FORMAT_BMP);

protected:
	RGBQUAD *m_pPal;//��ɫ��
	int m_nPalatteCount;
};