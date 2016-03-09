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

	vtkSmartPointer<vtkvmtkImagePlaneWidget> PlaneWidgetX;
	vtkSmartPointer<vtkvmtkImagePlaneWidget> PlaneWidgetY;
	vtkSmartPointer<vtkvmtkImagePlaneWidget> PlaneWidgetZ;
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

	int* wholeExtent;

	int Display;

	int OwnRenderer;
	
};

#endif