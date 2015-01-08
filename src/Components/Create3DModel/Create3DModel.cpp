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
#include <time.h>

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
    if(corners.size() == 4) {
        sheet->setImagePoints(corners);
        out_model.write(*sheet);
    }





}



} //: namespace Create3DModel
} //: namespace Processors
