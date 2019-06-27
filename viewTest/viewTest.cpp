#include "viewTest.h"
#include <opencv2/core/core.hpp>        
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>  
#include <qdebug.h>

viewTest::viewTest(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QObject::connect(this, SIGNAL(showImg()), this, SLOT(recvShowPicSignal()));	//打开图片后显示
	ui.disply_lab->setMouseTracking(true);										//鼠标跟踪
	ui.disply_lab->installEventFilter(this);
	ui.disply_lab->setFocusPolicy(Qt::StrongFocus);
	
	//ui.disply_lab->setAutoFillBackground(true);
	//QPalette label_palette = ui.disply_lab->palette();
	//label_palette.setColor(QPalette::Window, Qt::red);   //change the background 
	//ui.disply_lab->setPalette(label_palette);
	//ui.disply_lab->setEnabled(true);
	
	Paint = QRect(ui.disply_lab->rect());
	label_width = ui.disply_lab->width();
	label_height = ui.disply_lab->height();

	image_start_x = 0;
	image_start_y = 0;
	
	image_ratio_x = 1.0f;
	image_ratio_y = 1.0f;

	zoom_step = 0.5;
	zoom_ratio_min = 0.4;
	zoom_ratio_max = 4;
	zoom_current_scale = 1.0f;

	mouse_left_press = false;

	angle = 0;
	drawFlag = 0;
}
bool viewTest::eventFilter(QObject *obj, QEvent *event)
{

	if (event->type() == QEvent::MouseButtonPress)
	{
		QMouseEvent *mouse = dynamic_cast<QMouseEvent*>(event);
		if (mouse->button() == Qt::LeftButton && obj == ui.disply_lab)
		{
			slot_qclicklabel_mouse_press(mouse);
		}

	}
	else if (event->type() == QEvent::MouseButtonRelease)
	{
		QMouseEvent *mouse = dynamic_cast<QMouseEvent*>(event);
		if (mouse->button() == Qt::LeftButton /*&& obj == ui.disply_lab*/)
		{
			slot_qclicklabel_mouse_release(mouse);
		}
	}
	else if (event->type() == QEvent::MouseMove)
	{
		QMouseEvent *mouse = dynamic_cast<QMouseEvent*>(event);
		slot_qclicklabel_mouse_move(mouse);
	}
	else if(event->type()==QEvent::Wheel && obj == ui.disply_lab)
	{
		
		QWheelEvent *mouse = dynamic_cast<QWheelEvent*>(event);
		
		if (QApplication::keyboardModifiers() == Qt::ControlModifier)
			slot_qclicklabel_mouse_rotate(mouse);
		else
			slot_qclicklabel_wheel_move(mouse);
	}
	//一定要返回事件，否则后续的动作将被忽略
	return QObject::eventFilter(obj, event);
}

//打开图片
void viewTest::on_openPic_clicked()			//打开图片
{
	//打开文件打开对话框
	QString filePath = QFileDialog::getOpenFileName(NULL, QObject::tr("选择图像"), ".",QObject::tr("Images (*.png *.bmp *.jpg)"));
	if (filePath.isEmpty())
	{
		return;//路径为空，退出
	}
	else
	{
		//加载图片
		
		qimage_front_image = new QImage();
		
		if (!qimage_front_image->load(filePath))
		{
			QMessageBox::information(NULL, QObject::tr("打开图像失败"), QObject::tr("打开图像失败!"));
			delete qimage_front_image;
			return;
		}
		else
		{
			//记录图片的xy比率
			image_ratio_x = qimage_front_image->width()*1.0 / ui.disply_lab->width();
			image_ratio_y = qimage_front_image->height()*1.0 / ui.disply_lab->height();

			//显示
			QImage temp= qimage_front_image->copy();
			QImage *qimage_scaled = new QImage();
			*qimage_scaled = temp.scaled(QSize(ui.disply_lab->width(), ui.disply_lab->height()), Qt::IgnoreAspectRatio);
			ui.disply_lab->setPixmap(QPixmap::fromImage(*qimage_scaled));
	
			qImg = qimage_scaled->copy();

			//重置
			zoom_current_scale = 1;
			image_start_x = image_start_y = 0;
			emit showImg();//发出信号，我已经打开图片了，告诉别人显示图片
		}
	}

}
//保存图片
void viewTest::on_savePic_clicked()
{
	QString filePath = QFileDialog::getSaveFileName(this, QObject::tr("保存图片"), QObject::tr("Images(*.png *.jpg *.bmp)"));
	QScreen *screen = QGuiApplication::primaryScreen();
	screen->grabWindow(ui.disply_lab->winId()).save(filePath);
}



