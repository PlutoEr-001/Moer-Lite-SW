#pragma once
#include <CoreLayer/Math/Math.h>
#include <memory>
#include <CoreLayer/ColorSpace/Spectrum.h>
// TODO 实现一个模板类，提供图片多通道、多数据类型的支持
//* 目前只支持三通道（即RGB）的图片格式

//* Image的数据组织格式如下
//* [0, 0] ----X-----
//* |               |
//* |               |
//* Y        [x, y] |
//* -----------------
//* 坐标[0, 0]对应图片左上角
//* 坐标[x, y]对应图片第x列，第y行

class Image {
public:
  Image() = delete;

  Image(Vector2i _size) : size(_size) {
    data = new float[_size[0] * _size[1] * channels];
    filterWeigh = new float[_size[0] * _size[1]];
    contriSum = new Spectrum [_size[0] * _size[1]];
    for(int i=0;i<_size[0] * _size[1];i++){
        filterWeigh[i] = 0.f;
        contriSum[i] = {0.f, 0.f, 0.f};
    }
    pMin = Point2f{0.f,0.f};
    pMax = Point2f{(float)_size[0]-1.f,(float)_size[1]-1.f};
  }

  Image(Vector2i _size, float *_data) : size(_size), data(_data) {}

  ~Image() { delete[] data; }

  //* 获取坐标[x, y]处的三通道值
  Vector3f getValue(const Vector2i &xy) const;

  //* 设置坐标[x, y]处的三通道值
  void setValue(const Vector2i &xy, const Vector3f &val);

  void OIDN_deposit(const Vector2i &xy);

  void GAUSS_deposit(const Vector2i &xy);

  void addFilterWeigh(const Vector2i &xy, float val);

  void addContriSum(const Vector2i &xy, Spectrum val);

  //* 以PNG格式保存该图片
  void savePNG(const char *filename) const;

  //* 以HDR格式保存该图片
  void saveHDR(const char *filename) const;

public:
  Vector2i size;
  static constexpr int channels = 3;
  Point2f pMin,pMax;

private:
  float *data = nullptr;
  float *filterWeigh = nullptr;
  Spectrum *contriSum = nullptr;
};

//* 根据路径加载一张图片(PNG/JPG/HDR)
std::shared_ptr<Image> loadImage(const char *filepath);
