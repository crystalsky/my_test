#ifndef ImageProcessor_h__
#define ImageProcessor_h__

#include <QImage>
#include <QColor>
#include <QDir>
#include <QRunnable>
#include "QMLStudyBase.h"
#include "qqml.h"
namespace Study_QML
{
	class ImageProcessorPrivate;
	class ImageProcessor : public QObject
	{
		Q_OBJECT
		Q_DECLARE_PRIVATE(ImageProcessor)
		Q_ENUMS(ImageAlgorithm)
		Q_PROPERTY(QString sourceFile READ sourceFile)
		Q_PROPERTY(ImageAlgorithm algorithm READ algorithm)

	Q_SIGNALS:
		void finished(const QString& newFile);
		void progress(int value);

	public:
		ImageProcessor(QObject* parent = NULL);
		~ImageProcessor();

		enum ImageAlgorithm
		{
			Gray = 0,
			Binarize,
			Negative,
			Emboss,
			Sharpen,
			Soften,
			AlgorithmCount
		};

		QString sourceFile()const;

		ImageAlgorithm algorithm()const;

		void setAlgorithm(ImageAlgorithm algorithm);

	public Q_SLOTS:
		void process(const QString& fileName, ImageAlgorithm algorithm);
		void abort(const QString& fileName, ImageAlgorithm algorithm);
	private:
		ImageProcessorPrivate* m_d;
	};

	class ImageProcessorWidget : public CQuickViewWidgetBase
	{
	public:
		ImageProcessorWidget( QWidget* pParent /*= NULL*/ ) :
			CQuickViewWidgetBase("ImageProcessorTest.qml", pParent)
		{
			qmlRegisterType<ImageProcessor>("My.ImageProcessor", 1, 0, "ImageProcessor");

			refresh();
		}
	};
}

