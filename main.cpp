/*
@author:Birdy 2017/12/23
*/

#include "iostream"
#include "fstream" 
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
using namespace std;
using namespace cv;

const int size_cal = 72;
const char* window_name = "Eigen Face Demo";
int size_file;

void MatStore(Mat  &eigenfaceSpace)
{
	FileStorage fs("eigenfaceSpace.xml", FileStorage::WRITE);
	fs << "eigenfaceSpace" << eigenfaceSpace;
	fs.release();
}

void MatRead(Mat &eignfaceSpace)
{
	FileStorage fs("eigenfaceSpace.xml", FileStorage::READ);
	fs["eignfaceSpace"] >> eignfaceSpace;
}

/*
计算相似度 只能是N*1
*/
float difference(Mat& mat1, Mat& mat2, int m)
{
	Mat temp = mat1 - mat2;
	float number = 0;
	for (int i = 0; i < m; i++)
	{
 		number += temp.at<float>(i)*temp.at<float>(i);
	}
	//cout << number;
	return number;
}
/*
图像预处理
*/
void prehandle(Mat& src)
{
	cvtColor(src, src, COLOR_BGR2GRAY);
	equalizeHist(src, src);
	resize(src, src, Size(size_cal, size_cal), 0, 0, INTER_LINEAR);
	src.convertTo(src, CV_32FC1);
}

/*
pic : 重构的大图
m: 返回几个特征根重构的结果 如果m无意义返回全部
meanImg:均值人脸
*/
Mat myreconstruct(const Mat& eigenfaceSpace, const Mat& pic,const int m, const Mat& meanImg)//pic 1*N^2
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

		if (m == i)
		{
			result = temp;
		}

		//cout << reconstruct;
		showtemp = reconstruct.reshape(1, size_cal);
		showtemp = showtemp + meanImg;

		//cout << show;
		normalize(showtemp, showtemp, 255, 0, cv::NORM_MINMAX);
		showtemp.convertTo(showtemp, CV_8UC1);
		if (i == 0)
		{
			re_face = showtemp;
		}
		else
		{
			if (i % 10 == 0)
				hconcat(re_face,showtemp, re_face);//复制
		}
		//imshow("reconstruct", showtemp);
		//cout << show;
		//waitKey(0);
	}
	imshow("reconstruct", re_face);
	//cout << "end";
	waitKey(0);
	return result;
}



/*
计算特征空间
*/
void calculateEigen(const Mat& covMat, Mat &eigenfaceSpace)
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


int main(int argc, char** argv)
{
	
	ifstream fin("faces/index.txt");
	string s;
	vector<Mat> images;
	Mat meanImg;
	meanImg = Mat::zeros(size_cal, size_cal, CV_32FC1);
	Mat temp;
	//===================读取并求均值==================
	while (getline(fin, s))
	{
		cout << "filename: " << s << endl;
		Mat src = imread("faces/out/"+s);
		// Check if image is loaded fine
		if (src.empty()) {
			cout<<" Error opening image" << s;
			return -1;
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

	Mat covMat;		//协方差矩阵
	for (int i = 0; i < size_file; i++)
	{
		temp = images.at(i);
		temp.convertTo(temp, CV_32FC1);
		temp -= meanImg;//subtract the mean
		temp = temp.reshape(1, 1);

		if (0 == i)
			covMat = temp;
		else
			vconcat(covMat,temp,covMat);//复制
	}
	covMat /= size_file;

	//==================求特征人脸空间===========
	Mat eigenfaceSpace;
	
	calculateEigen(covMat, eigenfaceSpace);

	//===================重构==================

	Mat pic;
	pic = images.at(size_file+6);
	Mat show = pic;
	normalize(show, show, 255, 0, cv::NORM_MINMAX);
	show.convertTo(show, CV_8UC1);
 	imshow("img", show);
	waitKey(0);

	myreconstruct(eigenfaceSpace, pic, 10, meanImg);//pic 1*N^2


	pic = pic.reshape(1, size_cal*size_cal);//N^2 * 1


	float mindistance = 0;
	int indexrecord = 0;
	int tempdistance;
	Mat eigenfaceSpaceT;
	transpose(eigenfaceSpace, eigenfaceSpaceT);//转置

	vector<int> accurate_pic;
	int accurate[30] = {0};
	for (int index = 0; index < 30; index++)// 取几个人脸
	{
		pic = images.at(size_file + index);
		pic = pic.reshape(1, 1);//N^2 * 1

		for (int i = 0; i < size_file; i++)
		{
			Mat mat1 = eigenfaceSpaceT * pic.t();
			Mat mat2 = eigenfaceSpaceT * covMat.row(i).t();
			//cout << mat1 - mat2;
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
		cout << index << " ";
		cout << indexrecord << endl;
		accurate[index] = indexrecord;
		accurate_pic.push_back(indexrecord);
	}

	cout << accurate_pic.size();
	cout << endl << endl;
	
	cout << "====== accuracy ==========" << endl;
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
				//cout << mat1 - mat2;
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
			//cout << index << " ";
			//cout << indexrecord << endl;
			//accurate_pic.push_back(indexrecord);
			if (accurate[index] == indexrecord)
			{
				number++;
			}
		}
		cout << m << " ";
		cout << number << endl;
	}

	//transpose(covMat, covMatT);//转置
	/*
	Mat wholeSpace = (eigenfaceSpaceT *covMat.t());
	for (int index = 1; index < size_file; index = index + 5)// 取几个人脸
	{
		for (int i = 0; i < size_file; i++)
		{
			Mat mat1 = eigenfaceSpaceT *pic;
			Mat mat2 = wholeSpace.col(i);
			//cout << mat1 - mat2;
			tempdistance = difference(mat1, mat2);//pic 1*N^2
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
		cout << index<<" ";
		cout << indexrecord << endl;
	}
	//cout << indexrecord;
	*/
	myreconstruct(eigenfaceSpace, pic, 10, meanImg);//pic 1*N^2

	MatStore(eigenfaceSpace);

   	return 0;
}
