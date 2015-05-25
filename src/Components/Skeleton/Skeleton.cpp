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
		Base::Component(name),
		iterations("iterations", 0, "range")  {

		iterations.addConstraint("0");
        iterations.addConstraint("1000");
        registerProperty(iterations);

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

    //cv::threshold(img, img, 127, 255, cv::THRESH_BINARY);
    //cv::cvtColor(img,img,CV_RGB2GRAY);
    cv::Mat skel(img.size(), CV_8UC1, cv::Scalar(0));
    cv::Mat temp;
    cv::Mat eroded;
    cv::Mat subtracted;
    cv::Mat dilated;
    cv::bitwise_not ( img, img );

    cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS, cv::Size(3, 3));

    cv::Mat myElement1 = (cv::Mat_<bool>(3, 3) <<
	              0, 0, 0,
	              1, 1, 1,
	              1, 1, 1);
    cv::Mat myElement2 = (cv::Mat_<bool>(3, 3) <<
	              1, 1, 0,
	              1, 1, 0,
	              1, 1, 0);
    cv::Mat myElement3 = (cv::Mat_<bool>(3, 3) <<
	              1, 1, 1,
	              1, 1, 1,
	              0, 0, 0);
    cv::Mat myElement4 = (cv::Mat_<bool>(3, 3) <<
	              0, 1, 1,
	              0, 1, 1,
	              0, 1, 1);

    bool done;
    for(int i = 0; i < iterations; ++i)
    {
      /*cv::erode(img, eroded, element);
      cv::dilate(eroded, temp, element); // temp = open(img)
      cv::subtract(img, temp, temp);
      cv::bitwise_or(skel, temp, skel);
      eroded.copyTo(img);*/

      cv::morphologyEx(img, temp, cv::MORPH_OPEN, element);
      cv::bitwise_not(temp, temp);
      cv::bitwise_and(img, temp, temp);
      cv::bitwise_or(skel, temp, skel);
      cv::erode(img, img, element);

      double max;
      cv::minMaxLoc(img, 0, &max);
      done = (max == 0);




    }

    cv::bitwise_not ( skel, skel );
    out_img.write(skel);


}



} //: namespace Skeleton
} //: namespace Processors
