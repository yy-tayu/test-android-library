OPENCV_ROOT := $(LOCAL_PATH)/../../../../../deps/opencv/sdk/native/jni
OPENCV_LIB_TYPE:=SHARE  # Change this line to use static libraries
OPENCV_INSTALL_MODULES:=on
include $(OPENCV_ROOT)/OpenCV.mk