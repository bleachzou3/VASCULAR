#include "vmtkRenderer.h"
#include <vtkObjectFactory.h>
vtkStandardNewMacro(vmtkRenderer);
vmtkRenderer::vmtkRenderer()
{


	
}
vmtkRenderer::~vmtkRenderer()
{
}

void vmtkRenderer::Initialize(vtkSmartPointer<vtkRenderWindow> renw)
{
	
	Renderer = vtkSmartPointer<vtkRenderer>::New();

	RenderWindow = renw;

	RenderWindowInteractor = renw->GetInteractor();
	
	interactorCamera = vtkSmartPointer<vtkvmtkInteractorStyleTrackballCamera>::New();

	//�ܸı���ɫ
	//Renderer->SetBackground();

	RenderWindow->AddRenderer(Renderer);

	//RenderWindow->SetSize();

	//RenderWindow->SetPointSmoothing();

	//RenderWindow->SetLineSmoothing();
	
	//RenderWindow->SetPolygonSmoothing();

	RenderWindowInteractor->SetInteractorStyle(interactorCamera);


}