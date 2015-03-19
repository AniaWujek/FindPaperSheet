/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "Skeleton.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace Skeleton {

Skeleton::Skeleton(const std::string & name) :
		Base::Component(name)  {

}

Skeleton::~Skeleton() {
}

void Skeleton::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	// Register handlers
	h_makeSkeleton.setup(boost::bind(&Skeleton::makeSkeleton, this));
	registerHandler("makeSkeleton", &h_makeSkeleton);
	addDependency("makeSkeleton", &in_img);

}

bool Skeleton::onInit() {

	return true;
}

bool Skeleton::onFinish() {
	return true;
}

bool Skeleton::onStop() {
	return true;
}

bool Skeleton::onStart() {
	return true;
}

void Skeleton::makeSkeleton() {


    cv::Mat img = in_img.read().clone();

    cv::threshold(img, img, 127, 255, cv::THRESH_BINARY);
    cv::Mat skel(img.size(), CV_8UC1, cv::Scalar(0));
    cv::Mat temp;
    cv::Mat eroded;

    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));

    bool done;
    do
    {
      cv::erode(img, eroded, element);
      cv::dilate(eroded, temp, element); // temp = open(img)
      cv::subtract(img, temp, temp);
      cv::bitwise_or(skel, temp, skel);
      eroded.copyTo(img);

      done = (cv::countNonZero(img) == 0);
    } while (!done);


}



} //: namespace Skeleton
} //: namespace Processors
