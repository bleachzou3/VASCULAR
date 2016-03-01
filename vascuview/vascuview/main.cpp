#include "vascuview.h"
#include <QtWidgets/QApplication>
#include <vtkAutoInit.h>

int main(int argc, char *argv[])
{
	VTK_MODULE_INIT(vtkRenderingOpenGL);
	QApplication a(argc, argv);
	vascuview w;

	w.show();
	return a.exec();
}
