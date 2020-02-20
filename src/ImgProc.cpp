//
// Created by ferrycake on 2/17/20.
//

#include "ImgProc.h"
/**
 * convert RGB image to gray scale
 * @param src
 * @param dst
 */
void ImgProc::RGB2Gray(const ImgMat &src, ImgMat &dst) {
  assert(src.isValid()==1);
  assert(src.getChannel() == 3);
  for( int x = 0; x < dst.getHeight(); x++ ) {
    for( int y = 0; y < dst.getWidth(); y++ ) {
      uchar value = saturate_cast<uchar>(0.11 * src.at(x, y, 0) +
                                           0.59 * src.at(x, y, 1) +
                                           0.3 * src.at(x, y, 2));
      dst.set(x, y, 0, value);
    }
  }
}

/**
 * compute histogram of image
 * @param src
 * @return shape (1, 256) for grayscale and (3, 256) for color
 */
vector<vector<uchar> > ImgProc::ComputeHistogram(const ImgMat &src) {
  assert(src.isValid()==1);
  vector<vector<uchar>> hist(src.getChannel(), vector<uchar> (256));
  for( int x = 0; x < src.getHeight(); x++ ) {
    for( int y = 0; y < src.getWidth(); y++ ) {
      for (int c = 0; c < src.getChannel(); c++)
        hist[c][src.at(x, y, c)]++;
    }
  }
  return hist;
}

/**
 * display image
 * @param src
 * @param windowName
 */
void ImgProc::Display(const ImgMat &src, const string& windowName) {
  assert(src.isValid()==1);
  Mat img;
  img.create(src.getHeight(), src.getWidth(), CV_8UC(src.getChannel()));
  for( int x = 0; x < src.getHeight(); x++ ) {
    for( int y = 0; y < src.getWidth(); y++ ) {
      if (src.getChannel()==3) {
        for (int c = 0; c < 3; c++) {
          img.at<Vec3b>(x, y)[c] = src.at(x, y, c);
        }
      }
      else
        img.at<uchar>(x, y) = src.at(x, y, 0);
    }
  }
  Utility::Display(img, windowName);
}

/**
 * function for demonstrate shallow/deep copy
 * @param dst
 * @param maskSize
 */
void ImgProc::CenterMask(ImgMat& dst, int maskSize){
  assert(dst.isValid() == 1);
  if (dst.getChannel() != 1 || dst.getHeight() <= maskSize || dst.getWidth() <= maskSize) return;
  for (int i = dst.getHeight() / 2 - maskSize / 2; i < dst.getHeight() / 2 + maskSize / 2; i++){
    for (int j = dst.getWidth() / 2 - maskSize / 2; j < dst.getWidth() / 2 + maskSize / 2; j++){
      dst.set(i, j, 0, 0);
    }
  }
}