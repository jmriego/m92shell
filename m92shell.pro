
#CONFIG		+= debug
TEMPLATE	= app
TARGET 		=
INCLUDEPATH 	+= . /opt/onyx/arm/include/QtWebKit/
RESOURCES	= res.qrc

HEADERS 	= shell_view.h		\
		  shell_application.h      \
		  shell.h

SOURCES 	= shell_application.cpp 		\
		  shell_view.cpp	\
		  main.cpp \
		  shell.cpp
		  
LIBS += -lz -lonyxapp -lonyx_base -lonyx_ui -lonyx_screen -lonyx_sys -lonyx_wpa -lonyx_wireless -lonyx_data -lonyx_cms

INCLUDEPATH += /opt/onyx/arm/include
