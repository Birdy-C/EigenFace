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
�������ƶ� ֻ����N*1
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
ͼ��Ԥ����
*/
void prehandle(Mat& src)
{
	cvtColor(src, src, COLOR_BGR2GRAY);
	equalizeHist(src, src);
	resize(src, src, Size(size_cal, size_cal), 0, 0, INTER_LINEAR);
	src.convertTo(src, CV_32FC1);
}

/*
pic : �ع��Ĵ�ͼ
m: ���ؼ����������ع��Ľ�� ���m�����巵��ȫ��
meanImg:��ֵ����
*/
Mat myreconstruct(const Mat& eigenfaceSpace, const Mat& pic,const int m, const Mat& meanImg)//pic 1*N^2
{
	Mat eigenfaceSpaceT;
	transpose(eigenfaceSpace, eigenfaceSpaceT);//ת��

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
				hconcat(re_face,showtemp, re_face);//����
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
���������ռ�
*/
void calculateEigen(const Mat& covMat, Mat &eigenfaceSpace)
{
	Mat covMatT;//N^2 * m
	transpose(covMat, covMatT);//ת��
	covMatT.convertTo(covMatT, CV_32FC1);
	covMat.convertTo(covMat, CV_32FC1);
	Mat covMatResult = (covMat * covMatT);//

	Mat eigenvalues, eigenvectors;
	eigen(covMatResult, eigenvalues, eigenvectors);//subsequent matrix rows
	//===================�����������ռ�==================

	Mat eigenvectorsT, show;//N^2 *m
	Mat eigenfaceSpaceT, temp, tmp2, tempT;
	transpose(eigenvectors, eigenvectorsT);//ת��

	Mat pre_eigen_10;   //��ʾǰʮ����������



						//����������
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

		//eigenfaces.push_back(temp);//��λ��������.��������
		if (0 == i)
		{
			eigenfaceSpace = temp;
		}
		else
		{
			hconcat(eigenfaceSpace, temp, eigenfaceSpace);//����
		}

		transpose(temp, tempT);

		//��ʾ
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
	//===================��ȡ�����ֵ==================
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
		getline(fin, s); //���ݵ�ԭ������ȥ��һ��
	}
	size_file = images.size() - 30;
	meanImg = meanImg / size_file;
	Mat mean_show;
	meanImg.convertTo(mean_show, CV_8UC1);
	imshow("mean image", mean_show);
	//waitKey(0);

	//===================����Э����==================

	Mat covMat;		//Э�������
	for (int i = 0; i < size_file; i++)
	{
		temp = images.at(i);
		temp.convertTo(temp, CV_32FC1);
		temp -= meanImg;//subtract the mean
		temp = temp.reshape(1, 1);

		if (0 == i)
			covMat = temp;
		else
			vconcat(covMat,temp,covMat);//����
	}
	covMat /= size_file;

	//==================�����������ռ�===========
	Mat eigenfaceSpace;
	
	calculateEigen(covMat, eigenfaceSpace);

	//===================�ع�==================

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
	transpose(eigenfaceSpace, eigenfaceSpaceT);//ת��

	vector<int> accurate_pic;
	int accurate[30] = {0};
	for (int index = 0; index < 30; index++)// ȡ��������
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
	for (int m = 0; m < size_file; m = m + 1)// ȡ��������
	{
		int number = 0;
		for (int index = 0; index < 30; index++)// ȡ��������
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

	//transpose(covMat, covMatT);//ת��
	/*
	Mat wholeSpace = (eigenfaceSpaceT *covMat.t());
	for (int index = 1; index < size_file; index = index + 5)// ȡ��������
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
