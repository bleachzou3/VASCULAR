#include "vascuview.h"
#include <vtkSmartPointer.h>
#include <qfiledialog.h>
#include <vtkSmartPointer.h>
#include <vmtkImageReader.h>
#include <vmtkRenderer.h>
#include <vmtkImageViewer.h>
#include <vtkImageViewer2.h>
#include <vtkJPEGReader.h>
#include <vtkImageActor.h>
#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkPointPicker.h>
#include <PointPickerInteractorStyle.h>
#include <vtkStreamingDemandDrivenPipeline.h>
#include <vtkInformation.h>
#include <vtkAlgorithm.h>
#include <vtkImageReslice.h>
#include <vtkMetaImageReader.h>
#include <vtkImageFlip.h>
#include <vtkStringArray.h>
vascuview::vascuview(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//下面两行代码为了测试用的
	//------------------------------------------------------------
	m_pImageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	m_pRenderder      = vtkSmartPointer< vtkRenderer >::New();
	//---------------------------------------------------------------



	render = vtkSmartPointer<vmtkRenderer>::New();
	
	viewer = vtkSmartPointer<vmtkImageViewer>::New();


	//下面一行代码测试testWidget
	//-------------------------------------
	renderer_testWidget = vtkSmartPointer<vtkRenderer>::New();
	//------------------------------------------
	
	//下面一行代码测试testSimpleWidget()
	//------------------------------------------------------------
	renderer_testSimpleWidget = vtkSmartPointer<vtkRenderer>::New();
	//-------------------------------------------------------------


	//下面一行代码测试testSingleVtkImagePlane
	//----------------------------------------------------------------
	renderer_testVtkImagePlane = vtkSmartPointer<vtkRenderer>::New();
	//---------------------------------------------------------------------



	 PlaneWidgetX = vtkSmartPointer<vtkImagePlaneWidget>::New();
	 PlaneWidgetY = vtkSmartPointer<vtkImagePlaneWidget>::New();
	 PlaneWidgetZ = vtkSmartPointer<vtkImagePlaneWidget>::New();
	connectActions();
}

vascuview::~vascuview()
{
	
}

void vascuview::connectActions()
{
	connect( ui.actionOpenImaFile, SIGNAL( triggered() ), this, SLOT( SimplePlaget()));
}
void vascuview::renderImageData()
{


	viewer->setImage(data);
	viewer->setRender(render,ui.qvtkWidget_master->GetRenderWindow());
	viewer->BuildView();


}

void vascuview::openImaFileDirectory()
{
    QFileDialog::Options options = QFileDialog::DontResolveSymlinks | QFileDialog::ShowDirsOnly;  
    options |= QFileDialog::DontUseNativeDialog;  
    QString directory = QFileDialog::getExistingDirectory(this,  
                                    tr("Open Directory"),  
                                    "/home",  
                                    options);  
	ui.statusBar->showMessage(directory);
	vtkSmartPointer<vmtkImageReader> reader = vtkSmartPointer<vmtkImageReader>::New();
    data = reader->ReadDICOMDirectory("E:/patientData/TAN_RUMI",0);
	ui.statusBar->showMessage(QString::number(data->GetReferenceCount(),10));

	renderImageData();

	
	
}

//一开始为了测试做的看有没有走通，读取普通图片
void vascuview::test()
{
	
	QString filter;
	filter = "JPEG image file (*.jpg *.jpeg)";

	QDir dir;
	QString fileName = QFileDialog::getOpenFileName( this, QString(tr("打开图像")), dir.absolutePath() , filter );
	if ( fileName.isEmpty() == true ) return;

	// 支持带中文路径的读取
	QByteArray ba = fileName.toLocal8Bit();
	const char *fileName_str = ba.data();

	// 用vtkJPEGReader读取JPG图像
	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName(fileName_str);
	
	ui.qvtkWidget_master->GetRenderWindow()->AddRenderer(m_pRenderder);
	// 将reader的输出作为m_pImageViewer的输入，并设置m_pImageViewer与渲染器m_pRenderer的关联
	reader->Update();

	m_pImageViewer->SetInputData(reader->GetOutput());
	m_pImageViewer->UpdateDisplayExtent();
	m_pImageViewer->SetRenderWindow(ui.qvtkWidget_master->GetRenderWindow());
	m_pImageViewer->SetRenderer(m_pRenderder);
	m_pImageViewer->SetupInteractor(ui.qvtkWidget_master->GetInteractor());
	m_pImageViewer->SetSliceOrientationToXY(); //默认就是这个方向的

	m_pImageViewer->GetImageActor()->InterpolateOff();

	m_pRenderder->ResetCamera();
    m_pRenderder->DrawOn();
	

	ui.qvtkWidget_master->GetRenderWindow()->Render();

}