namespace PictureProcessorAlgorithm
{
	//黑白处理
	static void _binarize(const QString& strFile, const QString& strDestFile)
	{
		QImage img(strFile);
		if (img.isNull())
		{
			return;
		}

		int width = img.width();
		int height = img.height();
		QRgb color;
		QRgb everage;
		QRgb black = qRgb(0, 0, 0);
		QRgb white = qRgb(255, 255, 255);

		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				color = img.pixel(i, j);
				everage = (qRed(color) + qGreen(color) + qBlue(color)) / 3;
				img.setPixel(i, j, everage >= 128 ? white : black);
			}
		}

		img.save(strDestFile);
	}

	//灰度
	static void _gray(const QString& strFile, const QString& strDestFile)
	{
		QImage img(strFile);
		if (img.isNull())
		{
			return;
		}

		int width = img.width();
		int height = img.height();
		QRgb color;
		int gray;

		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				color = img.pixel(i, j);
				//加权平均值法
				gray = qGray(color);
				img.setPixel(i, j, qRgba(gray, gray, gray, qAlpha(color)));
			}
		}

		img.save(strDestFile);
	}

	//底片
	static void _negative(const QString& strFile, const QString& strDestFile)
	{
		QImage img(strFile);
		if (img.isNull())
		{
			return;
		}

		int width = img.width();
		int height = img.height();
		QRgb color;

		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				color = img.pixel(i, j);

				//取255与像互不的RGB分量差
				img.setPixel(i, j, qRgba(
					255 - qRed(color),
					255 - qGreen(color),
					255 - qBlue(color),
					qAlpha(color)));
			}
		}

		img.save(strDestFile);
	}

	//锐化
	//G[f(i,j)] = abs(f(i,j) - f(i+1, j)) + abs(f(i,j) - f(i, j+1))
	static void _shapen(const QString& strFile, const QString& strDestFile)
	{
		QImage img(strFile);
		if (img.isNull())
		{
			return;
		}

		int width = img.width();
		int height = img.height();
		int threshold = 80;
		QImage shapen(width, height, QImage::Format_ARGB32);
		int r = 0, g = 0, b = 0, gradientR = 0, gradientG = 0, gradientB = 0;
		QRgb rgb00, rgb01, rgb10;

		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				if (img.valid(i, j) && img.valid(i + 1, j) && img.valid(i, j + 1))
				{
					rgb00 = img.pixel(i, j);
					rgb01 = img.pixel(i, j + 1);
					rgb10 = img.pixel(i + 1, j);

					r = qRed(rgb00);
					g = qGreen(rgb00);
					b = qBlue(rgb00);

					gradientR = abs(qRed(rgb00) - qRed(rgb10)) +
						abs(qRed(rgb00) - qRed(rgb01));
					gradientG = abs(qGreen(rgb00) - qGreen(rgb10)) +
						abs(qGreen(rgb00) - qGreen(rgb01));
					gradientB = abs(qBlue(rgb00) - qBlue(rgb10)) +
						abs(qBlue(rgb00) - qBlue(rgb01));

					if (gradientR > threshold)
					{
						r = qMin(gradientR + 100, 255);
					}

					if (gradientG > threshold)
					{
						g = qMin(gradientG + 100, 255);
					}

					if (gradientB > threshold)
					{
						b = qMin(gradientB + 100, 255);
					}

					shapen.setPixel(i, j, qRgb(r, g, b));
				}
			}
		}

		img.save(strDestFile);
	}

	//模糊
	static void _soften(const QString& strFile, const QString& strDestFile)
	{
		QImage img(strFile);
		if (img.isNull())
		{
			return;
		}

		int width = img.width();
		int height = img.height();

		int r = 0, g = 0, b = 0;
		for (int i = 1; i < width - 1; ++i)
		{
			for (int j = 1; j < height - 1; ++j)
			{
				r = 0;
				g = 0;
				b = 0;

				//取九宫格平均值
				for (int k = 0; k < 9; ++k)
				{
					int at_x = 0;
					int at_y = 0;

					switch (k)
					{
					case 0:
						{
							at_x = i - 1;
							at_y = j - 1;
						}
						break;

					case 1:
						{
							at_x = i;
							at_y = j - 1;
						}
						break;

					case 2:
						{
							at_x = i + 1;
							at_y = j - 1;
						}
						break;

					case 3:
						{
							at_x = i + 1;
							at_y = j;
						}
						break;

					case 4:
						{
							at_x = i + 1;
							at_y = j + 1;
						}
						break;

					case 5:
						{
							at_x = i;
							at_y = j + 1;
						}
						break;

					case 6:
						{
							at_x = i - 1;
							at_y = j + 1;
						}
						break;

					case 7:
						{
							at_x = i - 1;
							at_y = j;
						}
						break;

					case 8:
						{
							at_x = i;
							at_y = j;
						}
						break;
					}

					QRgb color = img.pixel(at_x, at_y);
					r += qRed(color);
					g += qGreen(color);
					b += qBlue(color);
				}

				r = r / 9.0;
				g = g / 9.0;
				b = b / 9.0;

				r = qMin(255, qMax(0, r));
				g = qMin(255, qMax(0, g));
				b = qMin(255, qMax(0, b));

				img.setPixel(i, j, qRgb(r, g, b));
			}
		}

		img.save(strDestFile);
	}

	//浮雕
	static void _emboss(const QString& strFile, const QString& strDestFile)
	{
		QImage img(strFile);
		if (img.isNull())
		{
			return;
		}

		int width = img.width();
		int height = img.height();
		QRgb color;
		QRgb preColor = 0;
		QRgb newColor = 0;
		int gray, r, g, b;
		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				color = img.pixel(i, j);

				r = qRed(color) - qRed(preColor) + 128;

				g = qGreen(color) - qGreen(preColor) + 128;

				b = qBlue(color) - qBlue(preColor) + 128;

				gray = qGray(r, g, b);

				newColor = qRgba(gray, gray, gray, qAlpha(color));

				//取255与像互不的RGB分量差
				img.setPixel(i, j, newColor);

				preColor = newColor;
			}
		}

		img.save(strDestFile);
	}
}

#endif // ImageProcessor_h__
