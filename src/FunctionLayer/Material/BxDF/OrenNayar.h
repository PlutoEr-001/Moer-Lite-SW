#pragma once
#include "BSDF.h"
#include "Warp.h"

class OrenNayarBSDF : public BSDF {
public:
  OrenNayarBSDF(const Vector3f &_normal, const Vector3f &_tangent,
                const Vector3f &_bitangent, Spectrum _albedo, float _sigma)
      : BSDF(_normal, _tangent, _bitangent), albedo(_albedo), sigma(_sigma) {}

  virtual Spectrum f(const Vector3f &wo, const Vector3f &wi) const override {
    // TODO
    // 1. 转换坐标系到局部坐标
    // 2. 计算 A, B, \alpha, \beta（可以直接求\sin\alpha,\tan\beta）,
    // \cos(\phi_i-\phi_o)
    // 3. return Oren-Nayar brdf
    auto local_wo= normalize(toLocal(wo)),local_wi= normalize(toLocal(wi));
    float phi_o= atan2f(local_wo[2],local_wo[0]),phi_i= atan2f(local_wi[2],local_wi[0]);
    float sinalpha= sqrtf(1-powf(fmaxf(local_wi[1],local_wo[1]),2));
    float cosinebeta= fminf(local_wo[1],local_wi[1]);
    float square_cosinebeta=cosinebeta*cosinebeta;
    float tanbeta=sqrtf((1-square_cosinebeta))/cosinebeta;
    float sigma_square=sigma*sigma;
    float a=1.0f-sigma_square/(2*(sigma_square+0.33f));
    float b=0.45f*sigma_square/(sigma_square+0.09f);
    Spectrum res=albedo*INV_PI*(a+b*fmaxf(0.0, cosf((phi_i-phi_o)))*sinalpha*tanbeta)*local_wi[1];
    return res;
  }
  virtual BSDFSampleResult sample(const Vector3f &wo,
                                  const Vector2f &sample) const override {
    Vector3f wi = squareToCosineHemisphere(sample);
    float pdf = squareToCosineHemispherePdf(wi);
    return {albedo, toWorld(wi), pdf, BSDFType::Diffuse};
  }

private:
  Spectrum albedo;
  float sigma;
};