/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "Maska_chwytak.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace Maska_chwytak {

Maska_chwytak::Maska_chwytak(const std::string & name) :
		Base::Component(name) ,
		robot("robot", std::string("track")) {
	registerProperty(robot);

}

Maska_chwytak::~Maska_chwytak() {
}

void Maska_chwytak::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	// Register handlers
	h_apply_mask.setup(boost::bind(&Maska_chwytak::apply_mask, this));
	registerHandler("apply_mask", &h_apply_mask);
	addDependency("apply_mask", &in_img);

}

bool Maska_chwytak::onInit() {

	return true;
}

bool Maska_chwytak::onFinish() {
	return true;
}

bool Maska_chwytak::onStop() {
	return true;
}

bool Maska_chwytak::onStart() {
	return true;
}

void Maska_chwytak::apply_mask() {

    cv::Mat img = in_img.read().clone();
    cv::Mat mask(img.size(), CV_8UC1, cv::Scalar::all(255));

    cv::Point points[1][4];

    cout<<img.cols<<"\t"<<img.rows<<std::endl;

    points[0][0] = cv::Point(0,900);
    points[0][1] = cv::Point(1295,900);
    points[0][2] = cv::Point(1295,1031);
    points[0][3] = cv::Point(0,1031);


    const cv::Point* ppt[1] = { points[0] };
    int npt[] = { 4 };
    cv::fillPoly(mask, ppt, npt, 1, cv::Scalar::all(0), 8);
    cv::Mat new_img, new_gray, alpha;
    img.copyTo(new_img, mask);


    out_img.write(new_img);




}



} //: namespace Maska_chwytak
} //: namespace Processors
