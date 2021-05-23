#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void detect_keypoints();

int main(void)
{
	detect_keypoints();

	return 0;
}

void detect_keypoints()
{
	Mat src = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create(); //create 함수로 ORB클래스 객체 생성하고 feature 스마트 포인터에 저장

	vector<KeyPoint> keypoints; 
	feature->detect(src, keypoints); //ORB키포인트를 검출하여 keypoints 백터에 저장

	Mat desc;
	feature->compute(src, keypoints, desc); //ORB키포인트 기술자를 계산하여 desc 행렬에 저장

	cout << "keypoints.size(): " << keypoints.size() << endl;
	cout << "desc.size(): " << desc.size() << endl;

	Mat dst;
	drawKeypoints(src, keypoints, dst, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}