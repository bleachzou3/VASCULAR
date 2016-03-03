
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
	//vtkvmtkDICOMImageReader �Ĺ��췽ʽ���п����ǵ���ģʽ
	vtkvmtkDICOMImageReader* reader = vtkvmtkDICOMImageReader::New();

	reader->SetDirectoryName(directoryName);

	reader->SetAutoOrientImage(autoOrientImage);

	reader->Update();

	vtkImageData* data = reader->GetOutput();
	

	return data;
	
}

