# Include the directory itself as a path to include directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Create a variable containing all .cpp files:
FILE(GLOB files *.cpp)

# Find required packages
# Find OpenCV library files
FIND_PACKAGE( OpenCV REQUIRED )

# Create an executable file from sources:
ADD_LIBRARY(CvFindPaperSheet SHARED ${files})

# Link external libraries
TARGET_LINK_LIBRARIES(CvFindPaperSheet ${OpenCV_LIBS} ${DisCODe_LIBRARIES} )

INSTALL_COMPONENT(CvFindPaperSheet)
