//
// Created by shiyu on 2/16/20.
//

#include "Utility.h"
void Utility::Display(const Mat &img, const string &windowName) {
  if (!img.data) {
    cout << "invalid image" << endl;
    return;
  }
  namedWindow(windowName, CV_WINDOW_AUTOSIZE);
  imshow(windowName, img);
  waitKey(0);
}

void Utility::Display(const string &imgPath, int colorFlag) {
  Mat img;
  img = imread(imgPath, colorFlag);
  if (!img.data) {
    cout << "cannot load image file at " << imgPath << endl;
    return;
  }
  Display(img);
}

void Utility::SaveImg(const Mat &img, const string &filename) {
  if (!img.data) {
    cout << "invalid image" << endl;
    return;
  }
  imwrite(filename, img);
}