//测试QVTKWidget里面能不能加入vtk widget
void vascuview::testWidget()
{
	vtkSmartPointer<vtkSphereSource> sphereSource = 
		vtkSmartPointer<vtkSphereSource>::New();
	sphereSource->Update();

	// Create a mapper and actor
	vtkSmartPointer<vtkPolyDataMapper> mapper = 
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputConnection(sphereSource->GetOutputPort());
	vtkSmartPointer<vtkActor> actor = 
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	// Create a renderer, render window, and interactor

	vtkSmartPointer<vtkRenderWindow> renderWindow = 
		ui.qvtkWidget_master->GetRenderWindow();
	renderWindow->Render();
	renderWindow->SetWindowName("PointPicker");
	renderWindow->AddRenderer(renderer_testWidget);

	vtkSmartPointer<vtkPointPicker> pointPicker = 
		vtkSmartPointer<vtkPointPicker>::New();

	vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
		renderWindow->GetInteractor();
	renderWindowInteractor->SetPicker(pointPicker);
	

	vtkSmartPointer<PointPickerInteractorStyle> style = 
		vtkSmartPointer<PointPickerInteractorStyle>::New();
	renderWindowInteractor->SetInteractorStyle( style );

	// Add the actor to the scene
	renderer_testWidget->AddActor(actor);
	renderer_testWidget->SetBackground(1,1,1);

	// Render and interact
	renderWindow->Render();
	renderWindowInteractor->Start();
}


