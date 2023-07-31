/********************************************************************************
* @author: plutoEr$
* @date: 2023/7/25 11:16
* @version: 1.0
* @description: 
********************************************************************************/

#pragma once
#ifndef MOER_LITE_FILTER_H
#define MOER_LITE_FILTER_H
#include <ResourceLayer/JsonUtil.h>
#include "CoreLayer/Math/Geometry.h"
class Filter {
public:
    // Filter Interface
    virtual ~Filter();
    Filter(const Vector2f &radius)
            : radius(radius), invRadius(Vector2f(1 / radius[0], 1 / radius[1])) {}
    virtual float Evaluate(const Point2f &p) const = 0;

    // Filter Public Data
    const Vector2f radius, invRadius;
};

class GaussianFilter : public Filter {
public:
    // GaussianFilter Public Methods
    GaussianFilter(const Vector2f &radius, float alpha)
            : Filter(radius),
              alpha(alpha),
              expX(std::exp(-alpha * radius[0] * radius[0])),
              expY(std::exp(-alpha * radius[1] * radius[1])) {}
    float Evaluate(const Point2f &p) const;

private:
    // GaussianFilter Private Data
    const float alpha;
    const float expX, expY;

    // GaussianFilter Utility Functions
    float Gaussian(float d, float expv) const {
        return std::max((float)0, float(std::exp(-alpha * d * d) - expv));
    }
};
GaussianFilter *CreateGaussianFilter(const Json &json);
#endif //MOER_LITE_FILTER_H
