#ifndef _VMTK_IMAGE_VIEWER_HPP_
#define _VMTK_IMAGE_VIEWER_HPP_
#include <vtkObjectBase.h>
#include <vtkSmartPointer.h>
#include "vmtkRenderer.h"
class vmtkImageViewer : public vtkObjectBase
{
public:
	vmtkImageViewer(vtkSmartPointer<vmtkRenderer> vmtren);
	~vmtkImageViewer();
	void BuildView();

};

#endif