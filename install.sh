#!/bin/sh
# Creator: Dwaipayan Ray
# Feel free to modify this program and add your own options

# Check for existence of gtkmm-3.0, else exit
pkg-config --modversion gtkmm-3.0 2>/dev/null || {
	echo >&2 "I require gtkmm-3.0 but it's not installed.  Aborting.";
	exit 1; 
} 

# Compile all 
g++ start.cpp `pkg-config --cflags --libs gtkmm-3.0` -I/usr/local/include -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_face -lopencv_objdetect -lopencv_imgcodecs -lopencv_video -lopencv_videoio -o start

g++ src/run_training.cpp -o src/run_training -I/usr/local/include -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_face -lopencv_objdetect -lopencv_imgcodecs

g++ src/recognize.cpp -o src/recognize  -I/usr/local/include -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_face -lopencv_objdetect -lopencv_imgcodecs -lopencv_video -lopencv_videoio
