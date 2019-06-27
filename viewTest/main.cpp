#include "viewTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	viewTest w;
	w.show();
	return a.exec();
}
