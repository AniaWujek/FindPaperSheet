/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef APPLYCORNERMASK_HPP_
#define APPLYCORNERMASK_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace ApplyCornerMask {

/*!
 * \class ApplyCornerMask
 * \brief ApplyCornerMask processor class.
 *
 *
 */
class ApplyCornerMask: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	ApplyCornerMask(const std::string & name = "ApplyCornerMask");

	/*!
	 * Destructor
	 */
	virtual ~ApplyCornerMask();

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
	Base::DataStreamIn<std::vector<cv::Point2f>, Base::DataStreamBuffer::Newest, Base::Synchronization::Mutex > in_corners;
	Base::DataStreamIn<cv::Mat, Base::DataStreamBuffer::Newest, Base::Synchronization::Mutex> in_img;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;

	// Handlers
	Base::EventHandler2 h_apply_mask;

	// Properties


	// Handlers
	void apply_mask();

};

} //: namespace ApplyCornerMask
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("ApplyCornerMask", Processors::ApplyCornerMask::ApplyCornerMask)

#endif /* APPLYCORNERMASK_HPP_ */
