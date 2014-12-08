/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "ImprovedCorners.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace ImprovedCorners {

ImprovedCorners::ImprovedCorners(const std::string & name) :
		Base::Component(name) ,
		size("size", 100) {
	registerProperty(size);

}

ImprovedCorners::~ImprovedCorners() {
}

void ImprovedCorners::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("in_corners", &in_corners);
	registerStream("out_corners", &out_corners);
	// Register handlers
	h_mproveCorners.setup(boost::bind(&ImprovedCorners::improveCorners, this));
	registerHandler("improveCorners", &h_improveCorners);
	addDependency("improveCorners", &in_img);
	addDependency("improveCorners", &in_corners);

}

bool ImprovedCorners::onInit() {

	return true;
}

bool ImprovedCorners::onFinish() {
	return true;
}

bool ImprovedCorners::onStop() {
	return true;
}

bool ImprovedCorners::onStart() {
	return true;
}

void ImprovedCorners::improveCorners() {
}



} //: namespace ImprovedCorners
} //: namespace Processors
