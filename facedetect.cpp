#include <cv.h>
 #include <highgui.h> 
 #include <stdio.h>  
#include <sstream>

using namespace cv;
using namespace std;

 int main() {
   CvCapture* capture = cvCaptureFromCAM( CV_CAP_ANY );
   //(size can be reduced with the next two lines
   //cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH,320);
   //cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, 240);
   if ( !capture ) {
     fprintf( stderr, "ERROR: capture is NULL \n" );
     getchar();
     return -1;
   }

   cvNamedWindow( "mywindow", CV_WINDOW_AUTOSIZE );

   Mat original,gray,face,face_resized;

   string glasses_cascade_loc = "/home/fibrs/build/opencv/share/OpenCV/haarcascades/haarcascade_eye_tree_eyeglasses.xml";
   string eyes_cascade_loc = "/home/fibrs/build/opencv/share/OpenCV/haarcascades/haarcascade_eye.xml";
   string faces_cascade_loc = "/home/fibrs/build/opencv/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";

   CvPoint AnEye_left;
   CvPoint AnEye_right;
   CascadeClassifier glasses_cascade, eyes_cascade, faces_cascade;

   if( !eyes_cascade.load( eyes_cascade_loc ) ){ printf("--(!)Error loading eyes-cascade\n"); return -1; };
   if( !glasses_cascade.load( glasses_cascade_loc ) ){ printf("--(!)Error loading glasses-cascade\n"); return -1; };
   if( !faces_cascade.load( faces_cascade_loc ) ){ printf("--(!)Error loading faces-cascade\n"); return -1; };

   // Show the image captured from the camera in the window and repeat (and locate faces too)

   int j = 0;
   int i = 0;
   string face_window;

   for(;;)
   {
     original= cvQueryFrame ( capture);
     char key;

     cvtColor(original, gray, CV_BGR2GRAY);
     
     vector< Rect_<int> > faces;

     faces_cascade.detectMultiScale(gray, faces, 1.1, 3, CV_HAAR_SCALE_IMAGE, Size (60, 60));

     imshow( "mywindow", original );

     for(;j > faces.size(); j--)
     {
       face_window = "face " + static_cast<ostringstream*>( &(ostringstream() << (j)) )->str();

       destroyWindow(face_window);
     }

     for(i = 0; i < faces.size(); i++)
     {
       Rect face_i = faces[i];
       face = original(face_i);

       cv::resize(face, face_resized, Size(250, 250), 1.0, 1.0, INTER_CUBIC);

       face_window = "face " + static_cast<ostringstream*>( &(ostringstream() << (i + 1)) )->str();

       imshow(face_window , face_resized);

     }

     j = faces.size();

     // Do not release the frame!
     //If ESC key pressed, Key=0x10001B under OpenCV 0.9.7(linux version),
     //remove higher bits using AND operator
     if ( (cvWaitKey(10) & 255) == 27 ) break;
   }
   // Release the capture device housekeeping
   cvReleaseCapture( &capture );
   cvDestroyWindow( "mywindow" );
   return 0;
 }
