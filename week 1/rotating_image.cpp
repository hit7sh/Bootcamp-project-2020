#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

Mat rotate(Mat src, float angle)   
{
    Point2f center((src.cols - 1) / 2.0, (src.rows - 1) / 2.0);
    Mat rot = cv::getRotationMatrix2D(center, angle, 1.0);
    
    Rect2f bbox = cv::RotatedRect(cv::Point2f(), src.size(), angle).boundingRect2f();
    
    rot.at<double>(0, 2) += bbox.width / 2.0 - src.cols / 2.0;
    rot.at<double>(1, 2) += bbox.height / 2.0 - src.rows / 2.0;

    Mat dst;
    warpAffine(src, dst, rot, bbox.size());
    
    return dst;         
}

int main()
{
    Mat img = imread("C:/Users/hit7sh/Downloads/lenna.png");
    
    if (img.empty())
    {
        cout << "Could not open the image.";    
        cin.get();
        return -1;
    }

    float angle;
    cout << "ENTER ANGLE OF ROTATION : ";
    cin >> angle;

    Mat dst = rotate(img, angle);
    namedWindow("image", WINDOW_NORMAL);
    imshow("image", dst);

    waitKey(0);
    return 0;
}
