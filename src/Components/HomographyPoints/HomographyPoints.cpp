/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "HomographyPoints.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace HomographyPoints {

HomographyPoints::HomographyPoints(const std::string & name) :
		Base::Component(name) ,
		width("width", 0.21),
		height("height", 0.297) {
	registerProperty(width);
	registerProperty(height);

}

HomographyPoints::~HomographyPoints() {
}

void HomographyPoints::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_corners", &in_corners);
	registerStream("in_points", &in_points);
	registerStream("out_points", &out_points);
	// Register handlers
	registerHandler("findHomography_proc", boost::bind(&HomographyPoints::findHomography_proc, this));
	addDependency("findHomography_proc", &in_corners);
	addDependency("findHomography_proc", &in_points);

}

bool HomographyPoints::onInit() {

	return true;
}

bool HomographyPoints::onFinish() {
	return true;
}

bool HomographyPoints::onStop() {
	return true;
}

bool HomographyPoints::onStart() {
	return true;
}

void HomographyPoints::findHomography_proc() {

    std::vector<cv::Point2f> corners = in_corners.read();
    std::vector<std::vector<cv::Point> > points = in_points.read();
    std::vector<float> proxyPoints;

    std::vector<cv::Point2f> good_corners;
    good_corners.push_back(cv::Point2f(0,0));
    good_corners.push_back(cv::Point2f(width,0));
    good_corners.push_back(cv::Point2f(0,height));
    good_corners.push_back(cv::Point2f(width,height));

    if(corners.size() == 4) {
        cv::Mat homoMatrix = cv::findHomography(corners, good_corners, 0, 3, cv::noArray());
        //CLOG(LNOTICE) << "Homohomohomo "<< homoMatrix;
        cv::Mat temp;


        for(int i = 0; i < points.size(); ++i) {

            proxyPoints.push_back((float)points[i].size());

            for(int j = 0; j < points[i].size(); ++j) {
                temp = (cv::Mat_<double>(3, 1) <<
			            points[i][j].x,
				        points[i][j].y,
			            1);
                temp = homoMatrix * temp;
                proxyPoints.push_back(temp.at<double>(0,0));
                proxyPoints.push_back(temp.at<double>(1,0));
                suma++;

            }

        }

        out_points.write(proxyPoints);

    }



}



} //: namespace HomographyPoints
} //: namespace Processors
