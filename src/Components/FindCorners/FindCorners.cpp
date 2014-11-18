/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "FindCorners.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace FindCorners {

FindCorners::FindCorners(const std::string & name) :
		Base::Component(name) , 
		prop_width("prop_width", 9), 
		prop_height("prop_height", 6) {
	registerProperty(prop_width);
	registerProperty(prop_height);

}

FindCorners::~FindCorners() {
}

void FindCorners::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_lines", &in_lines);
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	registerStream("out_gridPattern", &out_gridPattern);
	registerStream("out_imagePosition", &out_imagePosition);
	// Register handlers
	h_onNewImage.setup(boost::bind(&FindCorners::onNewImage, this));
	registerHandler("onNewImage", &h_onNewImage);
	addDependency("onNewImage", &in_img);

}

bool FindCorners::onInit() {

	return true;
}

bool FindCorners::onFinish() {
	return true;
}

bool FindCorners::onStop() {
	return true;
}

bool FindCorners::onStart() {
	return true;
}

void FindCorners::onNewImage() {
}



} //: namespace FindCorners
} //: namespace Processors
