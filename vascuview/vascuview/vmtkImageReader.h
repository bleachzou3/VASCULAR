

#include <vtkImageData.h>
#include <string>
#include <vtkObjectBase.h>
#include <vtkSmartPointer.h>
#ifndef VMTK_IMAGE_READER_HPP_
#define VMTK_IMAGE_READER_HPP_

class vmtkImageReader:public vtkObjectBase
{
public:
	vmtkImageReader();

	~vmtkImageReader();

	vtkSmartPointer<vtkImageData> ReadDICOMDirectory(const char* directoryName,int autoOrientImage);



};

#endif