//
// Created by shiyu on 2/17/20.
//

#include "ImgMat.h"
typedef unsigned char uchar;

void ImgMat::init(){
  if (height && width && channel) {
    data = shared_ptr<uchar>(new uchar[height * width * channel]);
  }
}

ImgMat::ImgMat() : height(0), width(0), channel(0), data(0) {}

ImgMat::ImgMat(int height, int width, const string &ImgType){
  this->height = height;
  this->width = width;
  this->channel = ImgType == "RGB" ? 3 : 1;
//  this->owner = true;
  init();
}

void ImgMat::create(int height, int width, const string &ImgType) {
  this->height = height;
  this->width = width;
  this->channel = (ImgType == "RGB" ? 3 : 1);
  init();
}

void ImgMat::set(int x, int y, int c, uchar value) {
  data.get()[x * width * channel + y * channel + c] = value;
}

uchar ImgMat::at(int x, int y, int c) const {
  return data.get()[x * width * channel + y * channel + c];
}

bool ImgMat::isValid() const { return data != 0; }

/**
 * deep copy to other
 * @param other
 */
void ImgMat::copyTo(ImgMat &other) const {
  if (channel == 3)
    other.create(height, width, "RGB");
  else
    other.create(height, width, "GrayScale");
  for (int i = 0; i < height * width * channel; i++){
    other.data.get()[i] = data.get()[i];
  }
}

int ImgMat::getHeight() const {return height;}

int ImgMat::getWidth() const {return width;}

string ImgMat::getType() const {return channel==3 ? "RGB" : "GrayScale";}

int ImgMat::getChannel() const{return channel;};

/**
 * load image from path
 * @param path
 * @param imgType
 */
void ImgMat::loadImg(const string &path, const string &imgType) {
  Mat img;
  img = imread(path, imgType=="RGB");
  if (!img.data) {
    cout << "cannot load image file at " << path << endl;
    return;
  }
  if (img.channels()==3)
    create(img.rows, img.cols, "RGB");
  else
    create(img.rows, img.cols, "GrayScale");

  for( int x = 0; x < img.rows; x++ ) {
    for (int y = 0; y < img.cols; y++) {
      if (img.channels() == 3) {
        for (int c = 0; c < 3; c++) {
          set(x, y, c, saturate_cast<uchar>(img.at<Vec3b>(x, y)[c]));
        }
      } else
        set(x, y, 0, saturate_cast<uchar>(img.at<uchar>(x, y)));
    }
  }
}

long ImgMat::useCount() const {
  return data.use_count();
}




