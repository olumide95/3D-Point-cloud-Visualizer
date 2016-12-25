#include "mainwindow.h"
#include "build/ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	this->setWindowTitle("3DDAFRICA");
	
}

MainWindow::~MainWindow()
{

    delete ui;

}

//start the Kinect sensor
void MainWindow::on_actionStart_Scanner_triggered()
{
	if (start == false) {

		start = true;
		pointcloud.reset(new PointCloudXYZRGB);

		kinect = new KinectV2Interface();
		int return_val = kinect->openKinect();

		timerId = startTimer(100); //call timerEvemt every 100 msec
		time.start();
	}
    
}


//stop the Kinect sensor
void MainWindow::on_actionStop_Scanner_triggered()
{
    if (start == true) {
        killTimer(timerId);
        cv::destroyWindow("3DDAFRICA - KINECT VIZ");
        delete kinect;
        start = false;
    }
}

//Refrsh the point cloud visualizer every 100msec
void MainWindow::timerEvent(QTimerEvent *event)
{
	cv::namedWindow("3DDAFRICA - KINECT VIZ");
    cv::Mat colorMat = kinect->get_colorframe(0.3);
    cv::imshow("3DDAFRICA - KINECT VIZ", colorMat);

    kinect->get_depthframe();
    kinect->mapping_pointcloud(pointcloud);


}

//View 3D point cloud data
void MainWindow::on_actionOpen_triggered()
{
	QString filter = "PCD File (*.pcd) ;; PLY File (*.ply)";
	QString file_name = QFileDialog::getOpenFileName(this, "Open 3D Point Cloud", "", filter);
	string filename = file_name.toStdString();
}


//Save point cloud data in PCD or PLY format
void MainWindow::on_actionSave_Point_Cloud_As_triggered()
{
	if (!pointcloud) {
			QMessageBox::information(this, "Error", "There is no 3D Point Cloud Data to be Saved");
		}
	else {
		QString filter = "PCD File (*.pcd) ;; PLY File (*.ply)";
		QString file_name = QFileDialog::getSaveFileName(this, "Save 3D Point Cloud", QDir::homePath(), filter);
		string filename = file_name.toStdString();

		QFileInfo fi(file_name);
		QString extension = fi.suffix();

			if (extension == "pcd") {
				pcl::io::savePCDFile(filename, *pointcloud, true);
			}
			if (extension == "ply") {
				pcl::io::savePLYFile(filename, *pointcloud, true);

			}

		}
	

}


void MainWindow::on_actionExit_triggered()
{
	exit(0);
}