cv::Mat viewTest::imgP_QImg2Mat(QImage pic)
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
QImage viewTest::imgP_Mat2QImage(cv::Mat const& src)
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
		QImage image(pSrc, src.cols, src.rows, src.cols*src.channels(), QImage::Format_RGB888);
		return image.rgbSwapped();
	}
	else if (src.type() == CV_8UC4)
	{
		//qDebug() << "CV_8UC4";
		// Copy input Mat
		const uchar *pSrc = (const uchar*)src.data;
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, src.cols, src.rows, src.cols*src.channels(), QImage::Format_ARGB32);
		return image.copy();
	}
	else
	{
		//qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}

}

void viewTest::slot_qclicklabel_wheel_move(QWheelEvent* evt)
{
	//设置放缩的步进大小，这个640可以按需设定
	float degree_delta = evt->delta()*1.0 / 640;
	if (qimage_front_image==NULL)
	{
		return;
	}
	//判断是否到最大最小倍数
	if (zoom_current_scale+degree_delta>zoom_ratio_max||zoom_current_scale+degree_delta<zoom_ratio_min)
	{
		return;
	}
	//记录当前放缩比
	zoom_current_scale += degree_delta;
	//x,y两个方向的放缩比
	image_ratio_x = qimage_front_image->width()*1.0 / (zoom_current_scale*qimage_front_image->width());
	image_ratio_y = qimage_front_image->height()*1.0 / (zoom_current_scale*qimage_front_image->height());
	ui.label_scan->setText(QString::number(zoom_current_scale*100)+"%");
	image_show();

}
void viewTest::slot_qclicklabel_mouse_press(QMouseEvent* evt)
{
	//把鼠标按下标志设为真
	mouse_left_press = true;
	//记录按下时的位置
	mouse_last_position_x = evt->localPos().x();
	mouse_last_position_y = evt->localPos().y();
}
void viewTest::slot_qclicklabel_mouse_move(QMouseEvent* evt)
{
	//判断是否有载入图片
	if(qimage_front_image)
	{ 
		//是否鼠标左键有按下
		if (mouse_left_press)
		{
			//记录新位置
			mouse_new_position_x = evt->localPos().x();
			mouse_new_position_y = evt->localPos().y();

			
			//移动图片
			translate_image();
		}
	}
}
void viewTest::slot_qclicklabel_mouse_release(QMouseEvent* evt)
{
	mouse_left_press = false;
	if (drawFlag)
	{
		mouse_last_position_x = mouse_new_position_x;
		mouse_last_position_y = mouse_new_position_y;
	}
}

