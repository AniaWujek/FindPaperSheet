/*!
 * \file
 * \brief
 */

#include <memory>
#include <string>

#include "CvHoughLines.hpp"
#include "Common/Logger.hpp"

#include <opencv2/imgproc/imgproc.hpp>

#include "Types/DrawableContainer.hpp"
#include "Types/Line.hpp"
#include <math.h>

namespace Processors {
namespace CvHoughLines {

using namespace cv;
using namespace std;

CvHoughLines_Processor::CvHoughLines_Processor(const std::string & name) :
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

CvHoughLines_Processor::~CvHoughLines_Processor()
{
	LOG(LTRACE) << "Good bye CvHoughLines_Processor\n";
}

void CvHoughLines_Processor::prepareInterface() {
	// Register data streams, events and event handlers HERE!

	registerHandler("onNewImage", boost::bind(&CvHoughLines_Processor::onNewImage, this));
	addDependency("onNewImage", &in_img);

	registerStream("in_img", &in_img);
	registerStream("out_lines", &out_lines);
	registerStream("out_linesDrawable", &out_linesDrawable);
}

bool CvHoughLines_Processor::onInit()
{
	LOG(LTRACE) << "CvHoughLines_Processor::initialize\n";

	return true;
}

bool CvHoughLines_Processor::onFinish()
{
	return true;
}

bool CvHoughLines_Processor::onStop()
{
	return true;
}

bool CvHoughLines_Processor::onStart()
{
	return true;
}

bool sameLines(Vec4i line1, Vec4i line2) {
    float A1 = float(line1[3] - line1[1]) / float(line1[2] - line1[0]);
    float b1 = line1[1] - A1 * line1[0];
    float A2 = float(line2[3] - line2[1]) / float(line2[2] - line2[0]);
    float b2 = line2[1] - A2 * line2[0];

    float Yaxis1 = b1;
    float Xaxis1 = -b1 / A1;

    float Yaxis2 = b2;
    float Xaxis2 = -b2 / A2;



    float angle1 = atan2(float(line1[3] - line1[1]) , float(line1[2] - line1[0]));
    float angle2 = atan2(float(line2[3] - line2[1]) , float(line2[2] - line2[0]));

    float diffA = abs(angle1 - angle2)*180.0 / M_PI;

    cout<<diffA<<"\t"<<A2<<"\t"<<b1<<"\t"<<b2<<endl;
    if(diffA < 5.0 && (abs(Yaxis1 - Yaxis2) < 100 || abs(Xaxis1 - Xaxis2) < 100)) {
        return true;
    }
    return false;
}

vector<Vec4i> checkDuplicate(vector<Vec4i> & lines) {
    vector<Vec4i> newLines;

    for( size_t i = 0; i < lines.size(); i++ )
	{
        bool diff = true;
		for( size_t j = i+1; j < lines.size(); j++ )
        {
            if(sameLines(lines[i], lines[j])) {
                diff = false;
                break;
            }
        }
        if(diff == true) {


            newLines.push_back(lines[i]);
        }
	}
	return newLines;
}

void CvHoughLines_Processor::onNewImage()
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
    lines = checkDuplicate(lines);

	CLOG(LDEBUG) << "Found " << lines.size() << " lines";

	for( size_t i = 0; i < lines.size(); i++ )
	{
		c.add(new Types::Line(cv::Point(lines[i][0], lines[i][1]), cv::Point(lines[i][2], lines[i][3])));
	}
	out_linesDrawable.write(c);
	out_lines.write(lines);
}

}//: namespace CvHoughLines
}//: namespace Processors
