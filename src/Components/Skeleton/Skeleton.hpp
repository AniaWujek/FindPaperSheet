/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef SKELETON_HPP_
#define SKELETON_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace Skeleton {

/*!
 * \class Skeleton
 * \brief Skeleton processor class.
 *
 *
 */
class Skeleton: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	Skeleton(const std::string & name = "Skeleton");

	/*!
	 * Destructor
	 */
	virtual ~Skeleton();

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

	// Output data streams
	Base::DataStreamOut<cv::Mat> out_img;

	// Handlers
	Base::EventHandler2 h_makeSkeleton;

	// Properties
	Base::Property<int> iterations;


	// Handlers
	void makeSkeleton();

};

} //: namespace Skeleton
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("Skeleton", Processors::Skeleton::Skeleton)

#endif /* SKELETON_HPP_ */
