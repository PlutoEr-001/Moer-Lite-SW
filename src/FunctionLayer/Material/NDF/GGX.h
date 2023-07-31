#pragma once

#include "NDF.h"

class GGXDistribution : public NDF {
public:
  GGXDistribution() noexcept = default;
  virtual ~GGXDistribution() noexcept = default;
  virtual float getD(const Vector3f &whLocal,
                     const Vector2f &alpha) const noexcept override {
    // TODO
    // 根据公式即可
    float squarealpha=alpha[0]*alpha[0],squarecosineTheta=whLocal[1]*whLocal[1];
    float squaretanTheta=(1-squarecosineTheta)/squarecosineTheta;
    return squarealpha/(PI*squarecosineTheta*squarecosineTheta*powf(squarealpha+squaretanTheta,2));
  }
  // tips:
  // float getG1(...) {}
  float getG1(const Vector3f& wlocal,
              const Vector2f& alpha) const noexcept{
      float squarecosineTheta = wlocal[1]*wlocal[1];
      float temp = sqrtf(1+ alpha[0]*alpha[0] *(1 - squarecosineTheta) /squarecosineTheta);
      return 2/(1+temp);
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
    float tan_theta_2 = a * a * sample[0] / (1.f - sample[0]);
    float phi = sample[1] * 2 * PI;

    float cos_theta = std::sqrt(1.f / (1.f + tan_theta_2));
    float sin_theta = std::sqrt(1.f - cos_theta * cos_theta);
    return {sin_theta * std::cos(phi), sin_theta * std::sin(phi), cos_theta};
  }
};