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

	vector<KeyPoint> keypoints; //vector는 std의 객체임 <>는 템플릿형태로서 type을 넣음.
	FAST(src, keypoints, 60, true); //keypoints 변수에 FAST 연산의 결과가 저장됨. true는 NMS 비최대억제

	Mat dst;
	cvtColor(src, dst, COLOR_GRAY2BGR);

	for (KeyPoint kp : keypoints) { //range based for문 https://boycoding.tistory.com/210
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