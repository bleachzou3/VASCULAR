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
	//��Ӧ��ima���еĲۺ���
	void  openImaFileDirectory();
	
	//���Զ���ͼƬ
	void test();


	//�����ܲ�����QVTKWidget������ʾvtkһ���widget
	void testWidget();

	//����һ��vtkvmtkImagePlaneWidget�򵥰汾�����ǲ������������ķ�ʽ��֯������ֱ�Ӷ�ȡ�ķ�ʽ
	void SimplePlaget();

	//���Ե���vtkImagePlane�Ƿ���ʾ
	void testSingleVtkImagePlane();
private:
	vtkSmartPointer<vtkImageData> data;
	vtkSmartPointer<vmtkRenderer> render;	
	vtkSmartPointer<vmtkImageViewer> viewer;







	//����������������Ϊ�˲��Զ���ͼƬ�õ�
	//----------------------------------------------
	vtkSmartPointer<vtkImageViewer2> m_pImageViewer;
	vtkSmartPointer< vtkRenderer > m_pRenderder;
	//----------------------------------------------




















	//����ı�������testWidget
	//----------------------------------------------

	vtkSmartPointer<vtkRenderer> renderer_testWidget;
	//----------------------------------------------


	//����ı�������testSimpleWidget();
	//------------------------------------------------------
	vtkSmartPointer<vtkRenderer> renderer_testSimpleWidget;
	//----------------------------------------------------


	//����ı������Ե���testSingleVtkImagePlane

	vtkSmartPointer<vtkRenderer> renderer_testVtkImagePlane;

};


#endif // VASCUVIEW_H
