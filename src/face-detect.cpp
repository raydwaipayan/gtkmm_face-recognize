//Opencv C++ Example on Real time Face Detection Using Haar Cascade Classifier
  
/*We can similarly train our own Haar Classifier and Detect any object which we want
Only Thing is we need to load our Classifier in place of cascade_frontalface_alt2.xml */
  
#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/tracking.hpp" 
#include <iostream>
#include <stdio.h>
   
using namespace std;
using namespace cv;
   
int main( )
{
 VideoCapture capture(0);  
    if (!capture.isOpened())  
    throw "Error when reading file";  
    namedWindow("window", 1);  
    namedWindow("Crop_Image-window", 1);  
    int counter = 0;
    for (;;)
     { 
       Mat image; 
       capture >> image;  
       if (image.empty())  
       break; 
 
       // Load Face cascade (.xml file)
       CascadeClassifier face_cascade;
       face_cascade.load("/home/riom/Mini_Project/mini_project/src/etc/haarcascade_frontalface_alt.xml" );
       if(!face_cascade.load("/home/riom/Mini_Project/mini_project/src/etc/haarcascade_frontalface_alt.xml" ))
       {
         cerr<<"Error Loading XML file"<<endl;
         return 0;
       }
  
      // Detect faces
      std::vector<Rect> faces;
      face_cascade.detectMultiScale( image, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
      int i = 0;
      // Draw circles on the detected faces
      for(; i < faces.size(); i++ )
      {
	     // std::cout<<faces.size()<<endl;
	Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        //ellipse( image, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
	rectangle( image, Point(faces[i].x, faces[i].y), Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height), Scalar(0,0,255,1),1,8,0);
      }
       
  imshow( "Detected Face", image );
                
  Rect roi(faces[i].x,faces[i].y,(faces[i].width-1),(faces[i].height-1));
 
   Mat crop = image(roi);
   imshow( "Crop_Image-window", crop );
  String name = format("img%04d.png", counter++); // NEW !
  if(counter==61)
	  break;
  imwrite(name, crop);
  if(waitKey(1)==27)
	  break;  
   }  
}
