/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef ROI_HPP_
#define ROI_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace ROI {

/*!
 * \class ROI
 * \brief ROI processor class.
 *
 *
 */
class ROI: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	ROI(const std::string & name = "ROI");

	/*!
	 * Destructor
	 */
	virtual ~ROI();

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
	Base::DataStreamIn< std::vector<cv::Point2f> > in_corners;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_corner1;
	Base::DataStreamOut<cv::Mat> out_corner2;
	Base::DataStreamOut<cv::Mat> out_corner3;
	Base::DataStreamOut<cv::Mat> out_corner4;

	// Handlers
	Base::EventHandler2 h_findRoi;

	// Properties
	Base::Property<int> roiSize;


	// Handlers
	void findRoi();

};

} //: namespace ROI
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("ROI", Processors::ROI::ROI)

#endif /* ROI_HPP_ */
