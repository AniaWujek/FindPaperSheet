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
		blockSize("blockSize", 5),
		apertureSize("apertureSize", 3),
		k("k", 0.04),
		thresh("thresh", 254, "range"),
		roiSize("roisize", 100, "range"),
		qualityLevel("qualityLevel", 0.01) {

	// Constraints.
	thresh.addConstraint("0");
	thresh.addConstraint("255");

	roiSize.addConstraint("1");
	roiSize.addConstraint("1000");

	// Register properties.
	registerProperty(blockSize);
	registerProperty(apertureSize);
	registerProperty(k);
	registerProperty(thresh);
    registerProperty(qualityLevel),
    registerProperty(roiSize);


}

ImprovedCorners::~ImprovedCorners() {
}

void ImprovedCorners::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("in_corners", &in_corners);
	registerStream("out_corners", &out_corners);
	// Register handlers
	h_improveCorners.setup(boost::bind(&ImprovedCorners::improveCorners, this));
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

    cv::Mat image = in_img.read().clone();
    std::vector<cv::Point2f> corners = in_corners.read();
    double maxX = (float)image.cols;
    double maxY = (float)image.rows;
    std::vector<cv::Mat> rois;
    std::vector<float> x;
    std::vector<float> y;

    cv::Mat roi1, roi2, roi3, roi4;
    for(int i = 0; i < corners.size() && i < 4; ++i) {
        float px = max(corners[i].x - roiSize / 2.0, 0.0);
        if(px >= maxX) {
            px = maxX-1;
        }
        if(px < 0) {
            px = 0;
        }
        float py = max(corners[i].y - roiSize / 2.0, 0.0);
        if(py >= maxY) {
            py = maxY-1;
        }
        if(py < 0) {
            py = 0;
        }
        float kx = roiSize;
        if(px + kx >= maxX) {
            kx = maxX - px - 1;
        }

        float ky = roiSize;
        if(py + ky >= maxY) {
            ky = maxY - py - 1;
        }

        cv::Mat oneRoi = image(cv::Rect(px,py,kx,ky));
        x.push_back(px);
        y.push_back(py);
        rois.push_back(oneRoi);
    }

    std::vector<cv::Point2f> better_corners;
    for(int i = 0; i < rois.size(); ++i) {
        std::vector<cv::Point2f> temp;
        goodFeaturesToTrack(rois[i], temp, 2, qualityLevel, 10, cv::Mat(), blockSize, false, k);
        if(temp.size() > 0 ) {
            temp[0].x+=x[i];
            temp[0].y+=y[i];
            better_corners.push_back(temp[0]);
        }
        else better_corners.push_back(corners[i]);
    }
    out_corners.write(better_corners);
}



} //: namespace ImprovedCorners
} //: namespace Processors
