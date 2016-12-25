#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "KinectV2Interface.h"
#include <pcl/visualization/pcl_visualizer.h>
#include <QMainWindow>
#include <QTime>
#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>

typedef pcl::PointXYZRGBA PointType;
typedef pcl::PointXYZRGB PointTypeXYZRGB;
typedef pcl::PointCloud<PointTypeXYZRGB> PointCloudXYZRGB;
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;	
	boost::shared_ptr<pcl::visualization::PCLVisualizer> viewer;
	PointCloudXYZRGB::Ptr pointcloud;	
	KinectV2Interface *kinect;	
	QTime time;
	int timerId;
	bool start = false;

	void timerEvent(QTimerEvent *event);

private slots:
    void on_actionStart_Scanner_triggered();
    void on_actionStop_Scanner_triggered();
    void on_actionSave_Point_Cloud_As_triggered();
    void on_actionExit_triggered();
    void on_actionOpen_triggered();
};

#endif // MAINWINDOW_H
