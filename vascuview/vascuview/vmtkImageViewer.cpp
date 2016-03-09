#include "vmtkImageViewer.h"
#include <vtkSmartPointer.h>
#include "vmtkRenderer.h"
#include <vtkObjectFactory.h>
#include <vtkPointData.h>

vtkStandardNewMacro(vmtkImageViewer);

vmtkImageViewer::vmtkImageViewer()
{

}

vmtkImageViewer::~vmtkImageViewer()
{
	
}

void vmtkImageViewer::BuildView()
{

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
    wholeExtent = Image->GetExtent();
	
	
}

void vmtkImageViewer::setImage(vtkSmartPointer<vtkImageData> ima)
{
	Image = ima;
	Image->GetExtent();
	
}

void vmtkImageViewer::initWidget()
{
	TextureInterpolation = 1;
	ContinuousCursor = 0;
	Display = 1;
	OwnRenderer = 0;

	Picker = vtkSmartPointer<vtkCellPicker>::New();
	PlaneWidgetX = vtkSmartPointer<vtkvmtkImagePlaneWidget>::New();
	PlaneWidgetY = vtkSmartPointer<vtkvmtkImagePlaneWidget>::New();
	PlaneWidgetZ = vtkSmartPointer<vtkvmtkImagePlaneWidget>::New();

	Picker->SetTolerance(0.005);

	initPlaneWidgetX();
	initPlaneWidgetY();
	initPlaneWidgetZ();

	
		

	

}

void vmtkImageViewer::initPlaneWidgetX()
{

	    PlaneWidgetX->SetResliceInterpolateToLinear();		
		PlaneWidgetX->SetTextureInterpolate(TextureInterpolation);
		PlaneWidgetX->SetUseContinuousCursor(ContinuousCursor);
		PlaneWidgetX->SetInputData(Image);

		PlaneWidgetX->SetSliceIndex(wholeExtent[0]);

		PlaneWidgetX->SetPlaneOrientationToXAxes();
		
		//可选的
		PlaneWidgetX->DisplayTextOff();

		PlaneWidgetX->SetPicker(Picker);

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
        PlaneWidgetZ->SetPlaneOrientationToZAxes();
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