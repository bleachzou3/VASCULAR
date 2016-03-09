#ifndef _VMTK_RENDERER_HPP_
#define _VMTK_RENDERER_HPP_
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkvmtkInteractorStyleTrackballCamera.h>
#include <vtkTextActor.h>
#include <vtkObject.h>
#include <vtkSetGet.h>
/*
*@author ������
�����Ӧ��vmtk-master�µ�vmtkrenderer.py�ļ�
*/
class vmtkRenderer:public vtkObject
{
protected:
	/*
	*@author bleach
	*�����ڹ��캯����Ϊʲô����vtkRenderWindow����Ϊ����vtkRenderWindow����ֱ���������������������QT���Ͽ����ģ���Ҫ��QVTKWidget��ȡvtkRenderWindow;
	*/
	vmtkRenderer();
	
	~vmtkRenderer();

private:
	vtkSmartPointer<vtkRenderer> Renderer;
	vtkSmartPointer<vtkRenderWindow> RenderWindow;
	vtkSmartPointer<vtkRenderWindowInteractor> RenderWindowInteractor;
	vtkSmartPointer<vtkvmtkInteractorStyleTrackballCamera> interactorCamera;
	vtkSmartPointer<vtkTextActor> TextActor;
	vtkSmartPointer<vtkTextActor> TextInputActor;

public:
	vtkTypeMacro(vmtkRenderer,vtkObject);
	static vmtkRenderer* New();
	void Initialize(vtkSmartPointer<vtkRenderWindow> ren);

	vtkSmartPointer<vtkRenderWindowInteractor>  getRenderWindowInteractor();

	void Render(int interactive = 1);

	void Deallocate();

};

#endif