

#include <vtkImageData.h>
#include <string>
#ifndef VMTK_IMAGE_READER_HPP_
#define VMTK_IMAGE_READER_HPP_

class vmtkImageReader
{
public:
	vmtkImageReader();
	~vmtkImageReader();
	vtkImageData* ReadDICOMDirectory(const char* directoryName,int autoOrientImage);



};

#endif