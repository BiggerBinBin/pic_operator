#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_viewTest.h"
#include "qfiledialog.h"
#include "qscreen.h"
#include "qimage.h"
#include <qgraphicsitem.h>
#include <qgraphicsscene.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include <qpoint.h>
#include <qevent.h>
#include <QGraphicsView>
#include <qstring.h>
#include <qguiapplication.h>
#include <QObject>
#include <opencv2/opencv.hpp>
#include <qlabel.h>
#include "ImgProc.h"
#include <qpainter.h>
#include <qrect.h>
#include <QPixmap>
#include <cmath>
#include <iostream>
#include <QPainter>
//#include <algorithm>
#define min(a,b) (((a)<(b))?(a):(b))
#define max(x,y) (((x)>(y))?(x):(y))
#define CV_32F 5
#define PI 3.14159265359
class viewTest : public QMainWindow
{
	Q_OBJECT

public:
	viewTest(QWidget *parent = Q_NULLPTR);
	QImage imgP_Mat2QImage(cv::Mat const& src);
	cv::Mat imgP_QImg2Mat(QImage pic);
	QImage qImg;
    //bool event(QEvent * event);
	bool eventFilter(QObject *obj, QEvent *event);

signals:
	void showImg();

private:
	Ui::viewTestClass ui;



private slots:

	void on_openPic_clicked();
	void on_savePic_clicked();

	
	void slot_open_img_file();
	void slot_qclicklabel_wheel_move(QWheelEvent* evt);
	// used to select edge point and translate image
	void slot_qclicklabel_mouse_press(QMouseEvent* evt);
	void slot_qclicklabel_mouse_move(QMouseEvent* evt);
	void slot_qclicklabel_mouse_release(QMouseEvent* evt);
	void slot_qclicklabel_mouse_rotate(QWheelEvent* evt);
	//cv::Mat slot_qclicklabel_mouse_angelRote(cv::Mat&, int angle);
	//cv::Mat translation_img(cv::Mat&, int xOffset, int yOffset);

	void on_drawbutton_clicked();
		

private:
	int drawFlag;
	bool isDraw;

public:
	

	QRect Paint;         //绘画区域
	int label_width;
	int label_height;

	//图片显示初始位置
	int image_start_x;
	int image_start_y;

	//缩放比例
	float image_ratio_x;
	float image_ratio_y;

	//缩放的参数
	float zoom_step;
	float zoom_ratio_max;
	float zoom_ratio_min;
	float zoom_current_scale;

	//旋转角度
	double angle;

	QImage* qimage_front_image;

	bool is_translate_image;
	int mouse_last_position_x;
	int mouse_last_position_y;
	int mouse_new_position_x;
	int mouse_new_position_y;

	bool mouse_left_press;

	void translate_image();
	void image_show();


	
};
