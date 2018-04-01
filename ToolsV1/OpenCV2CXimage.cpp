#include "StdAfx.h"
#include "OpenCV2CXimage.h"
#include <map>
using namespace std;

OpenCV2CXimage::OpenCV2CXimage(void)
{
	m_pPal = NULL;
	m_nPalatteCount = 0;
}

OpenCV2CXimage::~OpenCV2CXimage(void)
{
	if (m_pPal != NULL)
	{
		delete[]m_pPal;
		m_pPal = NULL;
	}
}

//������: GetBlackColor
//����:  ��ȡ�ڵ��ǵķ�ʽ
//����:  cxImage ͼ������
//����ֵ: �ڵ���
int OpenCV2CXimage::GetBlackColor(CxImage cxImage)
{
	long i;
	int iBlackFlag = 0;
	RGBQUAD *pData = cxImage.GetPalette();
	long nPaletteSize = cxImage.GetPaletteSize() / sizeof(RGBQUAD);
	for (i = 0; i<nPaletteSize; i++)
	{
		if (pData[i].rgbBlue == 0 && pData[i].rgbGreen == 0 && pData[i].rgbRed == 0)
		{
			iBlackFlag = i;
			break;
		}
	}
	return iBlackFlag;
}

//������: GetWhiteColor
//����:  ��ȡ�׵��ǵķ�ʽ
//����:  cxImage ͼ������
//����ֵ: �ڵ���
int OpenCV2CXimage::GetWhiteColor(CxImage cxImage)
{
	long i;
	int iWhiteFlag = 255;
	RGBQUAD *pData = cxImage.GetPalette();
	long nPaletteSize = cxImage.GetPaletteSize() / sizeof(RGBQUAD);
	for (i = 0; i<nPaletteSize; i++)
	{
		if (pData[i].rgbBlue == 255 && pData[i].rgbGreen == 255 && pData[i].rgbRed == 255)
		{
			iWhiteFlag = i;
			break;
		}
	}
	return iWhiteFlag;
}

/*
*����˵����ת��Cximage��IplImage
*����˵����src����ʾԭʼCximageͼ��dst��[out] ��ʾOpencvͼ��IplImage�ṹ
*����ֵ��bool���͡�true����ʾ�ɹ���flase,��ʾʧ�ܡ�
*/
bool OpenCV2CXimage::Cximage2IplImage(CxImage *src, IplImage **dst)
{
	bool bRet = true;
	if (!src || !src->IsValid())
	{
		bRet = false;
		return bRet;
	}
	m_nPalatteCount = src->GetPaletteSize() / sizeof(RGBQUAD);;
	m_pPal = src->GetPalette();
	int iBackColor = GetBlackColor(*src);
	long i = 0, j = 0;
	long nImageWidth = 0, nImageHeight = 0;
	nImageWidth = src->GetWidth();
	nImageHeight = src->GetHeight();
	long nBitCunt = src->GetBpp();
	if (nBitCunt <= 1)
	{
		*dst = cvCreateImage(cvSize(nImageWidth, nImageHeight), IPL_DEPTH_8U, 1);
		cvZero(*dst);
		//ת��Cximage to IplImage
		for (j = 0; j<nImageHeight; j++)
		{
			for (i = 0; i<nImageWidth; i++)
			{
				if (src->GetPixelIndex(i, j) == iBackColor)
				{
					CV_IMAGE_ELEM(*dst, uchar, nImageHeight - 1 - j, i) = 0;
				}
				else
				{
					CV_IMAGE_ELEM(*dst, uchar, nImageHeight - 1 - j, i) = 255;
				}
			}
		}
	}
	else if (nBitCunt <= 8)
	{
		*dst = cvCreateImage(cvSize(nImageWidth, nImageHeight), IPL_DEPTH_8U, 1);
		cvZero(*dst);
		//��Ӧͼ���ɫ�����׼��ɫ��Ĺ�ϵ
		map<int, int> mapPalatte;
		RGBQUAD szSystemPal[256];
		int k = 0;
		for (k = 0; k<256; k++)
		{
			szSystemPal[k].rgbBlue = k;
			szSystemPal[k].rgbGreen = k;
			szSystemPal[k].rgbRed = k;
			szSystemPal[k].rgbReserved = 0;
		}
		int m = 0;
		for (m = 0; m<m_nPalatteCount; m++)
		{
			for (k = 0; k<256; k++)
			{
				if (m_pPal[m].rgbBlue == szSystemPal[k].rgbBlue && m_pPal[m].rgbGreen == szSystemPal[k].rgbGreen && m_pPal[m].rgbRed == szSystemPal[k].rgbRed)
				{
					mapPalatte.insert(make_pair(m, k));
					break;
				}
			}
		}
		//////////////////////////////////////////////////////////////////////////

		//ת��Cximage to IplImage
		map<int, int>::iterator iter;
		BYTE btIndex = 0;
		for (j = 0; j<nImageHeight; j++)
		{
			for (i = 0; i<nImageWidth; i++)
			{
				btIndex = src->GetPixelIndex(i, j);
				iter = mapPalatte.find(btIndex);
				if (iter != mapPalatte.end())
				{
					btIndex = iter->second;
				}
				CV_IMAGE_ELEM(*dst, uchar, nImageHeight - 1 - j, i) = btIndex;
			}
		}
	}
	else if (nBitCunt <= 16)
	{
		*dst = cvCreateImage(cvSize(nImageWidth, nImageHeight), IPL_DEPTH_16U, 1);
		(*dst)->origin = 1;//�ס���ṹ (Windows bitmaps ���) 
		cvZero(*dst);
		//ת��Cximage to IplImage
		for (j = 0; j<nImageHeight; j++)
		{
			for (i = 0; i<nImageWidth; i++)
			{
				BYTE *pSrc = src->GetBits(j) + 2 * i;
				CV_IMAGE_ELEM(*dst, ushort, j, i) = (*pSrc) + (*(pSrc + 1)) * 256;
			}
		}
	}
	else //24ɫ
	{
		*dst = cvCreateImage(cvSize(nImageWidth, nImageHeight), IPL_DEPTH_8U, 3);
		(*dst)->origin = 1;//�ס���ṹ (Windows bitmaps ���) 
		cvZero(*dst);
		//ת��Cximage to IplImag
		memcpy((*dst)->imageData, src->GetBits(0), src->GetSize());
	}
	return bRet;
}

