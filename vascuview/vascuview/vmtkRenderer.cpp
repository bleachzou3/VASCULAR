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
	double *color =new double[3];
	color[0] = 0.0;
	color[1] = 0.1;
	color[2] = 0.3;
	Renderer->SetBackground(color);

	RenderWindowInteractor = renw->GetInteractor();
	
	interactorCamera = vtkSmartPointer<vtkvmtkInteractorStyleTrackballCamera>::New();

	//能改变颜色
	//Renderer->SetBackground();

	RenderWindow->AddRenderer(Renderer);

	//RenderWindow->SetSize();

	//RenderWindow->SetPointSmoothing();

	//RenderWindow->SetLineSmoothing();
	
	//RenderWindow->SetPolygonSmoothing();
	//renw->SetSize(800,600);
	RenderWindowInteractor->SetInteractorStyle(interactorCamera);
	//RenderWindowInteractor->SetRenderWindow(renw);



}

vtkSmartPointer<vtkRenderWindowInteractor>  vmtkRenderer::getRenderWindowInteractor()
{
	return RenderWindowInteractor;
}

void  vmtkRenderer::Render(int interactive)
{
	/*
	if( interactive)
	{
		RenderWindowInteractor->Initialize();
	}
	*/
	/*
	if(interactive)
		RenderWindowInteractor->Start();
	*/
	Renderer->DrawOn();
	Renderer->ResetCamera();
	RenderWindow->Render();
}

void vmtkRenderer::Deallocate()
{
	RenderWindowInteractor->Delete();
	RenderWindow->Delete();
	RenderWindow->Delete();
}