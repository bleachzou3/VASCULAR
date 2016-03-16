#include "vmtkImageViewer.h"
#include <vtkSmartPointer.h>
#include "vmtkRenderer.h"
#include <vtkObjectFactory.h>
#include <vtkPointData.h>
#include <vtkImageSlice.h>
#include <vtkSmartPointer.h>
#include <vtkImagePlaneWidget.h>

#include <vtkvmtkImagePlaneWidget.h>
vtkStandardNewMacro(vmtkImageViewer);

vmtkImageViewer::vmtkImageViewer()
{

}

vmtkImageViewer::~vmtkImageViewer()
{
	
}

void vmtkImageViewer::BuildView()
{
	TextureInterpolation = 1;
	ContinuousCursor = 0;
	Display = 1;
	OwnRenderer = 0;

	Picker = vtkSmartPointer<vtkCellPicker>::New();
	PlaneWidgetX = vtkSmartPointer<vtkImagePlaneWidget>::New();
	PlaneWidgetY = vtkSmartPointer<vtkImagePlaneWidget>::New();
	PlaneWidgetZ = vtkSmartPointer<vtkImagePlaneWidget>::New();

	Picker->SetTolerance(0.005);
	initWidget();
	Render->Render();
}

void vmtkImageViewer::setRender(vtkSmartPointer<vmtkRenderer> ren,vtkSmartPointer<vtkRenderWindow> renw)
{
	Render = ren;

	Render->Initialize(renw);
	/*
	vtkSmartPointer<vtkPointData> pa =
	Image->GetPointData();
	pa->SetActiveScalars();
	*/
	Image->GetExtent(wholeExtent);

	Image->GetDimensions(dimension);
	
	
	
}

void vmtkImageViewer::setImage(vtkSmartPointer<vtkImageData> ima)
{
	Image = ima;
	//Image->GetExtent();
	
}

void vmtkImageViewer::initWidget()
{


	initPlaneWidgetX();
	//initPlaneWidgetY();
	//initPlaneWidgetZ();

	
		

	

}

void vmtkImageViewer::initPlaneWidgetX()
{

	    PlaneWidgetX->SetResliceInterpolateToLinear();		
		PlaneWidgetX->SetTextureInterpolate(TextureInterpolation);
		PlaneWidgetX->SetUseContinuousCursor(ContinuousCursor);		
		PlaneWidgetX->SetInputData(Image);		
		PlaneWidgetX->SetPlaneOrientationToXAxes();
		PlaneWidgetX->SetSliceIndex(wholeExtent[0]);	
		//可选的
		PlaneWidgetX->DisplayTextOff();
		PlaneWidgetX->SetPicker(Picker);
		//PlaneWidgetX->SetKeyPressActivationValue('x');
		PlaneWidgetX->KeyPressActivationOff();
		PlaneWidgetX->SetInteractor(Render->getRenderWindowInteractor());		
		//可选的
		PlaneWidgetX->SetMarginSizeX(0.0);
		PlaneWidgetX->SetMarginSizeY(0.0);		
		PlaneWidgetX->On();
        

}

void vmtkImageViewer::initPlaneWidgetY()
{
	    PlaneWidgetY->SetResliceInterpolateToLinear();
        PlaneWidgetY->SetTextureInterpolate(TextureInterpolation);
        PlaneWidgetY->SetUseContinuousCursor(ContinuousCursor);
        PlaneWidgetY->SetInputData(Image);
        PlaneWidgetY->SetPlaneOrientationToYAxes();
        PlaneWidgetY->SetSliceIndex(wholeExtent[2]);

        PlaneWidgetY->DisplayTextOff();
        PlaneWidgetY->SetPicker(Picker);
        PlaneWidgetY->KeyPressActivationOff();
        PlaneWidgetY->SetLookupTable(PlaneWidgetX->GetLookupTable());
		PlaneWidgetY->SetInteractor(Render->getRenderWindowInteractor());
        PlaneWidgetY->SetMarginSizeX(0.0);
        PlaneWidgetY->SetMarginSizeY(0.0);
  
       PlaneWidgetY->On();
}


void vmtkImageViewer::initPlaneWidgetZ()
{

	    PlaneWidgetZ->SetResliceInterpolateToLinear();
        PlaneWidgetZ->SetTextureInterpolate(TextureInterpolation);
        PlaneWidgetZ->SetUseContinuousCursor(ContinuousCursor);
        PlaneWidgetZ->SetInputData(Image);
        PlaneWidgetZ->SetPlaneOrientationToYAxes();
        PlaneWidgetZ->SetSliceIndex(wholeExtent[4]);

        PlaneWidgetZ->DisplayTextOff();
        PlaneWidgetZ->SetPicker(Picker);
        PlaneWidgetZ->KeyPressActivationOff();
        PlaneWidgetZ->SetLookupTable(PlaneWidgetX->GetLookupTable());
		PlaneWidgetZ->SetInteractor(Render->getRenderWindowInteractor());
        PlaneWidgetZ->SetMarginSizeX(0.0);
        PlaneWidgetZ->SetMarginSizeY(0.0);
  
       PlaneWidgetZ->On();
}