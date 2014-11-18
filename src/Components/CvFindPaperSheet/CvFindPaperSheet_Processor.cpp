/*
 * CvFindPaperSheet_Processor.cpp
 *
 *  Created on: 29-04-2014
 *      Author: lzmuda
 */

#include "CvFindPaperSheet_Processor.hpp"
#include <boost/bind.hpp>

namespace Processors {

namespace CvFindPaperSheet {

using namespace std;
using namespace boost;
using namespace cv;
using namespace Types::Objects3D;
static int counter= 0;

CvFindPaperSheet_Processor::CvFindPaperSheet_Processor(const std::string & name) :
	Component(name),

	prop_width("grid.width", 9),
	prop_height("grid.height", 6),
	prop_size("grid.size", 1),
	prop_inverse("image.inverse",false),

	prop_interpolation_type("scale.interpolation_type", INTER_NEAREST, "combo")
{
	registerProperty(prop_width);
	registerProperty(prop_height);
	registerProperty(prop_size);
	registerProperty(prop_inverse);

    prop_width.setCallback(boost::bind(&CvFindPaperSheet_Processor::sizeCallback, this, _1, _2));
    prop_height.setCallback(boost::bind(&CvFindPaperSheet_Processor::sizeCallback, this, _1, _2));

	prop_interpolation_type.setToolTip("Interpolation type");
	PROP_ADD_COMBO_ITEMS(prop_interpolation_type, ELEMS);
	registerProperty(prop_interpolation_type);
}

CvFindPaperSheet_Processor::~CvFindPaperSheet_Processor()
{
}

void CvFindPaperSheet_Processor::prepareInterface() {
    CLOG(LTRACE) << "CvFindPaperSheet_Processor::prepareInterface\n";

	// Register data streams.
	registerStream("in_img", &in_img);
	registerStream("out_pattern", &out_gridPattern);
	registerStream("out_imagePosition", &out_imagePosition);
	registerStream("out_img", &out_img);

	// Register handler responsible for finding grid pattern.
    registerHandler("onNewImage", boost::bind(&CvFindPaperSheet_Processor::onNewImage, this));
	addDependency("onNewImage", &in_img);
}



bool CvFindPaperSheet_Processor::onFinish()
{
	return true;
}

bool CvFindPaperSheet_Processor::onStop()
{
	return true;
}

bool CvFindPaperSheet_Processor::onInit()
{
	initGridPattern();

	CLOG(LTRACE) << "component initialized\n";
	return true;
}

void CvFindPaperSheet_Processor::initGridPattern() {
    CLOG(LINFO) << "CvFindPaperSheet_Processor: width: " << prop_width;
    CLOG(LINFO) << "CvFindPaperSheet_Processor: height: " << prop_height;
    CLOG(LINFO) << "CvFindPaperSheet_Processor: size: " << prop_size;

	// Create grid object.
	gridPattern = boost::shared_ptr <GridPattern>(new GridPattern(cv::Size(prop_width, prop_height)));

	// Initialize modelPoints - localization of the grid points in Cartesian space.
	vector <Point3f> modelPoints;

    modelPoints.push_back(Point3f(0,0,0));
    modelPoints.push_back(Point3f(0,float(prop_height),0));
    modelPoints.push_back(Point3f(float(prop_width),0,0));
    modelPoints.push_back(Point3f(float(prop_width),float(prop_height),0));



	// Set model points.
	gridPattern->setModelPoints(modelPoints);
	CLOG(LWARNING) << gridPattern->getModelPoints();
}

void CvFindPaperSheet_Processor::sizeCallback(int old_value, int new_value) {
	initGridPattern();
}


bool CvFindPaperSheet_Processor::onStart()
{
	return true;
}

bool CvFindPaperSheet_Processor::onStep()
{
	return true;
}



void CvFindPaperSheet_Processor::onNewImage()
{
    CLOG(LTRACE) << "void CvFindPaperSheet_Processor::onNewImage() begin\n";
	try {
		if(in_img.empty()){
			return;
		}
		// Retrieve image from the stream.
		Mat image = in_img.read().clone();

		if(prop_inverse){
			image =  cv::Scalar::all(255) - image;
		}

		bool found = false;

		// Initialize grid size.
		cv::Size gridSize(prop_width, prop_height);

        //found = findCirclesGrid(image, gridSize, gridPoints, CALIB_CB_ASYMMETRIC_GRID|CALIB_CB_CLUSTERING);



        //found = findPaperSheet(image, gridSize);

		// check if found, if not-invert colors and try again
		if(found){
			//LOG(LWARNING)<<"Dots found!!!\n\n\n";
			gridPattern->setImagePoints(gridPoints);
			out_gridPattern.write(*gridPattern);

		} else {
			CLOG(LWARNING) << "Pattern not found\n";
			// TODO: add unit type: not found
		}
		out_img.write(image);
	} catch (const Exception& e) {
		CLOG(LERROR) << e.what() << "\n";
	}



    LOG(LTRACE) << "void CvFindPaperSheet_Processor::onNewImage() end\n";
}

} // namespace CvFindPaperSheet{
} // namespace Processors {
