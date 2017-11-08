#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>

using namespace std;

#include <zxing/LuminanceSource.h>
#include <zxing/MultiFormatReader.h>
#include <zxing/qrcode/QRCodeReader.h>
#include <zxing/common/GlobalHistogramBinarizer.h>
#include <zxing/Exception.h>


using namespace zxing;
using namespace qrcode;

class OpenCVBitmapSource : public LuminanceSource {
 private:
  cv::Mat _image;

 public:
  OpenCVBitmapSource(cv::Mat &image) : LuminanceSource(image.cols, image.rows) {
    _image = image.clone();
  }

  ~OpenCVBitmapSource() {}

  int getWidth() const { return _image.cols; }
  int getHeight() const { return _image.rows; }

  ArrayRef<char> getRow(int y, ArrayRef<char> row) const {
    int width_ = getWidth();
    if (!row) row = ArrayRef<char>(width_);
    const char *p = _image.ptr<char>(y);
    for (int x = 0; x < width_; ++x, ++p) row[x] = *p;
    return row;
  }

  ArrayRef<char> getMatrix() const {
    int width_ = getWidth();
    int height_ = getHeight();
    ArrayRef<char> matrix = ArrayRef<char>(width_ * height_);
    for (int y = 0; y < height_; ++y) {
      const char *p = _image.ptr<char>(y);
      for (int x = 0; x < width_; ++x, ++p) {
        matrix[y * width_ + x] = *p;
      }
    }
    return matrix;
  }
  /*
  // The following methods are not supported (the DataMatrix Reader doesn't call these methods)
  bool isCropSupported() const { return false; }
  Ref<LuminanceSource> crop(int left, int top, int width, int height) {}
  bool isRotateSupported() const { return false; }
  Ref<LuminanceSource> rotateCounterClockwise() {}
  */
};

void decode_image(Reader *reader, cv::Mat &image)
{
    try
    {
        Ref<OpenCVBitmapSource> source(new OpenCVBitmapSource(image));
        Ref<Binarizer> binarizer(new GlobalHistogramBinarizer(source));
        Ref<BinaryBitmap> bitmap(new BinaryBitmap(binarizer));
        Ref<Result> result(reader->decode(bitmap, DecodeHints(DecodeHints::TRYHARDER_HINT)));
        cout << result->getText()->getText() << endl;
    }
    catch (zxing::Exception& e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

int main(int argc, const char** argv) {
    QRCodeReader cr;

    std::string imgPath(argv[1]);
    cv::Mat img = cv::imread(imgPath, CV_LOAD_IMAGE_GRAYSCALE);
    if(!img.data) {
        std::cerr << "exit";
        return -1;
    }

    cv::namedWindow("asd", 1);
    cv::imshow("asd", img);
    cv::waitKey(0);

    decode_image(&cr, img);

    return 0;
}