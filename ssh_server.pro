
#CONFIG		+= debug
TEMPLATE	= app
TARGET 		=
INCLUDEPATH 	+= . /opt/onyx/arm/include/QtWebKit/
RESOURCES	= res.qrc

HEADERS 	= sshd_view.h		\
		  sshd_application.h      \
		  sshd.h

SOURCES 	= sshd_application.cpp 		\
		  sshd_view.cpp	\
		  main.cpp \
		  sshd.cpp
		  
LIBS += -lz -lonyxapp -lonyx_base -lonyx_ui -lonyx_screen -lonyx_sys -lonyx_wpa -lonyx_wireless -lonyx_data -lonyx_cms

INCLUDEPATH += /opt/onyx/arm/include