/*
*����˵����ת��IplImage��Cximage
*����˵����src����ʾOpencvͼ��IplImage�ṹ��dst��[out] ��ʾ���Cximageͼ��;nBpp,��ʾ���Cximageͼ��λ��ռ����λ[һ������ռ����λ]
*����ֵ��bool���͡�true����ʾ�ɹ���flase,��ʾʧ�ܡ�
*/
bool OpenCV2CXimage::IplImage2Cximage(IplImage *src, CxImage *dst, long nBpp)
{
	bool bRet = true;
	if (src == NULL || dst == NULL)
	{
		return false;
	}
	if (!(nBpp == 1 || nBpp == 8 || nBpp == 24))
	{
		return false;
	}
	long i = 0, j = 0;
	CvSize csImageSize = cvGetSize(src);
	CxImage ciTmp;
	ciTmp.Create(csImageSize.width, csImageSize.height, src->depth, CXIMAGE_FORMAT_BMP);
	if (src->depth == IPL_DEPTH_8U)//�Ҷ�
	{
		ciTmp.SetStdPalette();
		BYTE btIndex = 0;
		for (j = 0; j<csImageSize.height; j++)
		{
			for (i = 0; i<csImageSize.width; i++)
			{
				btIndex = CV_IMAGE_ELEM(src, uchar, csImageSize.height - 1 - j, i);
				ciTmp.SetPixelIndex(i, j, btIndex);
			}
		}
	}
	else //��ɫ
	{
		//ת��IplImag to Cximage
		memcpy(ciTmp.GetBits(0), src->imageData, src->imageSize);
	}

	//ת������Ҫ��Ŀ��ͼ��
	dst->Create(csImageSize.width, csImageSize.height, nBpp, CXIMAGE_FORMAT_BMP);
	if (nBpp == ciTmp.GetBpp())
	{
		dst->Copy(ciTmp);
	}
	else
	{
		if (nBpp == 1)//��ֵ
		{
			//��Ӧͼ���ɫ�����׼��ɫ��Ĺ�ϵ
			map<int, int> mapPalatte;
			RGBQUAD szSystemPal[256];
			int k = 0;
			for (k = 0; k<256; k++)
			{
				szSystemPal[k].rgbBlue = k;
				szSystemPal[k].rgbGreen = k;
				szSystemPal[k].rgbRed = k;
				szSystemPal[k].rgbReserved = 0;
			}
			int m = 0;
			for (k = 0; k<256; k++)
			{
				for (m = 0; m<m_nPalatteCount; m++)
				{
					if (m_pPal[m].rgbBlue == szSystemPal[k].rgbBlue && m_pPal[m].rgbGreen == szSystemPal[k].rgbGreen && m_pPal[m].rgbRed == szSystemPal[k].rgbRed)
					{
						mapPalatte.insert(make_pair(k, m));
						break;
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////
			byte btValue = 0;
			map<int, int>::iterator iter;
			long nImageWidth = 0;
			long nImageHeight = 0;
			if (ciTmp.GetBpp()>8)
			{
				ciTmp.GrayScale();
			}
			if (m_nPalatteCount == 2) //��ʾԭʼ��ͼ��Ϊ��ֵͼ��
			{
				dst->SetPalette(m_pPal, m_nPalatteCount);
				btValue = 0;
				nImageWidth = ciTmp.GetWidth();
				nImageHeight = ciTmp.GetHeight();
				for (j = 0; j<nImageHeight; j++)
				{
					for (i = 0; i<nImageWidth; i++)
					{
						btValue = ciTmp.GetPixelIndex(i, j);
						iter = mapPalatte.find(btValue);
						if (iter != mapPalatte.end())
						{
							btValue = iter->second;
						}
						dst->SetPixelIndex(i, j, btValue);
					}
				}
			}
			else
			{
				ciTmp.Threshold(128);
				dst->Copy(ciTmp);
			}
		}
		else if (nBpp == 8)
		{
			//��Ӧͼ���ɫ�����׼��ɫ��Ĺ�ϵ
			map<int, int> mapPalatte;
			RGBQUAD szSystemPal[256];
			int k = 0;
			for (k = 0; k<256; k++)
			{
				szSystemPal[k].rgbBlue = k;
				szSystemPal[k].rgbGreen = k;
				szSystemPal[k].rgbRed = k;
				szSystemPal[k].rgbReserved = 0;
			}
			int m = 0;
			for (k = 0; k<256; k++)
			{
				for (m = 0; m<m_nPalatteCount; m++)
				{
					if (m_pPal[m].rgbBlue == szSystemPal[k].rgbBlue && m_pPal[m].rgbGreen == szSystemPal[k].rgbGreen && m_pPal[m].rgbRed == szSystemPal[k].rgbRed)
					{
						mapPalatte.insert(make_pair(k, m));
						break;
					}
				}
			}
			//////////////////////////////////////////////////////////////////////////
			byte btValue = 0;
			map<int, int>::iterator iter;
			long nImageWidth = 0;
			long nImageHeight = 0;
			if (ciTmp.GetBpp() != 8)
			{
				ciTmp.GrayScale();
			}
			if (m_nPalatteCount == 8) //��ʾԭʼ��ͼ��Ϊ�Ҷ�ͼ��
			{
				dst->SetPalette(m_pPal, m_nPalatteCount);
				btValue = 0;
				nImageWidth = ciTmp.GetWidth();
				nImageHeight = ciTmp.GetHeight();
				for (j = 0; j<nImageHeight; j++)
				{
					for (i = 0; i<nImageWidth; i++)
					{
						btValue = ciTmp.GetPixelIndex(i, j);
						iter = mapPalatte.find(btValue);
						if (iter != mapPalatte.end())
						{
							btValue = iter->second;
						}
						dst->SetPixelIndex(i, j, btValue);
					}
				}
			}
			else
			{
				dst->Copy(ciTmp);
			}
		}
		else
		{
			if (ciTmp.GetBpp() == 24)
			{
				dst->Copy(ciTmp);
			}
			else
			{
				byte btValue = 0;
				COLORREF clValue;
				map<int, int>::iterator iter;
				long nImageWidth = 0;
				long nImageHeight = 0;
				bRet = ciTmp.IncreaseBpp(24);
				dst->Copy(ciTmp);
			}
		}
	}
	return bRet;
}

//ͼ���ʽת��
bool OpenCV2CXimage::CxImageFormatConvert(CxImage *src, CxImage *dst, long imagetype)
{
	bool bRet = true;
	if (src == NULL || dst == NULL)
	{
		return false;
	}
	if (!(imagetype>0 && imagetype <= 19))
	{
		return false;
	}
	if (src->GetType() == imagetype)
	{
		dst->Copy(*src);
	}
	else
	{
		dst->Create(src->GetWidth(), src->GetHeight(), src->GetBpp(), imagetype);
		src->SetType(imagetype);
		dst->Copy(*src);
	}
	return true;
}