void viewTest::slot_qclicklabel_mouse_rotate(QWheelEvent* evt)
{
	if(qimage_front_image!=NULL)
		angle = evt->delta() > 0 ? ++angle : --angle;
	image_show();
	
	
}
void viewTest::slot_open_img_file()
{

}
void viewTest::image_show()
{
	if (qimage_front_image==NULL)
	{
		
		return;
	}
	QImage qimage_temp = qimage_front_image->copy();
	QImage *qimage_scaled = new QImage;

	//画框框模式
	if (drawFlag)
	{
		
		QImage img;
		img.load("1.jpg");
		cv::Mat tempMat = imgP_QImg2Mat(img);
		cv::Rect rect(mouse_last_position_x, mouse_last_position_y,abs( mouse_new_position_x-mouse_last_position_x), abs(mouse_new_position_y-mouse_last_position_y));
		cv::rectangle(tempMat, rect, cv::Scalar(255, 0, 0), 1, cv::LINE_8, 0);
		qimage_temp = imgP_Mat2QImage(tempMat);
		ui.disply_lab->setPixmap(QPixmap::fromImage(qimage_temp));
		
	}
	//移动操作模式
	else
	{ 
		cv::Mat tempMat = imgP_QImg2Mat(qimage_temp);
		cv::Mat warpMat(cv::Size(2, 3),tempMat.type());
	
		//旋转中心点
		cv::Point2f centerP = cv::Point2f(qimage_front_image->width() / 2, qimage_front_image->height() / 2);

		cv::Mat retultImg=cv::Mat::zeros(tempMat.cols, tempMat.rows, tempMat.type());
	

		warpMat = cv::getRotationMatrix2D(centerP, angle, zoom_current_scale);

		cv::Rect bbox = cv::RotatedRect(centerP, tempMat.size(), angle).boundingRect();
		warpMat.at<double>(0, 2) += bbox.width / 2.0 - centerP.x;
		warpMat.at<double>(1, 2) += bbox.height / 2.0 - centerP.y;
		cv::warpAffine(tempMat, retultImg, warpMat, bbox.size());

	
		qimage_temp = imgP_Mat2QImage(retultImg);
	
		*qimage_scaled = qimage_temp.scaled(QSize(ui.disply_lab->width()*zoom_current_scale, ui.disply_lab->height()*zoom_current_scale),
			Qt::KeepAspectRatioByExpanding).copy(image_start_x, image_start_y, ui.disply_lab->width(), ui.disply_lab->height());
		ui.disply_lab->setPixmap(QPixmap::fromImage(*qimage_scaled));

		//Qt::KeepAspectRatio 这个模式图片旋转图片时会拉伸，有点像斜切的那样
		//Qt::IgnoreAspectRatio 这个不会
		//Qt::KeepAspectRatioByExpanding 这个也不会

		mouse_last_position_x = mouse_new_position_x;	//更新坐标
		mouse_last_position_y = mouse_new_position_y;
	}

	//千万要加上这句，不然你的内存...
	delete qimage_scaled;
	
		
	
	
}
void viewTest::translate_image()
{
	//两点间的距离，不开方
	int distance = (mouse_new_position_x - mouse_last_position_x)*(mouse_new_position_x - mouse_last_position_x) +
				   (mouse_new_position_y - mouse_last_position_y)*(mouse_new_position_y - mouse_last_position_y);
	//移动幅度太小，则忽略
	if (distance<2)
	{
		return;
	}
	char str[100] = { " " };
	
	//计算移动距离
	//要乘以-1，不然移动的方向会相反
	int delta_x =  -1*(mouse_new_position_x - mouse_last_position_x);
	int delta_y =  -1*(mouse_new_position_y - mouse_last_position_y);
	image_start_x += delta_x;
	image_start_y += delta_y;

	//限制右方向移动范围，最大为图片宽的一半
	if (image_start_x < -qimage_front_image->width()/2)
		image_start_x = -qimage_front_image->width() / 2;

	//限制下方向移动范围，最大同上
	if (image_start_y< -qimage_front_image->height() / 2)
		image_start_y = -qimage_front_image->height() / 2;
	//限制左方向移动范围，最大同上
	if (image_start_x > qimage_front_image->width() / 2)
		image_start_x = qimage_front_image->width() / 2;
	//限制上方向移动范围，最大同上
	if (image_start_y > qimage_front_image->height() / 2)
		image_start_y = qimage_front_image->height() / 2;


	//显示
	image_show();

	
	
}
void viewTest::on_drawbutton_clicked()
{
	drawFlag = (drawFlag == 1) ? 0 : 1;
	if (drawFlag)
	{
		QScreen *screen = QGuiApplication::primaryScreen();
		screen->grabWindow(ui.disply_lab->winId()).save(QString("1.jpg"));
	}
	
}


