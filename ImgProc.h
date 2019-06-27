#pragma once
#include <qevent.h>
#include <qlabel.h>
#include <opencv2/opencv.hpp>
#include <qimage.h>
#include <qsize.h>
#include <math.h>
#include <qpainter.h>
#include <qpixmap.h>

class ImgProc:public QLabel
{
public:
	explicit ImgProc(QLabel*);
	~ImgProc();
	void wheelEvent(QWheelEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void mouseReleseEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseDoubleClickEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);
	//bool eventFilter(QObject *obj, QEvent *event);
	//void paintEvent();
	void setPic(QImage pic);
	cv::Mat imgP_QImg2Mat(QImage pic);
	QImage imgP_Mat2QImage(cv::Mat const& src);
private:
	QLabel *imgP_lab;		//指向绘画区域label的指针
	QImage imgP_pic;		//存储传过来的图片
	double m_scal;			//放缩比率

	QPoint offest;			//偏移量
	QPoint alloffest;		//总的偏移量
	int currenW;
	int currenH;
	int imgW;
	int imgH;
	int action;				//动作
	static bool press;
	static QPoint PreDot;
	QRect Paint;         //绘画区域
	enum  Type {
		None = 0,
		Amplification,
		Shrink,
		Move
	};

};

