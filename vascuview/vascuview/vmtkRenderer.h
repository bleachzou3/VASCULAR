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
*@author 邹王忠
此类对应着vmtk-master下的vmtkrenderer.py文件
*/
class vmtkRenderer:public vtkObject
{
protected:
	/*
	*@author bleach
	*这里在构造函数里为什么传入vtkRenderWindow，因为这里vtkRenderWindow不能直接自身构造出来，这里是与QT与结合开发的，需要从QVTKWidget获取vtkRenderWindow;
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

};

#endif