//效果不好
//cv::Mat viewTest::slot_qclicklabel_mouse_angelRote(cv::Mat& matSrc, int angle)
////cv::Mat angelRotate(cv::Mat& src, int angle)
//{
//	
//		float theta = angle * CV_PI / 180.0;
//		int nRowsSrc = matSrc.rows;
//		int nColsSrc = matSrc.cols;
//		// 如果是顺时针旋转
//		//if (!direction)
//		//	theta = 2 * CV_PI - theta;
//		// 全部以逆时针旋转来计算
//		// 逆时针旋转矩阵
//		float matRotate[3][3]{
//			{std::cos(theta), -std::sin(theta), 0},
//			{std::sin(theta), std::cos(theta), 0 },
//			{0, 0, 1}
//		};
//		float pt[3][2]{
//			{ 0, nRowsSrc },
//			{nColsSrc, nRowsSrc},
//			{nColsSrc, 0}
//		};
//		for (int i = 0; i < 3; i++)
//		{
//			float x = pt[i][0] * matRotate[0][0] + pt[i][1] * matRotate[1][0];
//			float y = pt[i][0] * matRotate[0][1] + pt[i][1] * matRotate[1][1];
//			pt[i][0] = x;
//			pt[i][1] = y;
//		}
//		// 计算出旋转后图像的极值点和尺寸
//		float fMin_x = min(min(min(pt[0][0], pt[1][0]), pt[2][0]), (float)0.0);
//		float fMin_y = min(min(min(pt[0][1], pt[1][1]), pt[2][1]), (float)0.0);
//		float fMax_x = max(max(max(pt[0][0], pt[1][0]), pt[2][0]), (float)0.0);
//		float fMax_y = max(max(max(pt[0][1], pt[1][1]), pt[2][1]), (float)0.0);
//		int nRows = cvRound(fMax_y - fMin_y + 0.5) + 1;
//		int nCols = cvRound(fMax_x - fMin_x + 0.5) + 1;
//		int nMin_x = cvRound(fMin_x + 0.5);
//		int nMin_y = cvRound(fMin_y + 0.5);
//		// 拷贝输出图像
//		cv::Mat matRet(nRows, nCols, matSrc.type(), cv::Scalar(0));
//		for (int j = 0; j < nRows; j++)
//		{
//			for (int i = 0; i < nCols; i++)
//			{
//				// 计算出输出图像在原图像中的对应点的坐标，然后复制该坐标的灰度值
//				// 因为是逆时针转换，所以这里映射到原图像的时候可以看成是，输出图像
//				// 到顺时针旋转到原图像的，而顺时针旋转矩阵刚好是逆时针旋转矩阵的转置
//				// 同时还要考虑到要把旋转后的图像的左上角移动到坐标原点。
//				int x = (i + nMin_x) * matRotate[0][0] + (j + nMin_y) * matRotate[0][1];
//				int y = (i + nMin_x) * matRotate[1][0] + (j + nMin_y) * matRotate[1][1];
//				if (x >= 0 && x < nColsSrc && y >= 0 && y < nRowsSrc)
//				{
//					matRet.at<cv::Vec3b>(j, i) = matSrc.at<cv::Vec3b>(y, x);
//				}
//			}
//		}
//		return matRet;
//	
//}
//效果不好
//cv::Mat viewTest::translation_img(cv::Mat& src, int xOffset, int yOffset)
//{
//	//std::string str1 = "../pic/src" + std::to_string(index++) + ".jpg";
//	//cv::imwrite(str1, src);
//	int nRows = src.rows;
//	int nCols = src.cols;
//	//cv::Size size(src.rows + abs(xOffset), src.cols + abs(yOffset));
//	
//	cv::Mat resultImage(nRows,nCols,src.type());
//	//resultImage = cv::Scalar::all(255);
//
//	//cv::Mat t_mat = cv::Mat::zeros(2, 3, CV_32FC1);
//
//	//t_mat.at<float>(0, 0) = 1;
//	//t_mat.at<float>(0, 2) = xOffset; //水平平移量
//	//t_mat.at<float>(1, 1) = 1;
//	//t_mat.at<float>(1, 2) = yOffset; //竖直平移量
//	//cv::Size size(label_width, label_height);
//	//cv::warpAffine(src, resultImage, t_mat, size);
//	//int n = src.channels();
//	//ui.label_scan->setText(QString::number(n));
//	for (int i = 0; i < nRows; i++)
//	{
//		
//		for (int j = 0; j < nCols; j++)
//		{
//			//平移后坐标映射到原图像
//			int x = j - xOffset;
//			int y = i - yOffset;
//			
//			//qDebug() << "x:" << x << "y:" << y;
//			//保证映射后的坐标在原图像范围内
//			if (x >= 0 && y >= 0 && x < nCols && y < nRows)
//			{
//				resultImage.at<cv::Vec3b>(i, j) = src.ptr<cv::Vec3b>(y)[x];//src.at<cv::Vec3b>(y, x);
//				 //resultImage.at<cv::Vec3b>(i, j)[1] = src.at<cv::Vec3b>(y, x)[1];
//				 //resultImage.at<cv::Vec3b>(i, j)[2] = src.at<cv::Vec3b>(y, x)[2];
//				 
//			}
//
//
//		}
//
//	}
//
//	//std::string str = "../pic/" + std::to_string(index++) + ".jpg";
//	//cv::imwrite(str, resultImage);
//	return resultImage;
//}