#include "CV_eigenface.h"
#include <QTextStream>


CV_eigenface::CV_eigenface(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect_signal();
	Load();
}

void CV_eigenface::connect_signal()
{
	connect(ui.pushButton, SIGNAL(clicked()), this, SLOT(MatStore()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(MatRead()));
	connect(ui.pushButton_3, SIGNAL(clicked()), this, SLOT(Load()));
	connect(ui.pushButton_4, SIGNAL(clicked()), this, SLOT(retrive()));
	connect(ui.pushButton_5, SIGNAL(clicked()), this, SLOT(testRetrival()));
	connect(ui.pushButton_6, SIGNAL(clicked()), this, SLOT(reconstruct()));

}

void CV_eigenface::MatStore()
{
	FileStorage fs("eigenfaceSpace.xml", FileStorage::WRITE);
	fs << "eigenfaceSpace" << eigenfaceSpace;
	fs.release();
}

void CV_eigenface::MatRead()
{
	FileStorage fs("eigenfaceSpace.xml", FileStorage::READ);
	fs["eignfaceSpace"] >> eigenfaceSpace;
}

/*
计算相似度 只能是N*1
*/
float CV_eigenface::difference(Mat& mat1, Mat& mat2, int m)
{
	Mat temp = mat1 - mat2;
	float number = 0;
	for (int i = 0; i < m; i++)
	{
		number += temp.at<float>(i)*temp.at<float>(i);
	}
	//qDebug() << number;
	return number;
}
/*
图像预处理
*/
void CV_eigenface::prehandle(Mat& src)
{
	cvtColor(src, src, COLOR_BGR2GRAY);
	equalizeHist(src, src);
	cv::resize(src, src, Size(size_cal, size_cal), 0, 0, INTER_LINEAR);
	src.convertTo(src, CV_32FC1);
}

void CV_eigenface::reconstruct()
{
		QFileDialog w;
		//设置选择框
		w.setAcceptMode(QFileDialog::AcceptOpen);   //AcceptOpen打开,AcceptSave保存文件
		w.setFileMode(QFileDialog::ExistingFiles);
		w.setOption(QFileDialog::ReadOnly, true);
		w.setWindowTitle(QString("choose.."));
		w.setDirectory(QString("./"));
		w.setNameFilter(QString("*.jpg *.png *pgm"));

		if (w.exec())
		{
			String file_path = w.selectedFiles().at(0).toStdString();
			Mat src = imread(file_path);
			// Check if image is loaded fine
			if (src.empty()) {
				qDebug() << " Error opening image" ;
				return;
			}
			//inital
			prehandle(src);
			Mat show = src;
			normalize(show, show, 255, 0, cv::NORM_MINMAX);
			show.convertTo(show, CV_8UC1);
			//imshow("img", show);
			//waitKey(0);
			imshow("reconstruct::pic", show);
			src.convertTo(src, CV_32FC1);
			src -= meanImg;//subtract the mean
			src = src.reshape(1, 1);
			myreconstruct(src);
		}

}


void CV_eigenface::retrive()
{
	QFileDialog w;
	//设置选择框
	w.setAcceptMode(QFileDialog::AcceptOpen);   //AcceptOpen打开,AcceptSave保存文件
	w.setFileMode(QFileDialog::ExistingFiles);
	w.setOption(QFileDialog::ReadOnly, true);
	w.setWindowTitle(QString("choose.."));
	w.setDirectory(QString("./"));
	w.setNameFilter(QString("*.jpg *.png *pgm"));

	if (w.exec())
	{
		String file_path = w.selectedFiles().at(0).toStdString();
		Mat src = imread(file_path);
		// Check if image is loaded fine
		if (src.empty()) {
			qDebug() << " Error opening image" ;
			return;
		}
		//inital
		prehandle(src);
		Mat show = src;
		normalize(show, show, 255, 0, cv::NORM_MINMAX);
		show.convertTo(show, CV_8UC1);

		imshow("retrive::pic", show);
		src.convertTo(src, CV_32FC1);
		src -= meanImg;//subtract the mean
		src = src.reshape(1, 1);
		myRetrival(src);
	}

}

/*
pic : 重构的大图
m: 返回几个特征根重构的结果 如果m无意义返回全部
meanImg:均值人脸
*/
Mat CV_eigenface::myreconstruct(Mat pic)//pic 1*N^2
{



	Mat eigenfaceSpaceT;
	transpose(eigenfaceSpace, eigenfaceSpaceT);//转置

	Mat handle;
	handle = pic.reshape(1, size_cal*size_cal);//N^2 * 1
	handle.convertTo(handle, CV_32FC1);
	handle = eigenfaceSpaceT * handle;

	Mat result, temp, reconstruct, showtemp, re_face;
	result = handle;
	//temp = handle;

	for (int i = 0; i < size_file; i++)
	{
		temp = handle.clone();
		float* p;
		p = temp.ptr<float>(0);
		for (int j = i + 1; j < size_file; j++)
		{
			p[j] = 0;
		}

		if (i == 0)
		{
			reconstruct = eigenfaceSpace * temp;
		}
		else
		{
			reconstruct = eigenfaceSpace * temp;
		}


		//qDebug() << reconstruct;
		showtemp = reconstruct.reshape(1, size_cal);
		showtemp = showtemp + meanImg;

		//qDebug() << show;
		normalize(showtemp, showtemp, 255, 0, cv::NORM_MINMAX);
		showtemp.convertTo(showtemp, CV_8UC1);
		if (i == 0)
		{
			re_face = showtemp;
		}
		else
		{
			if (i % 10 == 0)
				hconcat(re_face, showtemp, re_face);//复制
		}
		//imshow("reconstruct", showtemp);
		//qDebug() << show;
		//waitKey(0);
	}
	imshow("reconstruct", re_face);
	//qDebug() << "end";
	waitKey(0);
	return result;
}



/*
计算特征空间
*/
void CV_eigenface::calculateEigen(const Mat& covMat, Mat &eigenfaceSpace)
{
	Mat covMatT;//N^2 * m
	transpose(covMat, covMatT);//转置
	covMatT.convertTo(covMatT, CV_32FC1);
	covMat.convertTo(covMat, CV_32FC1);
	Mat covMatResult = (covMat * covMatT);//

	Mat eigenvalues, eigenvectors;
	eigen(covMatResult, eigenvalues, eigenvectors);//subsequent matrix rows
												   //===================求特征人脸空间==================

	Mat eigenvectorsT, show;//N^2 *m
	Mat eigenfaceSpaceT, temp, tmp2, tempT;
	transpose(eigenvectors, eigenvectorsT);//转置

	Mat pre_eigen_10;   //显示前十张特征人脸



						//求特征人脸
	for (int i = 0; i < size_file; i++)
	{

		temp = covMatT * eigenvectorsT.col(i);
		temp.convertTo(temp, CV_32FC1);
		transpose(temp, tempT);
		tmp2 = tempT * temp;
		covMat.convertTo(covMat, CV_32FC1);
		float number = tmp2.at<float>(0);

		number = sqrt(number);
		temp = temp / number;

		//eigenfaces.push_back(temp);//单位特征向量.特征人脸
		if (0 == i)
		{
			eigenfaceSpace = temp;
		}
		else
		{
			hconcat(eigenfaceSpace, temp, eigenfaceSpace);//复制
		}

		transpose(temp, tempT);

		//显示
		temp = temp.reshape(1, size_cal);
		normalize(temp, show, 255, 0, cv::NORM_MINMAX);
		show.convertTo(show, CV_8UC1);
		equalizeHist(show, show);
		if (0 == i)
		{
			pre_eigen_10 = show;
		}
		else if (0 == i % 10)
		{
			hconcat(pre_eigen_10, show, pre_eigen_10);
		}
		//imshow("eigenfacetemp", show);
		//waitKey(0);
	}

	imshow("eigenface", pre_eigen_10);
}


void CV_eigenface::Load()
{

	ifstream fin("faces/index.txt");
	string s;
	meanImg = Mat::zeros(size_cal, size_cal, CV_32FC1);
	Mat temp;
	//===================读取并求均值==================
	while (getline(fin, s))
	{
		//qDebug() << "filename: " << s << endl;
		Mat src = imread("faces/out/" + s);
		// Check if image is loaded fine
		if (src.empty()) {
			qDebug() << " Error opening image";// << s;
			return ;
		}
		//inital
		prehandle(src);
		meanImg += src;
		images.push_back(src);
		getline(fin, s); //数据的原因所以去掉一行
	}
	size_file = images.size() - 30;
	meanImg = meanImg / size_file;
	Mat mean_show;
	meanImg.convertTo(mean_show, CV_8UC1);
	imshow("mean image", mean_show);
	//waitKey(0);

	//===================计算协方差==================

	for (int i = 0; i < size_file; i++)
	{
		temp = images.at(i);
		temp.convertTo(temp, CV_32FC1);
		temp -= meanImg;//subtract the mean
		temp = temp.reshape(1, 1);

		if (0 == i)
			covMat = temp;
		else
			vconcat(covMat, temp, covMat);//复制
	}
	covMat /= size_file;

	//==================求特征人脸空间===========
	

	calculateEigen(covMat, eigenfaceSpace);

	//===================重构==================

	Mat pic;
	//pic = images.at(size_file + 6);



	return ;
}


void CV_eigenface::testRetrival()
{
	float mindistance = 0;
	int indexrecord = 0;
	int tempdistance;
	Mat eigenfaceSpaceT;
	transpose(eigenfaceSpace, eigenfaceSpaceT);//转置
	Mat pic;
	vector<int> accurate_pic;
	int accurate[30] = { 0 };
	for (int index = 0; index < 30; index++)// 取几个人脸
	{
		pic = images.at(size_file + index);
		pic = pic.reshape(1, 1);//N^2 * 1

		for (int i = 0; i < size_file; i++)
		{
			Mat mat1 = eigenfaceSpaceT * pic.t();
			Mat mat2 = eigenfaceSpaceT * covMat.row(i).t();
			//qDebug() << mat1 - mat2;
			//Mat mat1 = pic.t();
			//Mat mat2 = covMat.row(i).t();
			tempdistance = difference(mat1, mat2, 60);//pic 1*N^2
			if (0 == i)
			{
				indexrecord = i;
				mindistance = tempdistance;
			}
			if (tempdistance < mindistance)
			{
				indexrecord = i;
				mindistance = tempdistance;
			}
		}
		qDebug() << index << " ";
		qDebug() << indexrecord << endl;
		accurate[index] = indexrecord;
		accurate_pic.push_back(indexrecord);
	}

	qDebug() << accurate_pic.size();
	qDebug() << endl << endl;

	qDebug() << "====== accuracy ==========" << endl;
	for (int m = 0; m < size_file; m = m + 1)// 取几个人脸
	{
		int number = 0;
		for (int index = 0; index < 30; index++)// 取几个人脸
		{
			pic = images.at(size_file + index);
			pic = pic.reshape(1, 1);//N^2 * 1

			for (int i = 0; i < size_file; i++)
			{
				//Mat mat1 = eigenfaceSpaceT*pic.t();
				//Mat mat2 = eigenfaceSpaceT*covMat.row(i).t();
				Mat mat1 = eigenfaceSpaceT * pic.t();
				Mat mat2 = eigenfaceSpaceT*covMat.row(i).t();
				//qDebug() << mat1 - mat2;
				tempdistance = difference(mat1, mat2, m);//pic 1*N^2
				if (0 == i)
				{
					indexrecord = i;
					mindistance = tempdistance;
				}
				if (tempdistance < mindistance)
				{
					indexrecord = i;
					mindistance = tempdistance;
				}
			}
			//qDebug() << index << " ";
			//qDebug() << indexrecord << endl;
			//accurate_pic.push_back(indexrecord);
			if (accurate[index] == indexrecord)
			{
				number++;
			}
		}
		qDebug() << m << " ";
		qDebug() << number << endl;
	}
}



void CV_eigenface::myRetrival(Mat pic)
{
	float mindistance = 0;
	int indexrecord = 0;
	int tempdistance;
	Mat eigenfaceSpaceT;
	transpose(eigenfaceSpace, eigenfaceSpaceT);//转置
	pic = pic.reshape(1, 1);//N^2 * 1

	for (int i = 0; i < size_file; i++)
	{
		Mat mat1 = eigenfaceSpaceT * pic.t();
		Mat mat2 = eigenfaceSpaceT * covMat.row(i).t();
		//qDebug() << mat1 - mat2;
		//Mat mat1 = pic.t();
		//Mat mat2 = covMat.row(i).t();
		tempdistance = difference(mat1, mat2, 60);//pic 1*N^2
		if (0 == i)
		{
			indexrecord = i;
			mindistance = tempdistance;
		}
		if (tempdistance < mindistance)
		{
			indexrecord = i;
			mindistance = tempdistance;
		}
	}
	Mat show = images.at(indexrecord);
	normalize(show, show, 255, 0, cv::NORM_MINMAX);
	show.convertTo(show, CV_8UC1);
	imshow("most relevant", show);
	//waitKey(0);
	//imshow("retrive::result", show);

	
}
