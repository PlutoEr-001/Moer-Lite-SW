/********************************************************************************
* @author: plutoEr$
* @date: 2023/7/25 20:35
* @version: 1.0
* @description: 
********************************************************************************/
#include "Film.h"

Film::Film(const Json &json) {
    size = fetchRequired<Vector2i>(json, "size");
    image = std::make_shared<Image>(size);
    filter = CreateGaussianFilter(json);
    int offset = 0;
    for (int y = 0; y < filterTableWidth; ++y) {
        for (int x = 0; x < filterTableWidth; ++x, ++offset) {
            Point2f p;
            p[0] = ((float)x + 0.5f) * filter->radius[0]/ filterTableWidth;
            p[1] = ((float)y + 0.5f) * filter->radius[1] / filterTableWidth;
            filterTable[offset] = filter->Evaluate(p);
        }
    }
}
