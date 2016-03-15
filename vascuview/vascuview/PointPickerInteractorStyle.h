#ifndef POINT_PICKER_INTERACTOR_STYLE_HPP_
#define POINT_PICKER_INTERACTOR_STYLE_HPP_
#include <iostream>
#include <vtkSetGet.h>

#include <vtkSmartPointer.h>
#include <vtkRendererCollection.h>
#include <vtkPointPicker.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkObjectFactory.h>
#include <vtkProperty.h>
#include <vtkAutoInit.h>
#include <vtkImagePlaneWidget.h>
#include <vtkvmtkDICOMImageReader.h>
#include <vtkImageData.h>

// PointPickerInteractorStyle
class PointPickerInteractorStyle : public vtkInteractorStyleTrackballCamera
{
public:
	static PointPickerInteractorStyle* New();
	vtkTypeMacro(PointPickerInteractorStyle, vtkInteractorStyleTrackballCamera);

	virtual void OnLeftButtonDown() 
	{
		std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0] << " " << this->Interactor->GetEventPosition()[1] << std::endl;
		this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0], 
			this->Interactor->GetEventPosition()[1], 
			0,  // always zero.
			this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer());
		double picked[3];
		this->Interactor->GetPicker()->GetPickPosition(picked);
		std::cout << "Picked value: " << picked[0] << " " << picked[1] << " " << picked[2] << std::endl;

		vtkSmartPointer<vtkSphereSource> sphereSource = 
			vtkSmartPointer<vtkSphereSource>::New();
		sphereSource->Update();

		vtkSmartPointer<vtkPolyDataMapper> mapper = 
			vtkSmartPointer<vtkPolyDataMapper>::New();
		mapper->SetInputConnection(sphereSource->GetOutputPort());
		vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
		actor->SetMapper(mapper);
		actor->SetPosition(picked);
		actor->SetScale(0.05);
		actor->GetProperty()->SetColor(1.0, 0.0, 0.0);
		this->Interactor->GetRenderWindow()->GetRenderers()->GetFirstRenderer()->AddActor(actor);

		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	}
};

vtkStandardNewMacro(PointPickerInteractorStyle);

#endif