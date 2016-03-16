#ifndef VASCUVIEW_H
#define VASCUVIEW_H

#include <QtWidgets/QMainWindow>
#include "ui_vascuview.h"
#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageViewer2.h>
#include <vmtkRenderer.h>
#include <vmtkImageViewer.h>
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
	//响应打开ima序列的槽函数
	void  openImaFileDirectory();
	
	//测试读入图片
	void test();


	//测试能不能在QVTKWidget里面显示vtk一般的widget
	void testWidget();

	//测试一下vtkvmtkImagePlaneWidget简单版本，就是不是以面向对象的方式组织而是以直接读取的方式
	void testSimplePlaget();

	//测试单个vtkImagePlane是否显示
	void testSingleVtkImagePlane();
private:
	vtkSmartPointer<vtkImageData> data;
	vtkSmartPointer<vmtkRenderer> render;	
	vtkSmartPointer<vmtkImageViewer> viewer;







	//下面两个变量但是为了测试读入图片用的
	//----------------------------------------------
	vtkSmartPointer<vtkImageViewer2> m_pImageViewer;
	vtkSmartPointer< vtkRenderer > m_pRenderder;
	//----------------------------------------------




















	//下面的变量测试testWidget
	//----------------------------------------------

	vtkSmartPointer<vtkRenderer> renderer_testWidget;
	//----------------------------------------------


	//下面的变量测试testSimpleWidget();
	//------------------------------------------------------
	vtkSmartPointer<vtkRenderer> renderer_testSimpleWidget;
	//----------------------------------------------------


	//下面的变量测试单个testSingleVtkImagePlane

	vtkSmartPointer<vtkRenderer> renderer_testVtkImagePlane;

};


#endif // VASCUVIEW_H
