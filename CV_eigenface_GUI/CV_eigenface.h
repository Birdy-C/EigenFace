#pragma once
#include "iostream"
#include "fstream" 
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <QtWidgets/QMainWindow>
#include <QMessageBox>  
#include <QFileDialog>  
#include <QDebug>
#include "ui_CV_eigenface.h"

using namespace std;
using namespace cv;

class CV_eigenface : public QMainWindow
{
	Q_OBJECT

public:
	CV_eigenface(QWidget *parent = Q_NULLPTR);

private:
	Ui::CV_eigenfaceClass ui;
	void connect_signal();
	const int size_cal = 72;
	const char* window_name = "Eigen Face Demo";
	int size_file;
	Mat meanImg;
	Mat covMat;		//Ð­·½²î¾ØÕó
	Mat eigenfaceSpace;


	vector<Mat> images;
	public slots:

	void MatStore();
	void MatRead();
	float difference(Mat & mat1, Mat & mat2, int m);
	void prehandle(Mat & src);
	void reconstruct();
	void retrive();
	Mat myreconstruct(Mat pic);
	void calculateEigen(const Mat & covMat, Mat & eigenfaceSpace);
	void Load();
	void testRetrival();
	void myRetrival(Mat pic);
};
