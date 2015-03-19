/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef IMPROVEDCORNERS_HPP_
#define IMPROVEDCORNERS_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace ImprovedCorners {

/*!
 * \class ImprovedCorners
 * \brief ImprovedCorners processor class.
 *
 *
 */
class ImprovedCorners: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	ImprovedCorners(const std::string & name = "ImprovedCorners");

	/*!
	 * Destructor
	 */
	virtual ~ImprovedCorners();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to
	 * values set in config file.
	 */
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


	// Input data streams
	Base::DataStreamIn<cv::Mat> in_img;
	Base::DataStreamIn<std::vector<cv::Point2f> > in_corners;

	// Output data streams
	Base::DataStreamOut<std::vector<cv::Point2f> > out_corners;


	// Handlers
	Base::EventHandler2 h_improveCorners;

	// Properties
	/// Detector parameters
	Base::Property<int> blockSize;
	Base::Property<int> apertureSize;
	Base::Property<double> k;
	Base::Property<int> thresh;
	Base::Property<int> roiSize;
	Base::Property<float> qualityLevel;


	// Handlers
	void improveCorners();

};

} //: namespace ImprovedCorners
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("ImprovedCorners", Processors::ImprovedCorners::ImprovedCorners)

#endif /* IMPROVEDCORNERS_HPP_ */
