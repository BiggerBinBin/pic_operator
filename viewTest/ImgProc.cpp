#include "ImgProc.h"
#include <qmessagebox.h>
ImgProc::ImgProc(QLabel*lab)
{
	
	imgP_lab = lab;
	m_scal = 1;
	Paint = lab->rect();
	
	
}

QPoint ImgProc::PreDot = QPoint(0, 0);
bool ImgProc::press = false;
ImgProc::~ImgProc()
{
}
//滚轮事件
void ImgProc::wheelEvent(QWheelEvent *event)
{
	if (imgP_pic.isNull())
		return;
	cv::Mat tem = imgP_QImg2Mat(imgP_pic);
	cv::Mat result;
	int width = imgP_lab->width();
	int height = imgP_lab->height();
	
	//1是基点，最小是1/10倍，最大19/10倍
	m_scal += event->delta() > 0 ? 0.1 : -0.1;
	if (std::fabs(m_scal-1) > 0.9)
	{ 
		m_scal = m_scal > 1 ? 1.9 : 0.1;
		return;
	}
	//缩放图片，这里的Size(0,0)和m_scal不能同时为0；
	cv::resize(tem, result, cv::Size(0,0), m_scal, m_scal ,cv::INTER_AREA);
	QImage t_img = imgP_Mat2QImage(result);
	imgP_lab->setPixmap(QPixmap::fromImage(t_img));

}

//鼠标按下事件
void ImgProc::mousePressEvent(QMouseEvent *event)
{
	//判断是否为左键并且在画图区域
	if (event->button() == Qt::LeftButton && Paint.contains(event->pos()))
	{
		press = true;
		imgP_lab->setCursor(Qt::OpenHandCursor);
		PreDot = event->pos();
		imgP_lab->update();
	}
}
void ImgProc::mouseReleseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton && press)
	{
		press = false;
		imgP_lab->setCursor(Qt::ArrowCursor);
	    imgP_lab->update();
	}
}
void ImgProc::mouseMoveEvent(QMouseEvent *event)
{
	if (press)
	{
		offest.setX(event->pos().x() - PreDot.x());
		offest.setY(event->pos().y() - PreDot.y());
		PreDot = event->pos();
		action = ImgProc::Move;
		imgP_lab->update();
	}
	
}

void ImgProc::mouseDoubleClickEvent(QMouseEvent *event)
{


}
void ImgProc::paintEvent(QPaintEvent *event)

{
	QLabel::paintEvent(event);
	QPainter painter(this->imgP_lab);
	int NowW = m_scal * currenW;
	int NowH = m_scal * currenH;
	if (action == ImgProc::Move)                    //移动
	{
		int offsetx = alloffest.x() + offest.x();
		alloffest.setX(offsetx);
		int offsety = alloffest.y() + offest.y();
		alloffest.setY(offsety);
		action = ImgProc::None;
		imgP_lab->update();
	}
	
	painter.begin(this->imgP_lab);
	if (abs(alloffest.x()) >= (Paint.width() / 2 + NowW / 2 - 10))    //限制X偏移值
	{
		if (alloffest.x() > 0)
			alloffest.setX(Paint.width() / 2 + NowW / 2 - 10);
		else
			alloffest.setX(-Paint.width() / 2 + -NowW / 2 + 10);
	}
	if (abs(alloffest.y()) >= (Paint.height() / 2 + NowH / 2 - 10))    //限制Y偏移值
	{
		if (alloffest.y() > 0)
			alloffest.setY(Paint.height() / 2 + NowH / 2 - 10);
		else
			alloffest.setY(-Paint.height() / 2 + -NowH / 2 + 10);

	}

	int x = Paint.width() / 2 + alloffest.x() - NowW / 2;
	if (x < 0)
		x = 0;

	int y = Paint.height() / 2 + alloffest.y() - NowH / 2;
	if (y < 0)
		y = 0;

	int  sx = NowW / 2 - Paint.width() / 2 - alloffest.x();
	if (sx < 0)
		sx = 0;

	int  sy = NowH / 2 - Paint.height() / 2 - alloffest.y();
	if (sy < 0)
		sy = 0;

	int w = (NowW - sx) > Paint.width() ? Paint.width() : (NowW - sx);
	if (w > (Paint.width() - x))
		w = Paint.width() - x;

	int h = (NowH - sy) > Paint.height() ? Paint.height() : (NowH - sy);
	if (h > (Paint.height() - y))
		h = Paint.height() - y;
	painter.drawRect(Paint.x() - 1, Paint.y() - 1, Paint.width() + 1, Paint.height() + 1); //画框
	painter.drawTiledPixmap(x + Paint.x(), y + Paint.y(), w, h, QPixmap::fromImage(imgP_pic), sx, sy);             //绘画图形
	painter.drawRect(10, 10, 100, 100);
	painter.end();
}
void ImgProc::setPic(QImage pic)
{
	imgP_pic = pic;
	currenW = imgP_pic.width();
	currenH = imgP_pic.height();
	cv::Mat tem = imgP_QImg2Mat(imgP_pic);
	cv::Mat result;
	cv::Size size(imgP_lab->width(), imgP_lab->height());
	cv::resize(tem, result, size, cv::INTER_AREA);
	QImage t_img = imgP_Mat2QImage(result);
	imgP_lab->setPixmap(QPixmap::fromImage(t_img));
	
}
cv::Mat ImgProc::imgP_QImg2Mat(QImage pic)
{
	cv::Mat mat;
	//qDebug() << pic.format();
	switch (pic.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(pic.height(), pic.width(), CV_8UC4, (void*)pic.constBits(), pic.bytesPerLine());
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(pic.height(), pic.width(), CV_8UC3, (void*)pic.constBits(), pic.bytesPerLine());
		cv::cvtColor(mat, mat, cv::COLOR_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
		mat = cv::Mat(pic.height(), pic.width(), CV_8UC1, (void*)pic.constBits(), pic.bytesPerLine());
		break;
	}
	return mat;

	//Mat::Mat(int _rows, int _cols, int _type, void* _data, size_t _step)
	/*
		int _rows		Number of rows in a 2D array.
		int _cols		Number of columns in a 2D array.
		int _type		Array type. Use CV_8UC1, ..., CV_64FC4 to create 1-4 channel matrices, or CV_8UC(n), ...,
						CV_64FC(n) to create multi-channel (up to CV_CN_MAX channels) matrices.
		void* _data		Pointer to the user data. Matrix constructors that take data and step parameters do not allocate matrix data
		size_t _step	Number of bytes each matrix row occupies
	*/
}
QImage ImgProc::imgP_Mat2QImage(cv::Mat const& src)
{
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (src.type() == CV_8UC1)
	{
		QImage image(src.cols, src.rows, QImage::Format_Indexed8);
		// Set the color table (used to translate colour indexes to qRgb values)
		image.setColorCount(256);
		for (int i = 0; i < 256; i++)
		{
			image.setColor(i, qRgb(i, i, i));
		}
		// Copy input Mat
		uchar *pSrc = src.data;
		for (int row = 0; row < src.rows; row++)
		{
			uchar *pDest = image.scanLine(row);
			memcpy(pDest, pSrc, src.cols);
			pSrc += src.step;
		}
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (src.type() == CV_8UC3)
	{
		// Copy input Mat
		const uchar *pSrc = (const uchar*)src.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, src.cols, src.rows, src.step, QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (src.type() == CV_8UC4)
	{
		//qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar *pSrc = (const uchar*)src.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, src.cols, src.rows, src.step, QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		//qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}

}