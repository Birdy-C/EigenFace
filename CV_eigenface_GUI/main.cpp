#include "CV_eigenface.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	CV_eigenface w;
	w.show();
	return a.exec();
}
