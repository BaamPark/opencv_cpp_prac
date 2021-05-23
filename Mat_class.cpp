#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void MatOp1() //void �Լ����� ������ ���� ������. return �� �ʿ����.
{
	Mat img1; //img1.rows, img1.cols, img1.data ��� 0

	Mat img2(480, 640, CV_8UC1); // 8bit unsigned char, 1 channel

	Mat img3(480, 640, CV_8UC3); // 8bit unsigned char, 3 channel// ���� 480 ���� 640

	Mat img4(Size(640, 480), CV_8UC3); // ���� 640 �ȼ� ���� 480�ȼ��� ���. img3�� ����.
	
	// �׷��� ���� ��� ���ҵ��� ���� garbage ������ ä����. 
	
	//�׷��� �Ʒ��� ���� Mat ��ü�� �����԰� ���ÿ� ��� ���� ���� Ư�� ������ �ʱ�ȭ�Ͽ� ����ϴ� ���� ������.
	Mat img5(480, 640, CV_8UC1, Scalar(128));
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255));

	Mat mat1 = Mat::zeros(3, 3, CV_32SC1);// 32signed integer channel 1
	Mat mat2 = Mat::ones(3, 3, CV_32FC1);// ���ҵ��� 1�� ä���� ��� 3x3 32bit float channel 1
	Mat mat3 = Mat::eye(3, 3, CV_32FC1); //������� 3x3 32bit float channel 1

	//�Ҵ�� �޸� ������ �����͸� ��ķ�
	float data[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat4(2, 3, CV_32FC1, data);

	Mat_<float> mat5_(2, 3); //Mat_ class ���
	mat5_ << 1, 2, 3, 4, 5, 6;
	Mat mat5 = mat5_;
	// Ȥ�� �� 3�� �ڵ带 Mat mat5 = (Mat_<float>(2,3) << 1, 2, 3, 4, 5, 6); ���� ���ٷ� �� �� ����.

	mat4.create(256, 256, CV_8UC3); //29�ٿ� ������ ��ü mat4�� ���ο� ����� �Ҵ�. create��� ����Լ��� ���ؼ�.
	mat5.create(4, 4, CV_32FC1);

	mat4 = Scalar(255, 0, 0);
	mat5.setTo(1.f); //float�� �Ҽ����� f�� ����.
}

void MatOp2()
{
	Mat img1 = imread("dog.bmp");

	Mat img2 = img1; // shallow copy��� ��. img2�� img1�� �����ϰ� ������, img1�� img2�� �ϳ��� ������ ������.
	Mat img3;
	img3 = img1;

	Mat img4 = img1.clone(); //deep copy��� ��. �ȼ������͸� �������� �ʰ� �޸� ������ ���� �Ҵ��Ͽ� �ȼ������͸� ������.
	Mat img5;
	img1.copyTo(img5); //���������� ���ο� �޸𸮸� �Ҵ��ϴ� ���� ����

	img1.setTo(Scalar(0, 255, 255)); //yellow

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
	imshow("img4", img4);
	imshow("img5", img5);
}

void MatOp3()
{
	Mat img1 = imread("cat.bmp");

	if (img1.empty()) {
		cerr << "Image load failed" << endl;
		return;
	}

	Mat img2 = img1(Rect(220, 120, 340, 240));
	Mat img3 = img1(Rect(220, 120, 340, 240)).clone;

	img2 = ~img2;

	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);

	waitKey();
	destroyAllWindows();
}

void MatOp4() 
{
	Mat mat1 = Mat::zeros(3, 4, CV_8UC1);

	for (int j = 0; j < mat1.rows; j++) {
		for (int i = 0; i < mat1.cols; i++) {
			mat1.at<uchar>(j, i)++;
		}
	} //Mat::at ��� �Լ��� ����ؼ� ����� ��� ���Ҹ� 1�� ������Ŵ

	for (int j = 0; j < mat1.rows; j++) {
		uchar* p = mat1.ptr<uchar>(j);
		for (int i = 0; i < mat1.cols; i++) {
			p[i]++;
		}
	} //Mat::ptr�� �Ἥ ����� ��� ���Ұ��� 1�� ���� ��Ŵ

	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it) {
		(*it)++;
	} //MatIterator_ �ݺ��ڸ� ����Ͽ� ����� ��� ���Ҹ� 1�� ������Ŵ.

	cout << "mat1:\n" << mat1 << endl;
}

void MatOp5()
{
	Mat img1 = imread("lena.bmp");

	cout << "Width: " << img1.cols << endl;
	cout << "height: " << img1.rows << endl;
	cout << "channel: " << img1.channels() << endl;

	if (img1.type() == CV_8UC1) {
		cout << "img5 is a grayscale image." << endl;
	}

	else if (img1.type() == CV_8UC3) {
		cout << "img5 is a truecolor image" << endl;
	}

	float data[] = { 2.f, 1.414f, 3.f, 1.732f };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;
}

void MatOp6() 
{
	float data[] = { 1, 1, 2, 3 };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1L\n" << mat1 << endl;

	Mat mat2 = mat1.inv();
	cout << "mat2:\n" << mat2 << endl;

	cout << "mat1.t(): \n" << mat1.t() << endl; //��ġ���
	cout << "mat1 + 3: \n" << mat1 + 3 << endl; //��� ���ҿ� 3�� ����
	cout << "mat1 + mat2: \n" << mat1 + mat2 << endl;
	cout << "mat1 * mat2: \n" << mat1 * mat2 << endl; //��������. mat2 ����� mat1����� ������̴� �ΰ��� �����ϸ� ��������� ����.
}

void MatOp7()
{
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);

	Mat img1f;
	img1.convertTo(img1f, CV_32FC1);

	uchar data1[] = { 1, 2, 3, 4, 5, 6, 7, 8 ,9, 10, 11, 12 };
	Mat mat1(3, 4, CV_8UC1, data1);
	Mat mat2 = mat1.reshape(0, 1); //0�� �߰��ϴ� ä���� ��, 1�� resize�� row�� ��

	cout << "mat1:\n" << mat1 << endl;
	cout << "mat2:\n" << mat2 << endl;

	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
	mat1.push_back(mat3); //mat1�� ���ϴ� �࿡ mat3�� push
	cout << "mat1:\n" << mat1 << endl;

	mat1.resize(6, 100); //mat1�� ���� 6���� �ϰ� �þ ���ҵ��� ���� 100���� ä��
	cout << "mat1:\n" << mat1 << endl; 

}