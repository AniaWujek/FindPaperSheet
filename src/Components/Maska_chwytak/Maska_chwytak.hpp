/*!
 * \file
 * \brief 
 * \author Anna Wujek
 */

#ifndef MASKA_CHWYTAK_HPP_
#define MASKA_CHWYTAK_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace Maska_chwytak {

/*!
 * \class Maska_chwytak
 * \brief Maska_chwytak processor class.
 *
 * 
 */
class Maska_chwytak: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	Maska_chwytak(const std::string & name = "Maska_chwytak");

	/*!
	 * Destructor
	 */
	virtual ~Maska_chwytak();

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
	Base::EventHandler2 h_apply_mask;

	// Properties
	Base::Property<std::string> robot;

	
	// Handlers
	void apply_mask();

};

} //: namespace Maska_chwytak
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("Maska_chwytak", Processors::Maska_chwytak::Maska_chwytak)

#endif /* MASKA_CHWYTAK_HPP_ */
