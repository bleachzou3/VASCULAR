
#include <vmtkImageReader.h>
#include <vtkvmtkDICOMImageReader.h>


vmtkImageReader::vmtkImageReader()
{

}
vmtkImageReader::~vmtkImageReader()
{

}

vtkImageData* vmtkImageReader::ReadDICOMDirectory(const char* directoryName,int autoOrientImage)
{
	//vtkvmtkDICOMImageReader 的构造方式很有可能是单例模式
	vtkvmtkDICOMImageReader* reader = vtkvmtkDICOMImageReader::New();

	reader->SetDirectoryName(directoryName);

	reader->SetAutoOrientImage(autoOrientImage);

	reader->Update();

	vtkImageData* data = reader->GetOutput();
	

	return data;
	
}

