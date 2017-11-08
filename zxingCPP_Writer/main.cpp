#include <iostream>
#include <string>
#include <vector>

#include "nayukiQRCodeGen/QrCode.hpp"

#include <opencv2/opencv.hpp>

// build with g++ main.cpp nayukiQRCodeGen/QrCode.cpp
// nayukiQRCodeGen/BitBuffer.cpp nayukiQRCodeGen/QrSegment.cpp -o main

using namespace qrcodegen;
using namespace cv;

int main() {
  int scale = 5;
  int border = 2 * scale;

  // Simple operation
  QrCode qr0 = QrCode::encodeText("Helasdasdlo, world!", QrCode::Ecc::HIGH);
  unsigned char bits[qr0.size][qr0.size];
  std::cout << qr0.toSvgString(2);

  // get modules
  int k = 0;
  for (int y = 0; y < qr0.size; y++) {
    for (int x = 0; x < qr0.size; x++) {
      // white is 0(false), black is 1 (true)
      bits[y][x] =  (qr0.getModule(x, y) ? 0 : 255);  
    }
  }

  cv::Mat qrCodeRaw(qr0.size, qr0.size, CV_8UC1, bits);
  cv::Mat qrCode;

  resize(qrCodeRaw, qrCode, Size(), 5.0, 5.0, INTER_NEAREST);

  std::vector<int> compression_params;
  compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
  compression_params.push_back(9);

  cv::Scalar color = Scalar(255, 255, 255);
  copyMakeBorder(qrCode, qrCode, border, border, border, border, BORDER_CONSTANT, color);

  try {
    cv::imwrite("qrcode.png", qrCode, compression_params);
  } catch (std::runtime_error& ex) {
    fprintf(stderr, "Exception converting image to PNG format: %s\n",
            ex.what());
    return 1;
  }

  cv::waitKey();
}