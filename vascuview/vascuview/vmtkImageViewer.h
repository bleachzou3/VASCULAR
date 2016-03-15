#ifndef _VMTK_IMAGE_VIEWER_HPP_
#define _VMTK_IMAGE_VIEWER_HPP_
#include <vtkObjectBase.h>
#include <vtkSmartPointer.h>
#include <vtkObject.h>
#include <vtkImageData.h>
#include "vmtkRenderer.h"
#include <vtkCellPicker.h>
#include <vtkvmtkImagePlaneWidget.h>
class vmtkImageViewer : public vtkObject
{
protected:
	vmtkImageViewer();
	~vmtkImageViewer();
public:
	static vmtkImageViewer* New();
	vtkTypeMacro(vmtkImageViewer,vtkObject);
	void BuildView();
	void setRender(vtkSmartPointer<vmtkRenderer> ren,vtkSmartPointer<vtkRenderWindow> renw);
	void setImage(vtkSmartPointer<vtkImageData> ima);
private:
	vtkSmartPointer<vmtkRenderer> Render;
	vtkSmartPointer<vtkImageData> Image;


	vtkSmartPointer<vtkCellPicker> Picker;

	vtkSmartPointer<vtkImagePlaneWidget> PlaneWidgetX;
	vtkSmartPointer<vtkImagePlaneWidget> PlaneWidgetY;
	vtkSmartPointer<vtkImagePlaneWidget> PlaneWidgetZ;
private:
	/*
	*@author初始化Picker,PlaneWidgetX,PlaneWidgetY,PlaneWidgetZ
	*/
	void initWidget();

	/*
	*设置initPlaneWidgetX一些参数
	*
	*/


	void initPlaneWidgetX();
	void initPlaneWidgetY();
	void initPlaneWidgetZ();

	int TextureInterpolation;

	int ContinuousCursor;

	//图像的维度是根据是他算的
	int wholeExtent[6];


	//图像的维度
    int dimension[3];

	int Display;

	int OwnRenderer;
	
};

#endif