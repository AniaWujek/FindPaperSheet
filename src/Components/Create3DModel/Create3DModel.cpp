/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#include <memory>
#include <string>

#include "Create3DModel.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace Create3DModel {

Create3DModel::Create3DModel(const std::string & name) :
		Base::Component(name) ,
		width("width", 0.2),
		height("height", 0.2) {

	registerProperty(width);
	registerProperty(height);

	width.setCallback(boost::bind(&Create3DModel::sizeCallback, this, _1, _2));
	height.setCallback(boost::bind(&Create3DModel::sizeCallback, this, _1, _2));

}

Create3DModel::~Create3DModel() {
}

void Create3DModel::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_corners", &in_corners);
	registerStream("out_model", &out_model);
	// Register handlers
	h_createModel.setup(boost::bind(&Create3DModel::createModel, this));
	registerHandler("createModel", &h_createModel);
	addDependency("createModel", &in_corners);

}

bool Create3DModel::onInit() {
    initModel();
	return true;
}

void Create3DModel::initModel() {
    sheet = boost::shared_ptr<Types::Objects3D::Object3D>(new Types::Objects3D::Object3D());

    std::vector<cv::Point3f> modelPoints;

    modelPoints.push_back(cv::Point3f(0,0,0));
    modelPoints.push_back(cv::Point3f(width,0,0));
    modelPoints.push_back(cv::Point3f(0,height,0));
    modelPoints.push_back(cv::Point3f(width,height,0));

    sheet->setModelPoints(modelPoints);
}

void Create3DModel::sizeCallback(float old_val, float new_val) {
    initModel();
}

bool Create3DModel::onFinish() {
	return true;
}

bool Create3DModel::onStop() {
	return true;
}

bool Create3DModel::onStart() {
	return true;
}

void Create3DModel::createModel() {

    std::vector<cv::Point2f> corners = in_corners.read();
    sheet->setImagePoints(corners);
    out_model.write(*sheet);

    timeval curTime;
    gettimeofday(&curTime, NULL);
    int milli = curTime.tv_usec / 1000;

    char buffer [80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", localtime(&curTime.tv_sec));

    char currentTime[84] = "";
    sprintf(currentTime, "%s:%d", buffer, milli);
    std::cout<<"\n\ntime: "<<currentTime<<"\n\n";
}



} //: namespace Create3DModel
} //: namespace Processors
