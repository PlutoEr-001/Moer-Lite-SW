/********************************************************************************
* @author: plutoEr$
* @date: 2023/7/25 11:16
* @version: 1.0
* @description: 
********************************************************************************/


#include "Filter.h"

Filter::~Filter() {}

/***/

float GaussianFilter::Evaluate(/***/const Point2f &p) const {
    return Gaussian(p[0], expX) * Gaussian(p[1], expY);
}

GaussianFilter *CreateGaussianFilter(const Json &json) {
    // Find common filter parameters
    float xw = fetchOptional(json, "xwidth", .8f);
    float yw = fetchOptional(json, "ywidth", .8f);
    float alpha = fetchOptional(json, "alpha", 3.f);
    return new GaussianFilter(Vector2f(xw, yw), alpha);
}
