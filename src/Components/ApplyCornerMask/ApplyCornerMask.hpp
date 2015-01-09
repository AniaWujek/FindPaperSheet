/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef ApplyCornerMask_HPP_
#define ApplyCornerMask_HPP_

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
	Base::DataStreamIn<cv::Mat> in_img;
	Base::DataStreamIn< std::vector<cv::Point2f> > in_corners;

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;

	// Handlers
	Base::EventHandler2 h_apply_mask_proc_corners;

	// Properties



	// Handlers

	void apply_mask_proc_corners();

};

} //: namespace ApplyCornerMask
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("ApplyCornerMask", Processors::ApplyCornerMask::ApplyCornerMask)

#endif /* ApplyCornerMask_HPP_ */
