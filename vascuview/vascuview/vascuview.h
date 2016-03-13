#ifndef VASCUVIEW_H
#define VASCUVIEW_H

#include <QtWidgets/QMainWindow>
#include "ui_vascuview.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
class vascuview : public QMainWindow
{
	Q_OBJECT

public:
	vascuview(QWidget *parent = 0);
	~vascuview();

private:
	Ui::vascuviewClass ui;
private:
	void connectActions();
	void renderImageData();
private slots:
	//��Ӧ��ima���еĲۺ���
	void  openImaFileDirectory();
	void test();
private:
	vtkSmartPointer<vtkImageData> data;
};

#endif // VASCUVIEW_H
