#include "vascuview.h"
#include <vtkSmartPointer.h>
#include <qfiledialog.h>
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
	connect( ui.actionOpenImaFile, SIGNAL( triggered() ), this, SLOT( openImaFileDirectory( ) ));
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
}