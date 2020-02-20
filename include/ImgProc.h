//
// Created by shiyu on 2/17/20.
//

#ifndef APPLEASSIGNMENT_IMGPROC_H
#define APPLEASSIGNMENT_IMGPROC_H

#include <Utility.h>
#include <ImgMat.h>

class ImgProc {
public:
  static void RGB2Gray(const ImgMat& src, ImgMat& dst);
  static vector<vector<uchar> > ComputeHistogram(const ImgMat& src);
  static void Display(const ImgMat& src, const string& windowName);
  static void CenterMask(ImgMat& dst, int maskSize);
};


#endif //APPLEASSIGNMENT_IMGPROC_H
