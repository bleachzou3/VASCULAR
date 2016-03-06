#ifndef _VMTK_RENDERER_HPP_
#define _VMTK_RENDERER_HPP_
#include <vtkSmartPointer.h>
#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkvmtkInteractorStyleTrackballCamera.h>
#include <vtkTextActor.h>
/*
*@author ������
�����Ӧ��vmtk-master�µ�vmtkrenderer.py�ļ�
*/
class vmtkRenderer:public vtkObjectBase
{
public:
	/*
	*@author bleach
	*�����ڹ��캯����Ϊʲô����vtkRenderWindow����Ϊ����vtkRenderWindow����ֱ���������������������QT���Ͽ����ģ���Ҫ��QVTKWidget��ȡvtkRenderWindow;
	*/
	vmtkRenderer(vtkSmartPointer<vtkRenderWindow> renw);
	
	~vmtkRenderer();
	void Initialize();
private:
	vtkSmartPointer<vtkRenderer> Renderer;
	vtkSmartPointer<vtkRenderWindow> RenderWindow;
	vtkSmartPointer<vtkRenderWindowInteractor> RenderWindowInteractor;
	vtkSmartPointer<vtkvmtkInteractorStyleTrackballCamera> interactorCamera;
	vtkSmartPointer<vtkTextActor> TextActor;
	vtkSmartPointer<vtkTextActor> TextInputActor;

};

#endif