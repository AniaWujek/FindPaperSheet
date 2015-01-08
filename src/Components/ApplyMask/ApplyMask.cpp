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
		Base::Component(name) ,
		type("type", 1) {
	registerProperty(type);

}

ApplyMask::~ApplyMask() {
}

void ApplyMask::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("out_img", &out_img);
	registerStream("in_corners", &in_corners);
	// Register handlers
	h_apply_mask_proc.setup(boost::bind(&ApplyMask::apply_mask_proc, this));
	registerHandler("apply_mask_proc", &h_apply_mask_proc);
	addDependency("apply_mask_proc", &in_img);

	h_apply_mask_proc_corners.setup(boost::bind(&ApplyMask::apply_mask_proc_corners, this));
	registerHandler("apply_mask_proc_corners", &h_apply_mask_proc_corners);
	addDependency("apply_mask_proc_corners", &in_corners);
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

    cv::Mat img = in_img.read().clone();

    if(type == 1) {
        //maska na chwytak
        cv::Mat mask(img.size(), CV_8UC1, cv::Scalar::all(255));
        mask(cv::Rect(200,800,1000,232)).setTo(cv::Scalar::all(0));
        cv::Mat masked;
        img.copyTo(masked, mask);
        out_img.write(masked);
    }
}

void ApplyMask::apply_mask_proc_corners() {

    cv::Mat img = in_img.read().clone();


    /*if(type == 2) {
        //maska dla kartki
        std::vector<cv::Point2f> corners = in_corners.read();
        if(corners.size() == 4) {
            cv::Mat mask(img.size(), CV_8UC1, cv::Scalar::all(0));
            cv::Point points[0][4];
            for(int i = 0; i < 4; ++i) {
                points[0][i] = corners[i];
            }
            const cv::Point* ppt[1] = {points[0]};
            int npt[] = {4};

            cv::fillPoly(mask, ppt, npt, 1, cv::Scalar::all(255), 8);
            cv::Mat masked;
            img.copyTo(masked, mask);
            out_img.write(masked);
        }

    }*/
    out_img.write(img);

}



} //: namespace ApplyMask
} //: namespace Processors
