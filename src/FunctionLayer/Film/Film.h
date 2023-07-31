#pragma once
#include <CoreLayer/ColorSpace/Spectrum.h>
#include <ResourceLayer/Image.h>
#include <ResourceLayer/JsonUtil.h>
#include <FunctionLayer/Filter/Filter.h>

class Film {
public:
  Film() = delete;

  explicit Film(const Json &json) ;

  void OIDN_deposit(const Vector2i xy) {
    //* 无论光谱内部实现如何，写入图片时均转为3通道格式
    image->OIDN_deposit(xy);
  }

  void GAUSS_deposit(const Vector2i xy) {
      //* 无论光谱内部实现如何，写入图片时均转为3通道格式
      image->GAUSS_deposit(xy);
  }

  void OIDN_AddSample(const Vector2i &pFilm, Spectrum L) {
        Vector3f v = toVec3(L);
        image->setValue(pFilm, v);
  }

  void GAUSS_AddSample(const Vector2i &pFilm, Spectrum L){
      Point2f p0 {ceilf((float)pFilm[0] - filter->radius[0]),
                ceilf((float)pFilm[1] - filter->radius[1])};
      Point2f p1 {floorf((float)pFilm[0] + filter->radius[0])+1.f,
                    floorf((float)pFilm[1] + filter->radius[1])+1.f};
      p0 = Point2f{fmaxf(p0[0],image->pMin[0]),fmaxf(p0[1],image->pMin[1])};
      p1 = Point2f{fminf(p1[0],image->pMax[0]),fminf(p1[1],image->pMax[1])};

      // Loop over filter support and add sample to pixel arrays

      // Precompute $x$ and $y$ filter table offsets
      int *ifx = new int[int(p1[0] - p0[0])];
      for (int x = (int)p0[0]; x < (int)p1[0]; ++x) {
          float fx = std::abs(((float)x - (float)pFilm[0]) * filter->invRadius[0] *
                                filterTableSize);
          ifx[x - (int)p0[0]] = std::min((int)std::floor(fx), filterTableSize - 1);
      }
      int *ify = new int[int(p1[1] - p0[1])];
      for (int y = (int)p0[1]; y < (int)p1[1]; ++y) {
          float fy = std::abs(((float)y - (float)pFilm[1]) * filter->invRadius[1] *
                                filterTableSize);
          ify[y - (int)p0[1]] = std::min((int)std::floor(fy), filterTableSize - 1);
      }
      for (int y = (int)p0[1]; y < (int)p1[1]; ++y) {
          for (int x = (int)p0[0]; x < (int)p1[0]; ++x) {
              // Evaluate filter value at $(x,y)$ pixel
              int offset = ify[y - (int)p0[1]] * filterTableSize + ifx[x - (int)p0[0]];
              float filterWeight = filterTable[offset];

              // Update pixel values with filtered sample contribution
              //image->addFilterWeigh(Vector2i(x,y),filterWeight);
              image->addContriSum(Vector2i(x,y),L*filterWeight);
          }
      }
  }

  void savePNG(const char *filename) { image->savePNG(filename); }

  void saveHDR(const char *filename) { image->saveHDR(filename); }

public:
  Vector2i size;
  Filter* filter;

private:
    static const int filterTableWidth = 16;
    static const int filterTableSize = 16;
    float filterTable[16*16]{};

protected:
  std::shared_ptr<Image> image = nullptr;
};