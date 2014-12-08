/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "ROI.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace ROI {

ROI::ROI(const std::string & name) :
		Base::Component(name),
		roiSize("roiSize", 100, "range")  {

		roiSize.addConstraint("1");
		roiSize.addConstraint("1000");
		registerProperty(roiSize);

}

ROI::~ROI() {
}

void ROI::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_img", &in_img);
	registerStream("in_corners", &in_corners);
	registerStream("out_corner1", &out_corner1);
	registerStream("out_corner2", &out_corner2);
	registerStream("out_corner3", &out_corner3);
	registerStream("out_corner4", &out_corner4);
	// Register handlers
	h_findRoi.setup(boost::bind(&ROI::findRoi, this));
	registerHandler("findRoi", &h_findRoi);
	addDependency("findRoi", &in_img);
	addDependency("findRoi", &in_corners);

}

bool ROI::onInit() {

	return true;
}

bool ROI::onFinish() {
	return true;
}

bool ROI::onStop() {
	return true;
}

bool ROI::onStart() {
	return true;
}

void ROI::findRoi() {

    cv::Mat image = in_img.read().clone();
    std::vector<cv::Point2f> corners = in_corners.read();
    double maxX = (float)image.cols;
    double maxY = (float)image.rows;
    std::vector<cv::Mat> rois;

    cv::Mat roi1, roi2, roi3, roi4;
    for(int i = 0; i < corners.size() && i < 4; ++i) {
        float px = max(corners[i].x - roiSize / 2.0, 0.0);
        if(px > maxX) {
            px = maxX;
        }
        if(px < 0) {
            px = 0;
        }
        float py = max(corners[i].y - roiSize / 2.0, 0.0);
        if(py > maxY) {
            py = maxY;
        }
        if(py < 0) {
            py = 0;
        }
        float kx = roiSize;
        if(px + kx > maxX) {
            kx = maxX - px;
        }

        float ky = roiSize;
        if(py + ky > maxY) {
            ky = maxY - py;
        }
        std::cout<<"dim: "<<px<<"\t"<<py<<"\t"<<kx<<"\t"<<ky<<std::endl;
        cv::Mat oneRoi = image(cv::Rect(px,py,kx,ky));
        rois.push_back(oneRoi);
    }

    for(int i = 0; i < rois.size(); ++i) {
        if(i == 0) out_corner1.write(rois[i]);
        else if(i == 1) out_corner2.write(rois[i]);
        else if(i == 2) out_corner3.write(rois[i]);
        else if(i == 3) out_corner4.write(rois[i]);
    }


}



} //: namespace ROI
} //: namespace Processors
