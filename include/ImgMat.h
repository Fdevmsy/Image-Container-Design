//
// Created by shiyu on 2/17/20.
//

#ifndef APPLEASSIGNMENT_IMGMAT_H
#define APPLEASSIGNMENT_IMGMAT_H
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include <Utility.h>
#include <memory>
using namespace std;
using namespace cv;
typedef unsigned char uchar;

class ImgMat {
private:
  shared_ptr<uchar> data;
  int height_;
  int width_;
  int channel_;

  void init();

public:
  ImgMat();

  ImgMat(int height, int width, const string &ImgType);

  void create(int height, int width, const string &ImgType);

  void loadImg(const string &path, const string &imgType = "RGB");

  void copyTo(ImgMat &other) const;

  long useCount() const;

  bool isValid() const;

  int getHeight() const;

  int getWidth() const;

  int getChannel() const;

  string getType() const;

  void set(int x, int y, int c, uchar value);

  uchar at(int x, int y, int c) const;

};

#endif