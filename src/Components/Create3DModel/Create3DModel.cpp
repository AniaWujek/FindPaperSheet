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
		width("width", 10),
		height("height", 20) {
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
	registerStream("out_Model", &out_Model);
	// Register handlers
	h_OnNewImage.setup(boost::bind(&Create3DModel::OnNewImage, this));
	registerHandler("OnNewImage", &h_OnNewImage);
	addDependency("OnNewImage", &in_corners);

}

bool Create3DModel::onInit() {

	return true;
}

bool Create3DModel::onFinish() {
	return true;
}

bool Create3DModel::onStop() {
	return true;
}

bool Create3DModel::onStart() {
    vector <cv::Point3f> modelPoints;

    gridPattern = boost::shared_ptr <Types::Objects3D::Object3D>(new Types::Objects3D::Object3D());

    modelPoints.push_back(cv::Point3f(0,0,0));
    modelPoints.push_back(cv::Point3f(float(width),0,0));
    modelPoints.push_back(cv::Point3f(float(width),float(height),0));
    modelPoints.push_back(cv::Point3f(0,float(height),0));

	// Set model points.
	gridPattern->setModelPoints(modelPoints);
	return true;
}

void Create3DModel::initGridPattern() {
    vector <cv::Point3f> modelPoints;

    gridPattern = boost::shared_ptr <Types::Objects3D::Object3D>(new Types::Objects3D::Object3D());

    modelPoints.push_back(cv::Point3f(0,0,0));
    modelPoints.push_back(cv::Point3f(float(width),0,0));
    modelPoints.push_back(cv::Point3f(float(width),float(height),0));
    modelPoints.push_back(cv::Point3f(0,float(height),0));

	// Set model points.
	gridPattern->setModelPoints(modelPoints);
}

void Create3DModel::sizeCallback(int old_value, int new_value) {
	initGridPattern();
}

void Create3DModel::OnNewImage() {

    std::vector<cv::Point2f> corners = in_corners.read();

    gridPattern->setImagePoints(corners);
    out_Model.write(*gridPattern);
}



} //: namespace Create3DModel
} //: namespace Processors
