//
// Created by shiyu on 2/17/20.
//

#include <iostream>
#include <string>
#include <ImgMat.h>
#include <ImgProc.h>
using namespace std;
using namespace cv;

int main(int argc, char **argv) {
  if (argc != 2) {
    printf("usage: ./ImgLibrary <Image_Path>\n");
    return -1;
  }
  {
    /** original input */
    ImgMat imgMat;
    imgMat.loadImg(argv[1], "RGB");
    cout << "Height: " << imgMat.getHeight() << " Width: "
         << imgMat.getWidth() << " Type: " << imgMat.getType() << endl;
    ImgProc::Display(imgMat, "input");

    /** RGB to Gray */
    ImgMat gray(imgMat.getHeight(), imgMat.getWidth(), "GrayScale");
    ImgProc::RGB2Gray(imgMat, gray);
    ImgProc::Display(gray, "input (grayscale converted)");

    /** shallow copy of gray, shallow copy won't become the owner in this case*/
    ImgMat sCopy(gray);

    /** deep copy of gray*/
    ImgMat dCopy;
    gray.copyTo(dCopy);

    /** apply some mask to gray at the center*/
    ImgProc::CenterMask(gray, min(gray.getHeight(), gray.getWidth()) / 2);
    ImgProc::Display(gray, "masked gray");

    /** check if shallow/deep copy is touched */
    ImgProc::Display(dCopy, "deep copy of gray (untouched)");
    ImgProc::Display(sCopy, "shallow copy of gray (affected)");



    /** compute histogram */
    auto hist = ImgProc::ComputeHistogram(imgMat);
    cout << "size of histogram (" << hist.size() << ", " << hist[0].size() << ")" << endl;
    cout << "number of shallow copy of the ori image: " << sCopy.useCount() << endl;
  }
  return 0;
}