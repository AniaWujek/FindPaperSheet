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
		Base::Component(name) {

}

ApplyCornerMask::~ApplyCornerMask() {
}

void ApplyCornerMask::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	registerStream("in_corners", &in_corners);
	// Register handlers

	h_apply_mask_proc_corners.setup(boost::bind(&ApplyCornerMask::apply_mask_proc_corners, this));
	registerHandler("apply_mask_proc_corners", &h_apply_mask_proc_corners);
	addDependency("apply_mask_proc_corners", &in_corners);
	addDependency("apply_mask_proc_corners", &in_img);


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


void ApplyCornerMask::apply_mask_proc_corners() {




        cv::Mat img = in_img.read().clone();
        std::cout<<"\n corner mask \n"<<img.size()<<"\n";
        //maska dla kartki
        /*std::vector<cv::Point2f> corners = in_corners.read();
        if(corners.size() == 4) {
            cv::Mat mask(img.size(), CV_8UC1, cv::Scalar::all(0));
            cv::Point points[1][4];
            for(int i = 0; i < 4; ++i) {
                points[0][i] = cv::Point(corners[i].x, corners[i].y);
            }
            const cv::Point* ppt[1] = {points[0]};
            int npt[] = {4};

            cv::fillPoly(mask, ppt, npt, 1, cv::Scalar::all(255), 8);
            cv::Mat masked;
            img.copyTo(masked, mask);
            out_img.write(masked);
        }*/
        out_img.write(img);




}



} //: namespace ApplyCornerMask
} //: namespace Processors
