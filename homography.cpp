#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void keypoint_matching();
void good_matching();
void find_homography();

int main(void)
{
	keypoint_matching();
	good_matching();
	find_homography();

	return 0;
}

void keypoint_matching()
{
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create(); //ORB 객체 생성하고 feature 스마트 포인터에 저장

	vector<KeyPoint> keypoints1, keypoints2;
	Mat desc1, desc2;
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1); //특징점 걸출하고 기술자를 계산한 것을 desc1에 저장
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);
	cout << "desc1.size(): " << desc1.size() << endl;
	cout << "desc2.size(): " << desc2.size() << endl;

	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING); //BFMatcher 클래스 객체 생성하고 거기 계산방식은 해밍거리 사용

	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches); //매치

	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, matches, dst);

	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void good_matching()
{
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create();

	vector<KeyPoint> keypoints1, keypoints2;
	Mat desc1, desc2;
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);

	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches);

	std::sort(matches.begin(), matches.end()); //두 영상의 특징점 매칭 결과를 정렬
	vector<DMatch> good_matches(matches.begin(), matches.begin() + 50); //정렬된 매칭 결과에서 상위 50개 매칭결과를 good_matches에 저장

	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, good_matches, dst,
		Scalar::all(-1), Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}

void find_homography()
{
	Mat src1 = imread("box.png", IMREAD_GRAYSCALE);
	Mat src2 = imread("box_in_scene.png", IMREAD_GRAYSCALE);

	if (src1.empty() || src2.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}

	Ptr<Feature2D> feature = ORB::create();

	vector<KeyPoint> keypoints1, keypoints2;
	Mat desc1, desc2;
	feature->detectAndCompute(src1, Mat(), keypoints1, desc1);
	feature->detectAndCompute(src2, Mat(), keypoints2, desc2);

	Ptr<DescriptorMatcher> matcher = BFMatcher::create(NORM_HAMMING);

	vector<DMatch> matches;
	matcher->match(desc1, desc2, matches);

	std::sort(matches.begin(), matches.end());
	vector<DMatch> good_matches(matches.begin(), matches.begin() + 50);

	Mat dst;
	drawMatches(src1, keypoints1, src2, keypoints2, good_matches, dst,
		Scalar::all(-1), Scalar::all(-1), vector<char>(),
		DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS);

	vector<Point2f> pts1, pts2; 
	for (size_t i = 0; i < good_matches.size(); i++) { //특징점 좌표를 추출하여 pts1, pts2에 저장. findHomography함수가 인수를 Point2f 객체로 받아서 이 작업이 필요
		pts1.push_back(keypoints1[good_matches[i].queryIdx].pt);
		pts2.push_back(keypoints2[good_matches[i].trainIdx].pt);
	}

	Mat H = findHomography(pts1, pts2, RANSAC); //호모그래피 행렬을 H에 저장. RANSAC알고리즘 사용.

	vector<Point2f> corners1, corners2;
	corners1.push_back(Point2f(0, 0));
	corners1.push_back(Point2f(src1.cols - 1.f, 0));
	corners1.push_back(Point2f(src1.cols - 1.f, src1.rows - 1.f));
	corners1.push_back(Point2f(0, src1.rows - 1.f));
	perspectiveTransform(corners1, corners2, H);

	vector<Point> corners_dst;
	for (Point2f pt : corners2) {
		corners_dst.push_back(Point(cvRound(pt.x + src1.cols), cvRound(pt.y)));
	}

	polylines(dst, corners_dst, true, Scalar(0, 255, 0), 2, LINE_AA);

	imshow("dst", dst);

	waitKey();
	destroyAllWindows();
}