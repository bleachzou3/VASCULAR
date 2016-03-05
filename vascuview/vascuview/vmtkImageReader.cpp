
#include <vmtkImageReader.h>
#include <vtkvmtkDICOMImageReader.h>
#include <vtkSmartPointer.h>

vmtkImageReader::vmtkImageReader()
{

}
vmtkImageReader::~vmtkImageReader()
{

}

vtkSmartPointer<vtkImageData> vmtkImageReader::ReadDICOMDirectory(const char* directoryName,int autoOrientImage)
{

	
	vtkSmartPointer<vtkvmtkDICOMImageReader> reader = vtkSmartPointer<vtkvmtkDICOMImageReader>::New();

	reader->SetDirectoryName(directoryName);

	reader->SetAutoOrientImage(autoOrientImage);

	reader->Update();

	vtkSmartPointer<vtkImageData> data = reader->GetOutput();
	
	
	return data;
	
}

