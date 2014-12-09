/*!
 * \file
 * \brief
 * \author Anna Wujek
 */

#ifndef CREATE3DMODEL_HPP_
#define CREATE3DMODEL_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"
#include "Types/Objects3D/Object3D.hpp"

#include <opencv2/opencv.hpp>


namespace Processors {
namespace Create3DModel {

/*!
 * \class Create3DModel
 * \brief Create3DModel processor class.
 *
 *
 */
class Create3DModel: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	Create3DModel(const std::string & name = "Create3DModel");

	/*!
	 * Destructor
	 */
	virtual ~Create3DModel();

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

	boost::shared_ptr<Types::Objects3D::Object3D> sheet;


	// Input data streams
	Base::DataStreamIn<std::vector<cv::Point2f> > in_corners;

	// Output data streams
	Base::DataStreamOut<Types::Objects3D::Object3D> out_model;

	// Handlers
	Base::EventHandler2 h_createModel;

	// Properties
	Base::Property<float> width;
	Base::Property<float> height;

    void sizeCallback(int old_value, int new_value);
    void initModel();

	// Handlers
	void createModel();

};

} //: namespace Create3DModel
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("Create3DModel", Processors::Create3DModel::Create3DModel)

#endif /* CREATE3DMODEL_HPP_ */
