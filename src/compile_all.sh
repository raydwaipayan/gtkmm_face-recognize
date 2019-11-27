echo "Compiling run_training";
g++ /home/dwai/Desktop/workspace/src/run_training.cpp -o /home/dwai/Desktop/workspace/src/run_training -I/usr/local/include -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_face -lopencv_objdetect -lopencv_imgcodecs

echo "Compiling recognize";
g++ /home/dwai/Desktop/workspace/src/recognize.cpp -o /home/dwai/Desktop/workspace/src/recognize  -I/usr/local/include -L/usr/local/lib -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_face -lopencv_objdetect -lopencv_imgcodecs -lopencv_video -lopencv_videoio