//测试直接以最简单的形式组织
void vascuview::SimplePlaget()
{
	
	vtkSmartPointer<vtkvmtkDICOMImageReader> reader = vtkSmartPointer<vtkvmtkDICOMImageReader>::New();
	//reader->SetFileDimensionality(3);
	//reader->SetDataScalarTypeToUnsignedChar();
	//reader->SetDataByteOrderToBigEndian();
	//reader->SetDebug(true);
	reader->SetAutoOrientImage(1);
	reader->SetDirectoryName("E:/patientData/TAN_RUMI");
	reader->Update();

	//reader->UpdateWholeExtent();
	int Flip[3] = {1,0,1};
	
	/*
	vtkSmartPointer<vtkMetaImageReader> reader =
	vtkSmartPointer<vtkMetaImageReader>::New();
	reader->SetFileName("E:/brain.mhd");
	reader->Update();
	*/
	/*
	vtkSmartPointer<vtkStringArray> fileArray = vtkSmartPointer<vtkStringArray>::New();
	char fileName[500];
	for(int i = 1; i <= 281;i++)
	{
		sprintf(fileName,"E:/ZHANG_XIANGJU/ZHANG_XIANG_JU_BAH_03434948_F_64Y.CT.CARDIAC_N_FLASH_CARDIO_(ADULT).0006.%04d.2013.08.29.19.12.43.140625.170674642.jpg");
		vtkstd::string fileStr(fileName);
		fileArray->InsertNextValue(fileStr);
	}

	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileNames(fileArray);
	*/
//	Image->AllocateScalars(VTK_FLOAT,3);
	Image= reader->GetOutput();
	/*
	int temp = Image->GetNumberOfScalarComponents();
	//Image->SetScalarType();
	//Image->AllocateScalars(VTK_FLOAT,3);
	vtkSmartPointer<vtkImageFlip> flipFilter = vtkSmartPointer<vtkImageFlip>::New(); 
	flipFilter->SetDebug(true);
	    if (Flip[0] == 1 || Flip[1] == 1 || Flip[2] == 1)
		{
            vtkImageData *temp0 = Image;
			int cnt =  temp0->GetReferenceCount();
			vtkImageData* temp1;
            if (Flip[0] == 1)
			{
                //flipFilter = vtk.vtkImageFlip();
				flipFilter->SetInputData(temp0);
                flipFilter->SetFilteredAxis(0);
                flipFilter->Update();
				temp1 = flipFilter->GetOutput();
			}
            //temp1 = temp0
            if (Flip[1] == 1)
			{
				//flipFilter = vtk.vtkImageFlip();
                flipFilter->SetInputData(Image);
                flipFilter->SetFilteredAxis(1);
                flipFilter->Update();
                Image = flipFilter->GetOutput();
			}
            //temp2 = temp1
            if (Flip[2] == 1 )
			{
                //flipFilter = vtk.vtkImageFlip()
				flipFilter->SetInputData(Image);
                flipFilter->SetFilteredAxis(2);
                flipFilter->Update();
				Image = flipFilter->GetOutput();
			}
            //self.Image = temp2
		}
	*/

	

	/*
	vtkSmartPointer<vtkvmtkImagePlaneWidget> PlaneWidgetX = vtkSmartPointer<vtkvmtkImagePlaneWidget>::New();
	vtkSmartPointer<vtkvmtkImagePlaneWidget> PlaneWidgetY = vtkSmartPointer<vtkvmtkImagePlaneWidget>::New();
	vtkSmartPointer<vtkvmtkImagePlaneWidget> PlaneWidgetZ = vtkSmartPointer<vtkvmtkImagePlaneWidget>::New();
	*/

	vtkSmartPointer<vtkCellPicker> Picker = vtkSmartPointer<vtkCellPicker>::New();	
	vtkSmartPointer<vtkvmtkInteractorStyleTrackballCamera> interactorCamera = vtkSmartPointer<vtkvmtkInteractorStyleTrackballCamera>::New();
	ui.qvtkWidget_master->GetRenderWindow()->AddRenderer(renderer_testSimpleWidget);

	int TextureInterpolation = 1;
	int ContinuousCursor = 0;
	int Display = 1;
	int OwnRenderer = 0;
	int wholeExtent[6];
	int dimesion[3];


	Image->GetDimensions(dimesion);
	Image->SetDimensions(dimesion);
	PlaneWidgetX->SetResliceInterpolateToLinear();		
	PlaneWidgetX->SetTextureInterpolate(TextureInterpolation);
	PlaneWidgetX->SetUseContinuousCursor(ContinuousCursor);		
	
	//PlaneWidgetX->SetInputConnection(reader->GetOutputPort());
	PlaneWidgetX->SetInputData(Image);
	
	
	PlaneWidgetX->SetPlaneOrientationToXAxes();
	PlaneWidgetX->SetSliceIndex(wholeExtent[0]);	
	//可选的
	PlaneWidgetX->DisplayTextOff();
	PlaneWidgetX->SetPicker(Picker);
	//PlaneWidgetX->SetKeyPressActivationValue('x');
	PlaneWidgetX->KeyPressActivationOff();
	ui.qvtkWidget_master->GetRenderWindow()->GetInteractor()->SetInteractorStyle(interactorCamera);
	PlaneWidgetX->SetInteractor(ui.qvtkWidget_master->GetRenderWindow()->GetInteractor());		
	PlaneWidgetX->SetMarginSizeX(0.0);
	PlaneWidgetX->SetMarginSizeY(0.0);		
	



	PlaneWidgetY->SetResliceInterpolateToLinear();
    PlaneWidgetY->SetTextureInterpolate(TextureInterpolation);
    PlaneWidgetY->SetUseContinuousCursor(ContinuousCursor);
	//PlaneWidgetY->SetInputConnection(reader->GetOutputPort());
    PlaneWidgetY->SetInputData(Image);
	
    PlaneWidgetY->SetPlaneOrientationToYAxes();
    PlaneWidgetY->SetSliceIndex(wholeExtent[2]);

    PlaneWidgetY->DisplayTextOff();
    PlaneWidgetY->SetPicker(Picker);
    PlaneWidgetY->KeyPressActivationOff();
    PlaneWidgetY->SetLookupTable(PlaneWidgetX->GetLookupTable());

	PlaneWidgetY->SetInteractor(ui.qvtkWidget_master->GetRenderWindow()->GetInteractor());
    PlaneWidgetY->SetMarginSizeX(0.0);
    PlaneWidgetY->SetMarginSizeY(0.0);
  
  


	PlaneWidgetZ->SetResliceInterpolateToLinear();
    PlaneWidgetZ->SetTextureInterpolate(TextureInterpolation);
    PlaneWidgetZ->SetUseContinuousCursor(ContinuousCursor);
	//PlaneWidgetZ->SetInputConnection(reader->GetOutputPort());
    PlaneWidgetZ->SetInputData(Image);

    PlaneWidgetZ->SetPlaneOrientationToZAxes();
    PlaneWidgetZ->SetSliceIndex(wholeExtent[4]);

    PlaneWidgetZ->DisplayTextOff();
    PlaneWidgetZ->SetPicker(Picker);
    PlaneWidgetZ->KeyPressActivationOff();
    PlaneWidgetZ->SetLookupTable(PlaneWidgetX->GetLookupTable());
	PlaneWidgetZ->SetInteractor(ui.qvtkWidget_master->GetRenderWindow()->GetInteractor());
    PlaneWidgetZ->SetMarginSizeX(0.0);
    PlaneWidgetZ->SetMarginSizeY(0.0);
  
       //PlaneWidgetZ->On();

	   


	renderer_testSimpleWidget->SetBackground(255,251,240);
	ui.qvtkWidget_master->GetRenderWindow()->GetInteractor()->Initialize();
	ui.qvtkWidget_master->GetRenderWindow()->Render();

	PlaneWidgetX->On();
	PlaneWidgetY->On();
	PlaneWidgetZ->On();
	PlaneWidgetX->InteractionOn();
	PlaneWidgetY->InteractionOn();
	PlaneWidgetZ->InteractionOn();
	
	 
}


void vascuview::testSingleVtkImagePlane()
{
	ui.qvtkWidget_master->GetRenderWindow()->AddRenderer(renderer_testVtkImagePlane);
	 vtkSmartPointer<vtkImagePlaneWidget> planeWidget = 
    vtkSmartPointer<vtkImagePlaneWidget>::New();
  planeWidget->SetInteractor( ui.qvtkWidget_master->GetRenderWindow()->GetInteractor());
  planeWidget->TextureVisibilityOff();
    ui.qvtkWidget_master->GetRenderWindow()->GetInteractor()->Initialize();
	//ui.qvtkWidget_master->GetRenderWindow()->GetInteractor()->Start();
	ui.qvtkWidget_master->GetRenderWindow()->Render();

  planeWidget->On();
}
