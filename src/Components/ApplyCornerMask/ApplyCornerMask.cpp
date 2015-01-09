/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "ApplyCornerMask.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace ApplyCornerMask {

ApplyCornerMask::ApplyCornerMask(const std::string & name) :
		Base::Component(name)  {

}

ApplyCornerMask::~ApplyCornerMask() {
}

void ApplyCornerMask::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("in_corners", &in_corners);
	registerStream("out_img", &out_img);
	// Register handlers
	h_applyMask.setup(boost::bind(&ApplyCornerMask::applyMask, this));
	registerHandler("applyMask", &h_applyMask);
	addDependency("applyMask", &in_img);
	addDependency("applyMask", &in_corners);

}

bool ApplyCornerMask::onInit() {

	return true;
}

bool ApplyCornerMask::onFinish() {
	return true;
}

bool ApplyCornerMask::onStop() {
	return true;
}

bool ApplyCornerMask::onStart() {
	return true;
}

void ApplyCornerMask::applyMask() {
    cv::Mat img = in_img.read().clone();

    out_img.write(img);
}



} //: namespace ApplyCornerMask
} //: namespace Processors
