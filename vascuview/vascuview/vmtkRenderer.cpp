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

	//能改变颜色
	//Renderer->SetBackground();

	RenderWindow->AddRenderer(Renderer);

	//RenderWindow->SetSize();

	//RenderWindow->SetPointSmoothing();

	//RenderWindow->SetLineSmoothing();
	
	//RenderWindow->SetPolygonSmoothing();

	RenderWindowInteractor->SetInteractorStyle(interactorCamera);


}

vtkSmartPointer<vtkRenderWindowInteractor>  vmtkRenderer::getRenderWindowInteractor()
{
	return RenderWindowInteractor;
}

void  vmtkRenderer::Render(int interactive)
{
	if( interactive)
	{
		RenderWindowInteractor->Initialize();
	}

	RenderWindow->Render();

	if(interactive)
		RenderWindowInteractor->Start();
}

void vmtkRenderer::Deallocate()
{
	RenderWindowInteractor->Delete();
	RenderWindow->Delete();
	RenderWindow->Delete();
}