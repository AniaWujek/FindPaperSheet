

#ifndef CONTOURS_ARRAY_HPP_
#define CONTOURS_ARRAY_HPP_

#include <opencv2/core/core.hpp>

namespace Types {

class Contoursarray {

    public:
        Contoursarray(){}

        void addContour(std::vector<cv::Point> contour) {
            contours.push_back(contour);
        }

        std::vector<std::vector<cv::Point> > contours;

};

} //: namespace Types

#endif /* CONTOURS_ARRAY_HPP_ */
