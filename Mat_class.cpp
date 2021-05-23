#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void MatOp1() //void 함수안의 변수는 지역 변수임. return 값 필요없음.
{
	Mat img1; //img1.rows, img1.cols, img1.data 모두 0

	Mat img2(480, 640, CV_8UC1); // 8bit unsigned char, 1 channel

	Mat img3(480, 640, CV_8UC3); // 8bit unsigned char, 3 channel// 행이 480 열이 640

	Mat img4(Size(640, 480), CV_8UC3); // 가로 640 픽셀 세로 480픽셀의 행렬. img3와 같음.
	
	// 그런데 위의 경우 원소들의 값이 garbage 값으로 채워짐. 
	
	//그래서 아래와 같이 Mat 객체를 생성함과 동시에 모든 원소 값을 특정 값으로 초기화하여 사용하는 것이 안전함.
	Mat img5(480, 640, CV_8UC1, Scalar(128));
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255));

	Mat mat1 = Mat::zeros(3, 3, CV_32SC1);// 32signed integer channel 1
	Mat mat2 = Mat::ones(3, 3, CV_32FC1);// 원소들이 1로 채워진 행렬 3x3 32bit float channel 1
	Mat mat3 = Mat::eye(3, 3, CV_32FC1); //단위행렬 3x3 32bit float channel 1

	//할당된 메모리 공간의 데이터를 행렬로
	float data[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat4(2, 3, CV_32FC1, data);

	Mat_<float> mat5_(2, 3); //Mat_ class 사용
	mat5_ << 1, 2, 3, 4, 5, 6;
	Mat mat5 = mat5_;
	// 혹은 위 3줄 코드를 Mat mat5 = (Mat_<float>(2,3) << 1, 2, 3, 4, 5, 6); 으로 한줄로 쓸 수 있음.

	mat4.create(256, 256, CV_8UC3); //29줄에 생성된 객체 mat4에 새로운 행렬을 할당. create라는 멤버함수를 통해서.
	mat5.create(4, 4, CV_32FC1);

	mat4 = Scalar(255, 0, 0);
	mat5.setTo(1.f); //float은 소수점에 f를 붙임.
}

void MatOp2()
{
	Mat img1 = imread("dog.bmp");

	Mat img2 = img1; // shallow copy라고 함. img2는 img1을 참조하고 있으며, img1과 img2는 하나의 영상을 공유함.
	Mat img3;
	img3 = img1;

	Mat img4 = img1.clone(); //deep copy라고 함. 픽셀데이터를 공유하지 않고 메모리 공간을 새로 할당하여 픽셀데이터를 복사함.
	Mat img5;
	img1.copyTo(img5); //마찬가지로 새로운 메모리를 할당하는 깊은 복사

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
	} //Mat::at 멤버 함수를 사용해서 행렬의 모든 원소를 1씩 증가시킴

	for (int j = 0; j < mat1.rows; j++) {
		uchar* p = mat1.ptr<uchar>(j);
		for (int i = 0; i < mat1.cols; i++) {
			p[i]++;
		}
	} //Mat::ptr을 써서 행렬의 모든 원소값을 1씩 증가 시킴

	for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it) {
		(*it)++;
	} //MatIterator_ 반복자를 사용하여 행렬의 모든 원소를 1씩 증가시킴.

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

	cout << "mat1.t(): \n" << mat1.t() << endl; //전치행렬
	cout << "mat1 + 3: \n" << mat1 + 3 << endl; //모든 원소에 3씩 더함
	cout << "mat1 + mat2: \n" << mat1 + mat2 << endl;
	cout << "mat1 * mat2: \n" << mat1 * mat2 << endl; //내적연산. mat2 행렬은 mat1행렬의 역행렬이니 두개를 내적하면 단위행렬이 나옴.
}

void MatOp7()
{
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);

	Mat img1f;
	img1.convertTo(img1f, CV_32FC1);

	uchar data1[] = { 1, 2, 3, 4, 5, 6, 7, 8 ,9, 10, 11, 12 };
	Mat mat1(3, 4, CV_8UC1, data1);
	Mat mat2 = mat1.reshape(0, 1); //0은 추가하는 채널의 수, 1은 resize할 row의 값

	cout << "mat1:\n" << mat1 << endl;
	cout << "mat2:\n" << mat2 << endl;

	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
	mat1.push_back(mat3); //mat1의 최하단 행에 mat3를 push
	cout << "mat1:\n" << mat1 << endl;

	mat1.resize(6, 100); //mat1의 행을 6개로 하고 늘어난 원소들의 값을 100으로 채움
	cout << "mat1:\n" << mat1 << endl; 

}