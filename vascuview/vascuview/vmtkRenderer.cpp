#include "vmtkRenderer.h"
vmtkRenderer::vmtkRenderer(vtkSmartPointer<vtkRenderWindow>renw)
{
	Renderer = vtkSmartPointer<vtkRenderer>::New();

	RenderWindow = renw;

	RenderWindowInteractor = renw->GetInteractor();
	
	interactorCamera = vtkSmartPointer<vtkvmtkInteractorStyleTrackballCamera>::New();

	
}
vmtkRenderer::~vmtkRenderer()
{
}

void vmtkRenderer::Initialize()
{
	

	//能改变颜色
	//Renderer->SetBackground();

	RenderWindow->AddRenderer(Renderer);

	//RenderWindow->SetSize();

	//RenderWindow->SetPointSmoothing();

	//RenderWindow->SetLineSmoothing();
	
	//RenderWindow->SetPolygonSmoothing();

	RenderWindowInteractor->SetInteractorStyle(interactorCamera);


}