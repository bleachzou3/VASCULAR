#ifndef _VMTK_RENDERER_HPP_
#define _VMTK_RENDERER_HPP_
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkvmtkInteractorStyleTrackballCamera.h>
#include <vtkTextActor.h>
/*
* @author�����Ӧ��vmtk-master�µ�vmtkrenderer.py�ļ�
*/
class vmtkRenderer
{
public:
	vmtkRenderer();
	~vmtkRenderer();
	void Initialize();
private:
	vtkSmartPointer<vtkRenderer> Renderer;
	vtkSmartPointer<vtkRenderWindow> vtkRenderWindow;
	vtkSmartPointer<vtkRenderWindowInteractor> vtkRenderWindowInteractor;
	vtkSmartPointer<vtkvmtkInteractorStyleTrackballCamera> interactorCamera;
	vtkSmartPointer<vtkTextActor> TextInputActor;

};

#endif