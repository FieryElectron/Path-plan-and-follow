TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += /usr/local/include/opencv4





LIBS += -L/usr/local/lib
LIBS += -lopencv_aruco
LIBS += -lopencv_bgsegm
LIBS += -lopencv_bioinspired
LIBS += -lopencv_calib3d
LIBS += -lopencv_ccalib
LIBS += -lopencv_core
LIBS += -lopencv_cvv
LIBS += -lopencv_datasets
LIBS += -lopencv_dnn
LIBS += -lopencv_dnn_objdetect
LIBS += -lopencv_dpm
LIBS += -lopencv_face
LIBS += -lopencv_features2d
LIBS += -lopencv_flann
LIBS += -lopencv_fuzzy
LIBS += -lopencv_gapi
LIBS += -lopencv_hfs
LIBS += -lopencv_highgui
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_imgproc
LIBS += -lopencv_img_hash
LIBS += -lopencv_line_descriptor
LIBS += -lopencv_ml
LIBS += -lopencv_objdetect
LIBS += -lopencv_optflow
LIBS += -lopencv_phase_unwrapping
LIBS += -lopencv_photo
LIBS += -lopencv_plot
LIBS += -lopencv_quality
LIBS += -lopencv_reg
LIBS += -lopencv_rgbd
LIBS += -lopencv_saliency
#LIBS += -lopencv_sfm
LIBS += -lopencv_shape
LIBS += -lopencv_stereo
LIBS += -lopencv_stitching
LIBS += -lopencv_structured_light
LIBS += -lopencv_superres
LIBS += -lopencv_surface_matching
LIBS += -lopencv_text
LIBS += -lopencv_tracking
LIBS += -lopencv_video
LIBS += -lopencv_videoio
LIBS += -lopencv_videostab
LIBS += -lopencv_viz
LIBS += -lopencv_xfeatures2d
LIBS += -lopencv_ximgproc
LIBS += -lopencv_xobjdetect

LIBS += -lpthread


