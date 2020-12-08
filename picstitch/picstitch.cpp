#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/stitching.hpp>
using namespace std;
using namespace cv;
bool try_use_gpu = false;
vector<Mat> imgs;
string result_name = "dst1.jpg";
void readImage();  //导入所有原始图像
int main()
{
	//Mat img1 = imread("1.jpg");
	//Mat img2 = imread("2.jpg");
	readImage();

	Stitcher stitcher = Stitcher::createDefault(try_use_gpu);
	// 使用stitch函数进行拼接
	Mat pano;
	Stitcher::Status status = stitcher.stitch(imgs, pano);
	if (status != Stitcher::OK)
	{
		cout << "Can't stitch images, error code = " << int(status) << endl;
		return -1;
	}
	imwrite(result_name, pano);
	// 显示源图像，和结果图像
	imshow("拼接后图像", pano);
	if (waitKey() == 27)
		return 0;
}

void readImage()
{
	std::string pattern_jpg;
	std::vector<cv::String> imgage_files;
	//图片所在的绝对路径
	pattern_jpg = "C:\\Users\\DELL\\Desktop\\pic\\*.jpg";
	cv::glob(pattern_jpg, imgage_files);
	cout << "图片数量" << imgage_files.size() << endl;
	for (int i = 0; i < imgage_files.size(); i++)
	{
		Mat img = imread(imgage_files[i]);
		//imshow("123",img);
		if (img.empty())
		{
			cout << "Can't read image '" << imgage_files[i] << "'\n";
		}
		imgs.push_back(img);
	}			
}