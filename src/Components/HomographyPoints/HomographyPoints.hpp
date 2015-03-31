/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef HOMOGRAPHYPOINTS_HPP_
#define HOMOGRAPHYPOINTS_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace HomographyPoints {

/*!
 * \class HomographyPoints
 * \brief HomographyPoints processor class.
 *
 *
 */
class HomographyPoints: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	HomographyPoints(const std::string & name = "HomographyPoints");

	/*!
	 * Destructor
	 */
	virtual ~HomographyPoints();

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
	Base::DataStreamIn<std::vector<cv::Point2f> > in_corners;
	Base::DataStreamIn<std::vector<std::vector<cv::Point> > > in_points;

	// Output data streams
	Base::DataStreamOut<std::vector<std::vector<cv::Point> > > out_points;

	// Handlers

	// Properties
	Base::Property<float> width;
	Base::Property<float> height;


	// Handlers
	void findHomography_proc();

};

} //: namespace HomographyPoints
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("HomographyPoints", Processors::HomographyPoints::HomographyPoints)

#endif /* HOMOGRAPHYPOINTS_HPP_ */
