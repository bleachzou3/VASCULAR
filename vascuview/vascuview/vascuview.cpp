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
vascuview::vascuview(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//�������д���Ϊ�˲����õ�
	//------------------------------------------------------------
	m_pImageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	m_pRenderder      = vtkSmartPointer< vtkRenderer >::New();
	//---------------------------------------------------------------



	render = vtkSmartPointer<vmtkRenderer>::New();
	
	viewer = vtkSmartPointer<vmtkImageViewer>::New();


	//����һ�д������testWidget
	//-------------------------------------
	renderer_testWidget = vtkSmartPointer<vtkRenderer>::New();
	//------------------------------------------
	
	//����һ�д������testSimpleWidget()
	//------------------------------------------------------------
	renderer_testSimpleWidget = vtkSmartPointer<vtkRenderer>::New();
	//-------------------------------------------------------------


	//����һ�д������testSingleVtkImagePlane
	//----------------------------------------------------------------
	renderer_testVtkImagePlane = vtkSmartPointer<vtkRenderer>::New();
	//---------------------------------------------------------------------
	connectActions();
}

vascuview::~vascuview()
{
	
}

void vascuview::connectActions()
{
	connect( ui.actionOpenImaFile, SIGNAL( triggered() ), this, SLOT( testSimplePlaget()));
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

//һ��ʼΪ�˲������Ŀ���û����ͨ����ȡ��ͨͼƬ
void vascuview::test()
{
	
	QString filter;
	filter = "JPEG image file (*.jpg *.jpeg)";

	QDir dir;
	QString fileName = QFileDialog::getOpenFileName( this, QString(tr("��ͼ��")), dir.absolutePath() , filter );
	if ( fileName.isEmpty() == true ) return;

	// ֧�ִ�����·���Ķ�ȡ
	QByteArray ba = fileName.toLocal8Bit();
	const char *fileName_str = ba.data();

	// ��vtkJPEGReader��ȡJPGͼ��
	vtkSmartPointer<vtkJPEGReader> reader = vtkSmartPointer<vtkJPEGReader>::New();
	reader->SetFileName(fileName_str);
	
	ui.qvtkWidget_master->GetRenderWindow()->AddRenderer(m_pRenderder);
	// ��reader�������Ϊm_pImageViewer�����룬������m_pImageViewer����Ⱦ��m_pRenderer�Ĺ���
	reader->Update();

	m_pImageViewer->SetInputData(reader->GetOutput());
	m_pImageViewer->UpdateDisplayExtent();
	m_pImageViewer->SetRenderWindow(ui.qvtkWidget_master->GetRenderWindow());
	m_pImageViewer->SetRenderer(m_pRenderder);
	m_pImageViewer->SetupInteractor(ui.qvtkWidget_master->GetInteractor());
	m_pImageViewer->SetSliceOrientationToXY(); //Ĭ�Ͼ�����������

	m_pImageViewer->GetImageActor()->InterpolateOff();

	m_pRenderder->ResetCamera();
    m_pRenderder->DrawOn();
	

	ui.qvtkWidget_master->GetRenderWindow()->Render();

}

//����QVTKWidget�����ܲ��ܼ���vtk widget
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


//����ֱ������򵥵���ʽ��֯
void vascuview::testSimplePlaget()
{
	
	vtkSmartPointer<vtkvmtkDICOMImageReader> reader = vtkSmartPointer<vtkvmtkDICOMImageReader>::New();
	reader->SetDirectoryName("E:/patientData/TAN_RUMI");
	reader->Update();
	vtkSmartPointer<vtkImageData> Image = reader->GetOutput();

	vtkSmartPointer<vtkImagePlaneWidget> PlaneWidgetX = vtkSmartPointer<vtkImagePlaneWidget>::New();
	vtkSmartPointer<vtkCellPicker> Picker = vtkSmartPointer<vtkCellPicker>::New();	
	vtkSmartPointer<vtkImagePlaneWidget> PlaneWidgetY = vtkSmartPointer<vtkImagePlaneWidget>::New();
	vtkSmartPointer<vtkImagePlaneWidget> PlaneWidgetZ = vtkSmartPointer<vtkImagePlaneWidget>::New();
	vtkSmartPointer<vtkvmtkInteractorStyleTrackballCamera> interactorCamera = vtkSmartPointer<vtkvmtkInteractorStyleTrackballCamera>::New();
	ui.qvtkWidget_master->GetRenderWindow()->AddRenderer(renderer_testSimpleWidget);

	int TextureInterpolation = 1;
	int ContinuousCursor = 0;
	int Display = 1;
	int OwnRenderer = 0;
	int wholeExtent[6];
	Image->GetExtent(wholeExtent);
	
	//vtkStreamingDemandDrivenPipeline::WHOLE_EXTENT();
	vtkSmartPointer<vtkInformation> inf = vtkSmartPointer<vtkInformation>::New();
	vtkStreamingDemandDrivenPipeline::SetWholeExtent(vtkSmartPointer<vtkInformation>::New(),wholeExtent);

	

	reader->Update();


	PlaneWidgetX->SetResliceInterpolateToLinear();		
	PlaneWidgetX->SetTextureInterpolate(TextureInterpolation);
	PlaneWidgetX->SetUseContinuousCursor(ContinuousCursor);		

	PlaneWidgetX->SetInputData(Image);


	PlaneWidgetX->SetPlaneOrientationToXAxes();
	PlaneWidgetX->SetSliceIndex(wholeExtent[0]);	
	//��ѡ��
	PlaneWidgetX->DisplayTextOff();
	PlaneWidgetX->SetPicker(Picker);
	//PlaneWidgetX->SetKeyPressActivationValue('x');
	PlaneWidgetX->KeyPressActivationOff();


	ui.qvtkWidget_master->GetRenderWindow()->GetInteractor()->SetInteractorStyle(interactorCamera);
	PlaneWidgetX->SetInteractor(ui.qvtkWidget_master->GetRenderWindow()->GetInteractor());		
	//��ѡ��
	PlaneWidgetX->SetMarginSizeX(0.0);
	PlaneWidgetX->SetMarginSizeY(0.0);		
	//PlaneWidgetX->On();



	


	PlaneWidgetY->SetResliceInterpolateToLinear();
    PlaneWidgetY->SetTextureInterpolate(TextureInterpolation);
    PlaneWidgetY->SetUseContinuousCursor(ContinuousCursor);
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
  
   // PlaneWidgetY->On();


		PlaneWidgetZ->SetResliceInterpolateToLinear();
        PlaneWidgetZ->SetTextureInterpolate(TextureInterpolation);
        PlaneWidgetZ->SetUseContinuousCursor(ContinuousCursor);
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

	   

  //double origin[3] = {0, 1,0};
  //planeWidget->SetOrigin(origin);
 //planeWidget->UpdatePlacement();
	   //renderer_testSimpleWidget->SetBackground(255,251,240);
	   ui.qvtkWidget_master->GetRenderWindow()->GetInteractor()->Initialize();
	//ui.qvtkWidget_master->GetRenderWindow()->GetInteractor()->Start();
	ui.qvtkWidget_master->GetRenderWindow()->Render();

	PlaneWidgetX->On();
	PlaneWidgetY->On();
	PlaneWidgetZ->On();
     
	
	 
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
