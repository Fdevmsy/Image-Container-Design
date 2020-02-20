#ifndef APPLEASSIGNMENT_UTILITY_H
#define APPLEASSIGNMENT_UTILITY_H
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<string>
using namespace std;
using namespace cv;

class Utility {
public:
  Utility(){};
  static void Display(const Mat& img, const string& windowName="default");
  static void Display(const string &imgPath, int colorFlag=1);
  static void SaveImg(const Mat& img, const string& filename="output.png");
};


#endif //APPLEASSIGNMENT_UTILITY_H
