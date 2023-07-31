#pragma once

#include "NDF.h"

class BeckmannDistribution : public NDF {
public:
  BeckmannDistribution() noexcept = default;
  virtual ~BeckmannDistribution() noexcept = default;
  virtual float getD(const Vector3f &whLocal,
                     const Vector2f &alpha) const noexcept override {
    // TODO
    // 根据公式即可
    float cosineTheta =whLocal[1];
    float squaretanTheta = (1 - cosineTheta*cosineTheta) / (cosineTheta*cosineTheta);
    float squarealpha=alpha[0]*alpha[0];
    return powf(M_E, -squaretanTheta/squarealpha) /(PI * squarealpha * powf(cosineTheta, 4));
  }
  // tips:
  // float getG1(...) {}
  float getG1(const Vector3f& wlocal,
              const Vector2f& alpha) const noexcept{
      float cosineTheta = wlocal[1];
      float a = 1 / (alpha[0] * sqrtf(1 - cosineTheta*cosineTheta) / cosineTheta);
      return a < 1.6 ? ((3.535f * a + 2.181f * powf(a, 2)))/ (1 + 2.276f * a + 2.577f* powf(a, 2)):1;
  }
  virtual float getG(const Vector3f &woLocal, const Vector3f &wiLocal,
                     const Vector2f &alpha) const noexcept override {
    // TODO
    // 根据公式即可
    // tips: return getG1(wo) * getG1(wi);
    return getG1(woLocal,alpha)* getG1(wiLocal,alpha);
  }
  virtual float pdf(const Vector3f &woLocal, const Vector3f &whLocal,
                    const Vector2f &alpha) const noexcept override {
    return getD(whLocal, alpha) * whLocal[1];
  }
  virtual Vector3f sampleWh(const Vector3f &woLocal, const Vector2f &alpha,
                            const Vector2f &sample) const noexcept override {
    float a = alpha[0];
    float tan_theta_2 = -std::log(1 - sample[0]) * a * a;
    float phi = sample[1] * 2 * PI;

    float cos_theta = std::sqrt(1.f / (1.f + tan_theta_2));
    float sin_theta = std::sqrt(1.f - cos_theta * cos_theta);
    return {sin_theta * std::cos(phi), sin_theta * std::sin(phi), cos_theta};
  }
};