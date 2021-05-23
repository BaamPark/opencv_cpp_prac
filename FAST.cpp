#include "opencv2/opencv.hpp"
#include <iostream>
using namespace cv;
using namespace std;

void corner_fast()
{
	Mat src = imread("building.jpg", IMREAD_GRAYSCALE);

	if (src.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	vector<KeyPoint> keypoints; //vector�� std�� ��ü�� <>�� ���ø����·μ� type�� ����.
	FAST(src, keypoints, 60, true); //keypoints ������ FAST ������ ����� �����. true�� NMS ���ִ����

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (KeyPoint kp : keypoints) { //range based for�� https://boycoding.tistory.com/210
		Point pt(cvRound(kp.pt.x), cvRound(kp.pt.y)); //Point object pt initialization
		circle(dst, pt, 5, Scalar(0, 0, 255), 2);
	}

	imshow("src", src);
	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

int main()
{
	corner_fast();

	return 0;
}