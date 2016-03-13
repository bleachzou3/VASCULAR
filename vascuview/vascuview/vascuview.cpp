#include "vascuview.h"
#include <vtkSmartPointer.h>
#include <qfiledialog.h>
#include <vtkSmartPointer.h>
#include <vmtkImageReader.h>
#include <vmtkRenderer.h>
#include <vmtkImageViewer.h>
#include <vtkImageViewer2.h>
#include <vtkJPEGReader.h>
vascuview::vascuview(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connectActions();
}

vascuview::~vascuview()
{
	
}

void vascuview::connectActions()
{
	connect( ui.actionOpenImaFile, SIGNAL( triggered() ), this, SLOT( test() ));
}
void vascuview::renderImageData()
{
	vtkSmartPointer<vmtkRenderer> render = vtkSmartPointer<vmtkRenderer>::New();
	
	vtkSmartPointer<vmtkImageViewer> viewer = vtkSmartPointer<vmtkImageViewer>::New();

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

//Ҫɾ��
void vascuview::test()
{
	vtkSmartPointer<vtkImageViewer2> m_pImageViewer;
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
	vtkSmartPointer< vtkRenderer > m_pRenderder      = vtkSmartPointer< vtkRenderer >::New();
	ui.qvtkWidget_master->GetRenderWindow()->AddRenderer(m_pRenderder);
	// ��reader�������Ϊm_pImageViewer�����룬������m_pImageViewer����Ⱦ��m_pRenderer�Ĺ���
	reader->Update();

	m_pImageViewer->SetInputData(reader->GetOutput());
	m_pImageViewer->UpdateDisplayExtent();
	m_pImageViewer->SetRenderWindow(ui.qvtkWidget_master->GetRenderWindow());
	m_pImageViewer->SetRenderer(m_pRenderder);
	m_pImageViewer->SetupInteractor(ui.qvtkWidget_master->GetInteractor());
	m_pImageViewer->SetSliceOrientationToXY(); //Ĭ�Ͼ�����������
	//m_pImageViewer->GetImageActor()->InterpolateOff();
}