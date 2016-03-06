#include <vmtkRenderer.h>
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
	

	//�ܸı���ɫ
	//Renderer->SetBackground();

	RenderWindow->AddRenderer(Renderer);

	//RenderWindow->SetSize();

	//RenderWindow->SetPointSmoothing();

	//RenderWindow->SetLineSmoothing();
	
	//RenderWindow->SetPolygonSmoothing();

	RenderWindowInteractor->SetInteractorStyle(interactorCamera);


}