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



};

#endif // VASCUVIEW_H
