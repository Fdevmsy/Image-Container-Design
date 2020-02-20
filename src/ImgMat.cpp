//
// Created by shiyu on 2/17/20.
//

#include "ImgMat.h"
typedef unsigned char uchar;

void ImgMat::init(){
  if (height && width && channel) {
    Pixels = new uchar [height * width * channel];
  }
}

void ImgMat::release() {
  delete [] Pixels;
}

ImgMat::ImgMat() : height(0), width(0), channel(0), Pixels(0), owner(true){}

ImgMat::ImgMat(int height, int width, const string &ImgType){
  this->height = height;
  this->width = width;
  this->channel = ImgType == "RGB" ? 3 : 1;
  this->owner = true;
  init();
}

ImgMat::~ImgMat() {
  if (owner)
    release();
}

ImgMat::ImgMat(const ImgMat &other) {
  Pixels = other.Pixels;
  height = other.height;
  width = other.width;
  channel = other.channel;
  owner = false;
}

ImgMat &ImgMat::operator=(const ImgMat &other) {
  release();
  Pixels = other.Pixels;
  height = other.height;
  width = other.width;
  channel = other.channel;
  owner = false;
  return *this;
}

void ImgMat::create(int height, int width, const string &ImgType) {
  this->height = height;
  this->width = width;
  this->channel = (ImgType == "RGB" ? 3 : 1);
  this->owner = true;
  init();
}

void ImgMat::set(int x, int y, int c, uchar value) {
  Pixels[x * width * channel + y * channel + c] = value;
}

uchar ImgMat::at(int x, int y, int c) const {
  return Pixels[x * width * channel + y * channel + c];
}

bool ImgMat::isValid() const {return Pixels!=0;}

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
    other.Pixels[i] = Pixels[i];
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
    for( int y = 0; y < img.cols; y++ ) {
      if (img.channels() == 3) {
        for (int c = 0; c < 3; c++) {
          set(x, y, c, saturate_cast<uchar>(img.at<Vec3b>(x, y)[c]));
        }
      }
      else
        set(x, y, 0, saturate_cast<uchar>(img.at<uchar>(x, y)));
    }
  }
}




