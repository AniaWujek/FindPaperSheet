/*!
 * \file
 * \brief
 */

#ifndef CvHoughLinesImage_PROCESSOR_HPP_
#define CvHoughLinesImage_PROCESSOR_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "Types/Line.hpp"
#include "Types/DrawableContainer.hpp"

#include <opencv2/core/core.hpp>
using namespace cv;

namespace Processors {
namespace CvHoughLinesImage {

struct lineParams {
        bool pozioma;
        bool pionowa;
        float A;
        float b;
	} LineParams;
/*!
 * \class CvHoughLinesImage_Processor
 * \brief CvHoughLinesImage processor class.
 */
class CvHoughLinesImage_Processor: public Base::Component
{
public:
	/*!
	 * Constructor.
	 */
	CvHoughLinesImage_Processor(const std::string & name = "");

	/*!
	 * Destructor
	 */
	virtual ~CvHoughLinesImage_Processor();

	void prepareInterface();



protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();

private:
	Base::Property<int> threshold;
	Base::Property<double> minLineLength;
	Base::Property<double> maxLineGap;

	/** Image stream. */
	Base::DataStreamIn <cv::Mat> in_img;

	Base::DataStreamOut <Types::DrawableContainer> out_linesDrawable;
	Base::DataStreamOut < vector<cv::Vec4i> > out_lines;

	void onNewImage();
};

}//: namespace CvHoughLinesImage
}//: namespace Processors


/*
 * Register processor component.
 */
REGISTER_COMPONENT("CvHoughLinesImage", Processors::CvHoughLinesImage::CvHoughLinesImage_Processor)

#endif /* CvHoughLinesImage_PROCESSOR_HPP_ */
