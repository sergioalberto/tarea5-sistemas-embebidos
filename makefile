APP=reproducir_mp3
SRC=$(APP).c
OBJ=$(APP).o
CC=gcc
CROSS_COMPILE=/home/sergio/ti-sdk-beagleboard-06.00.00.00/linux-devkit/sysroots/i686-arago-linux/usr/bin/arm-linux-gnueabihf-
LIB= `pkg-config --cflags --libs gstreamer-0.10`
DirIni=`/opt/gstreamer-sdk/bin/gst-sdk-shell`

all: $(APP)

$(APP):
		$(CC) -o $(APP) $(SRC) $(LIB)

xBB: 
		$(CROSS_COMPILE)$(CC) -o $(APP) $(SRC) $(LIB)

clean:
		rm $(APP) #$(OBJ)
