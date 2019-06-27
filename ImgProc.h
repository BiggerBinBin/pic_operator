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
	QLabel *imgP_lab;		//ָ��滭����label��ָ��
	QImage imgP_pic;		//�洢��������ͼƬ
	double m_scal;			//��������

	QPoint offest;			//ƫ����
	QPoint alloffest;		//�ܵ�ƫ����
	int currenW;
	int currenH;
	int imgW;
	int imgH;
	int action;				//����
	static bool press;
	static QPoint PreDot;
	QRect Paint;         //�滭����
	enum  Type {
		None = 0,
		Amplification,
		Shrink,
		Move
	};

};

