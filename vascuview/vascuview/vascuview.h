#ifndef VASCUVIEW_H
#define VASCUVIEW_H

#include <QtWidgets/QMainWindow>
#include "ui_vascuview.h"

class vascuview : public QMainWindow
{
	Q_OBJECT

public:
	vascuview(QWidget *parent = 0);
	~vascuview();

private:
	Ui::vascuviewClass ui;
private:
	void connectActions();
private slots:
	//��Ӧ��ima���еĲۺ���
	void  openImaFileDirectory();
};

#endif // VASCUVIEW_H
