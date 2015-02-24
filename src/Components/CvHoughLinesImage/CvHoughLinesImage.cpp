/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include "CvHoughLinesImage.hpp"
#include "Common/Logger.hpp"

#include <opencv2/imgproc/imgproc.hpp>

#include "Types/DrawableContainer.hpp"
#include "Types/Line.hpp"
#include <math.h>

namespace Processors {
namespace CvHoughLinesImage {

using namespace cv;
using namespace std;

CvHoughLinesImage_Processor::CvHoughLinesImage_Processor(const std::string & name) :
	Base::Component(name),
	threshold("threshold", 80, "range"),
	minLineLength("minLineLength", 30, "range"),
	maxLineGap("maxLineGap", 10, "range")
{
	threshold.addConstraint("1");
	threshold.addConstraint("1000");
	registerProperty(threshold);

	minLineLength.addConstraint("0");
	minLineLength.addConstraint("1000");
	registerProperty(minLineLength);

	maxLineGap.addConstraint("0");
	maxLineGap.addConstraint("100");
	registerProperty(maxLineGap);
}

CvHoughLinesImage_Processor::~CvHoughLinesImage_Processor()
{
	LOG(LTRACE) << "Good bye CvHoughLinesImage_Processor\n";
}

void CvHoughLinesImage_Processor::prepareInterface() {
	// Register data streams, events and event handlers HERE!

	registerHandler("onNewImage", boost::bind(&CvHoughLinesImage_Processor::onNewImage, this));
	addDependency("onNewImage", &in_img);

	registerStream("in_img", &in_img);
	registerStream("out_lines", &out_lines);
	registerStream("out_linesDrawable", &out_linesDrawable);
}

bool CvHoughLinesImage_Processor::onInit()
{
	LOG(LTRACE) << "CvHoughLinesImage_Processor::initialize\n";

	return true;
}

bool CvHoughLinesImage_Processor::onFinish()
{
	return true;
}

bool CvHoughLinesImage_Processor::onStop()
{
	return true;
}

bool CvHoughLinesImage_Processor::onStart()
{
	return true;
}

bool sameLines(Vec4i line1, Vec4i line2) {
    float A1, A2, b1, b2, Yaxis1, Xaxis1, Yaxis2, Xaxis2, angle1, angle2;

    float len1 = sqrt(float(line1[2] - line1[0])*float(line1[2] - line1[0]) + float(line1[3] - line1[1])*float(line1[3] - line1[1]));
    if(abs(float(line1[2] - line1[0])) < 0.01 * len1) {
        //linia 1 pionowa
        angle1 = 90.0;
        Yaxis1 = 0.0;
        Xaxis1 = (line1[0] + line1[2]) / 2.0;
    }
    else {
        A1 = float(line1[3] - line1[1]) / float(line1[2] - line1[0]);
        b1 = line1[1] - A1 * line1[0];

        Yaxis1 = b1;
        Xaxis1 = -b1 / A1;

        angle1 = atan2(float(line1[3] - line1[1]) , float(line1[2] - line1[0]))*180.0 / M_PI;
    }
    float len2 = sqrt(float(line2[2] - line2[0])*float(line2[2] - line2[0]) + float(line2[3] - line2[1])*float(line2[3] - line2[1]));
    if(abs(float(line2[2] - line2[0])) < 0.001 * len2) {
        //linia 2 pionowa
        angle2 = 90.0;
        Yaxis2 = 0.0;
        Xaxis2 = (line2[0] + line2[2]) / 2.0;
    }
    else {
        A2 = float(line2[3] - line2[1]) / float(line2[2] - line2[0]);
        b2 = line2[1] - A2 * line2[0];

        Yaxis2 = b2;
        Xaxis2 = -b2 / A2;

        angle2 = atan2(float(line2[3] - line2[1]) , float(line2[2] - line2[0]))*180.0 / M_PI;
    }

    float diffA = abs(angle1 - angle2);

    if(diffA < 5.0 && (abs(Yaxis1 - Yaxis2) < 100 || abs(Xaxis1 - Xaxis2) < 100)) {
        return true;
    }
    return false;
}



void CvHoughLinesImage_Processor::onNewImage()
{
	if (in_img.empty()) {
		LOG(LFATAL) << "Component " << name() << " " << "in_img input stream is empty.";
		return;
	}
	Mat image = in_img.read();

	if (image.channels() != 1) {
		LOG(LFATAL) << "Component " << name() << " " << "in_img received image must have only one channel.";
		return;
	}



	Types::DrawableContainer c;
	vector<Vec4i> lines;
	cv::HoughLinesP( image, lines, 1, CV_PI/180, threshold, minLineLength, maxLineGap);


	CLOG(LDEBUG) << "Found " << lines.size() << " lines";

	for( size_t i = 0; i < lines.size(); i++ )
	{
		c.add(new Types::Line(cv::Point(lines[i][0], lines[i][1]), cv::Point(lines[i][2], lines[i][3])));
	}
	out_linesDrawable.write(c);
	out_lines.write(lines);
}

}//: namespace CvHoughLinesImage
}//: namespace Processors
