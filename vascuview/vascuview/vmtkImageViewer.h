#ifndef _VMTK_IMAGE_VIEWER_HPP_
#define _VMTK_IMAGE_VIEWER_HPP_
#include <vtkObjectBase.h>
#include <vtkSmartPointer.h>
#include <vtkObject.h>

#include "vmtkRenderer.h"
class vmtkImageViewer : public vtkObject
{
protected:
	vmtkImageViewer();
	~vmtkImageViewer();
public:
	static vmtkImageViewer* New();
	vtkTypeMacro(vmtkImageViewer,vtkObject);
	void BuildView();

};

#endif