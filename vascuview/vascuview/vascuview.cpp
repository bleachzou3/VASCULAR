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
vascuview::vascuview(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//下面两行代码为了测试用的
	m_pImageViewer = vtkSmartPointer<vtkImageViewer2>::New();
	m_pRenderder      = vtkSmartPointer< vtkRenderer >::New();

	render = vtkSmartPointer<vmtkRenderer>::New();
	
	viewer = vtkSmartPointer<vmtkImageViewer>::New();
	
	connectActions();
}

vascuview::~vascuview()
{
	
}

void vascuview::connectActions()
{
	connect( ui.actionOpenImaFile, SIGNAL( triggered() ), this, SLOT( openImaFileDirectory() ));
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