/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef FINDCORNERS_HPP_
#define FINDCORNERS_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"
#include "Types/Objects3D/GridPattern.hpp"
#include "Types/ImagePosition.hpp"
#include <opencv2/opencv.hpp>


namespace Processors {
namespace FindCorners {

/*!
 * \class FindCorners
 * \brief FindCorners processor class.
 *
 *
 */
class FindCorners: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	FindCorners(const std::string & name = "FindCorners");

	/*!
	 * Destructor
	 */
	virtual ~FindCorners();

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
	Base::DataStreamIn< vector<cv::Vec4i> > in_lines;

	// Output data streams
	Base::DataStreamOut<Types::Objects3D::GridPattern> out_gridPattern;
	Base::DataStreamOut<Types::ImagePosition> out_imagePosition;

	// Handlers
	Base::EventHandler2 h_onNewImage;

	// Properties
	Base::Property<int> prop_width;
	Base::Property<int> prop_height;


	// Handlers
	void onNewImage();

};

} //: namespace FindCorners
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("FindCorners", Processors::FindCorners::FindCorners)

#endif /* FINDCORNERS_HPP_ */
