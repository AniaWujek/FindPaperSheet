/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "ApplyMask.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace ApplyMask {

ApplyMask::ApplyMask(const std::string & name) :
		Base::Component(name) {

}

ApplyMask::~ApplyMask() {
}

void ApplyMask::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	// Register handlers
	h_apply_mask_proc.setup(boost::bind(&ApplyMask::apply_mask_proc, this));
	registerHandler("apply_mask_proc", &h_apply_mask_proc);
	addDependency("apply_mask_proc", &in_img);




}

bool ApplyMask::onInit() {

	return true;
}

bool ApplyMask::onFinish() {
	return true;
}

bool ApplyMask::onStop() {
	return true;
}

bool ApplyMask::onStart() {
	return true;
}

void ApplyMask::apply_mask_proc() {



        //maska na chwytak
        cv::Mat img = in_img.read().clone();

        cv::Mat mask(img.size(), CV_8UC1, cv::Scalar::all(255));
        mask(cv::Rect(200,800,1000,232)).setTo(cv::Scalar::all(0));
        cv::Mat masked;
        img.copyTo(masked, mask);
        out_img.write(masked);

}






} //: namespace ApplyMask
} //: namespace Processors
