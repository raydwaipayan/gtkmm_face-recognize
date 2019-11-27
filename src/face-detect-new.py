import cv2
import numpy as np
from sys import argv
import sys
import os
from os import path

sys.path.append('/usr/local/lib/python2.7/site-packages')

argumentList=sys.argv
cascade_loc=sys.argv[1]
qty=sys.argv[2]

print qty
full_path=str(sys.argv[3])

face_cascade = cv2.CascadeClassifier(cascade_loc+'haarcascade_frontalface_default.xml')
# To capture video from webcam. 
cap = cv2.VideoCapture(0)

count = 1
quantity = int(qty)
if(path.exists(full_path)==False):
    os.makedirs(full_path)
while True:
    # Read the frame
    _, img = cap.read()
    # Convert to grayscale
    gray = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)
    # Detect the faces
    faces = face_cascade.detectMultiScale(gray, 1.1, 4)
    # Draw the rectangle around each face
    z=1
    x=0
    y=0
    w=0
    h=0
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x+w, y+h), (255, 0, 0), 2)
        print "------%d" % count
        print "%d %d %d %d %d %d" % (count,z,x,y,w,h)
        z = z+1
    # Display
    cv2.imshow('img', img)
    # Write
    if count==(quantity+1):
        break
    if h < 100 or w < 100:
        continue
    name = "/img%d.png" % (count)
    crop_img = img[y:y+h, x:x+w] 
    
    savepath=full_path + name
    cv2.imwrite(savepath,crop_img)
    count=count+1
    # Stop if escape key is pressed
    k = cv2.waitKey(30) & 0xff
    if k==27:
        break
# Release the VideoCapture object
cap.release()
