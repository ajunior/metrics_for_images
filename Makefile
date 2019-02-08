
include Makefile.top


MODULE     = dvat

CFLAGS = -I$(INCDIR)/ \
        -I/usr/local/include/\
        -I/usr/include/\
	-Iinclude/\
		-lopencv_highgui\
		-lopencv_core\

CFLAGS += -g -ggdb -fPIC


LDFLAGS = \
	-L/usr/local/lib\
	-lopencv_highgui\
	-lopencv_core\
	-lopencv_videoio\
	-lopencv_video\
	-lopencv_imgproc\
	-lopencv_imgcodecs\

SOURCES = \
	PSNR_GPDS.cpp\
	PWSSIM.cpp\
	SSIM.cpp\
    main.cpp


.SUFFIXES: .cpp .o .h

include Makefile.build

default: all