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

	Ptr<Feature2D> feature = ORB::create(); //create �Լ��� ORBŬ���� ��ü �����ϰ� feature ����Ʈ �����Ϳ� ����

	vector<KeyPoint> keypoints; 
	feature->detect(src, keypoints); //ORBŰ����Ʈ�� �����Ͽ� keypoints ���Ϳ� ����

	Mat desc;
	feature->compute(src, keypoints, desc); //ORBŰ����Ʈ ����ڸ� ����Ͽ� desc ��Ŀ� ����

	cout << "keypoints.size(): " << keypoints.size() << endl;
	cout << "desc.size(): " << desc.size() << endl;

	Mat dst;
	drawKeypoints(src, keypoints, dst, Scalar::all(-1), DrawMatchesFlags::DRAW_RICH_KEYPOINTS);

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}