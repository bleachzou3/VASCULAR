


#include <string>

#include <vtkSmartPointer.h>
#include <vtkSetGet.h>
#include <vtkObject.h>
#include <vtkImageData.h>
#ifndef VMTK_IMAGE_READER_HPP_
#define VMTK_IMAGE_READER_HPP_


class vmtkImageReader:public vtkObject
{
protected:
	vmtkImageReader();

	~vmtkImageReader();
public:
	vtkTypeMacro(vmtkImageReader,vtkObject);

	static vmtkImageReader* New();
	
	vtkSmartPointer<vtkImageData> ReadDICOMDirectory(const char* directoryName,int autoOrientImage);



};

#endif