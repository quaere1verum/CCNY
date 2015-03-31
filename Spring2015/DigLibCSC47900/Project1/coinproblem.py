import cv2
from scipy import misc
# import matplotlib.pyplot as plt
import numpy as np 
from PIL import Image

#################################################################
# Javier Pajuelo                                                #
# Professor Jie Wei                                             #
#                                                               #
# Project 1 - Digital Libraries Spring 2015                     #
# Problem #4 : Coin Recognition                                 #
# Code uses opencv2 built-in HoughCircles algorithm             #
# that finds circles in image, but algorithm is far from        #
# being robust, so I aided the recognition with modifyications  #
# in the images such as medianBlur, etc.                        #
#                                                               #
# * Outcome: When coins are distant apart and colors are defined# 
# from background, the recognition is almost flawless.          #
#################################################################
def main():
    # read coin 
    image = cv2.imread('uk-coins.jpg')
    #image = cv2.imread('coins-2.jpg')
    # image = cv2.imread('coins.jpg')
    # image = cv2.imread('coinstacked.jpg')
    
    # show gray image 
    # cv2.imshow('gray ', gray)
    # cv2.show()
    outimg = image.copy() 
    # The functions below can aid recognition 
    '''
    image = cv2.medianBlur(image,5 ) 
    # adding more aid to recognition
    # smoothing edges and make gray image more recognizable
    image = cv2.GaussianBlur(image,(5,5),0) 
    # smooth image prevent false circles
    image = cv2.bilateralFilter(image,9,75,75)
    ''' 

    # defuault approach 
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)   
    gray = cv2.medianBlur(gray,5 )
    # gray = cv2.GaussianBlur(gray,(5,5),0) 
    gray = cv2.bilateralFilter(gray,9,75,75)
    
    # opencv stuff  
    circles = cv2.HoughCircles(gray, cv2.cv.CV_HOUGH_GRADIENT, 1.2, 100)
    
    # opencv might return nothing, if circles cannot be read in image 
    if circles is not None:
        # circles contains positions of center and such, convert into integer
        circles = np.round(circles[0, :]).astype("int")

        # iterate over coordinates and radius 
        for (x_axis, y_axis, r) in circles:
            # draw on image for output  
            cv2.circle(outimg, (x_axis, y_axis), r, (255, 55, 90), 4)
            cv2.rectangle(outimg, (x_axis - 5, y_axis - 5), (x_axis + 5, y_axis + 5),\
                    (0, 128, 255), -1)
        
        # show image 
        cv2.imshow("Image using medianBlur, bilateralFiler, and "\
                "HoughCircles: ", np.hstack([outimg]))
        cv2.waitKey(0)
    
    else:
        """
        Upon failure to recognize default recognition.
        Code showcases all image files with different approaches to 
        recognize circles 
        """
        trial = 4
        print "No circles found using default approach.\n"\
                "Starting trials to modify image and aid algorithm:"
        filelst = ['coins-2.jpg', 'uk-coins.jpg', 'coins.jpg',\
                'coinstacked.jpg']    
        fidx = 0
        
        image = cv2.imread(filelst[fidx])
        print "Working on image: "+filelst[fidx]
        while trial>0:
            
            
            outimg = image.copy() 
            circle_count = 0
            gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
            if trial==1:

                gray = cv2.medianBlur(gray,5 )
                circles = cv2.HoughCircles(gray, cv2.cv.CV_HOUGH_GRADIENT,\
                        1.2, 100)

                
                if circles is not None:
                    circles = np.round(circles[0, :]).astype("int")

                    for (x_axis, y_axis, r) in circles:
                        circle_count += 1
                        cv2.circle(outimg, (x_axis, y_axis), r, (111, 255, 0), 4)
                        cv2.rectangle(outimg, (x_axis - 5, y_axis - 5), (x_axis + 5, y_axis + 5),\
                                (0, 128, 255), -1)

                    cv2.imshow("Image aided by medianBlur", outimg)
                    cv2.waitKey(0)

                print "Trial "+str(trial)+" using medianBlur found "+\
                        str(circle_count)+ " circles"
            
            if trial==2:
                gray = cv2.GaussianBlur(gray,(5,5),0) 
                circles = cv2.HoughCircles(gray, cv2.cv.CV_HOUGH_GRADIENT,\
                        1.2, 100)
                
                if circles is not None:
                    circles = np.round(circles[0, :]).astype("int")

                    for (x_axis, y_axis, r) in circles:
                        circle_count+=1
                        cv2.circle(outimg, (x_axis, y_axis), r, (20, 50, 255), 4)
                        cv2.rectangle(outimg, (x_axis - 5, y_axis - 5), (x_axis + 5, y_axis + 5),\
                                (0, 128, 255), -1)

                    cv2.imshow("Image aided by GaussianBlur",\
                            np.hstack([outimg]))
                    cv2.waitKey(0)
                
                print "Trial "+str(trial)+" using GaussianBlur found "+\
                        str(circle_count)+" circles"

            if trial ==3:       
                gray = cv2.bilateralFilter(gray,9,75,75)
                circles = cv2.HoughCircles(gray, cv2.cv.CV_HOUGH_GRADIENT,\
                        1.2, 100)

                if circles is not None:
                    circles = np.round(circles[0, :]).astype("int")

                    for (x_axis, y_axis, r) in circles:
                        circle_count+=1
                        cv2.circle(outimg, (x_axis, y_axis), r, (50, 255, 50), 4)
                        cv2.rectangle(outimg, (x_axis - 5, y_axis - 5), (x_axis + 5, y_axis + 5),\
                                (0, 128, 255), -1)

                    cv2.imshow("Image aided by bilateralFilter",\
                            np.hstack([outimg]))
                    cv2.waitKey(0)

                print "Trial "+str(trial)+" using bilateralFilter found "\
                        +str(circle_count)+" circles"


            if trial ==4:       
                gray = cv2.medianBlur(gray,5 ) 
                gray = cv2.GaussianBlur(gray,(5,5),0) 
                gray = cv2.bilateralFilter(gray,9,75,75)
                circles = cv2.HoughCircles(gray, cv2.cv.CV_HOUGH_GRADIENT,\
                        1.2, 100)

                if circles is not None:
                    circles = np.round(circles[0, :]).astype("int")

                    for (x_axis, y_axis, r) in circles:
                        circle_count+=1
                        cv2.circle(outimg, (x_axis, y_axis), r, (255, 50, 50), 4)
                        cv2.rectangle(outimg, (x_axis - 5, y_axis - 5), (x_axis + 5, y_axis + 5),\
                                (0, 128, 255), -1)

                    cv2.imshow("Image aided by all previous algorithms",\
                            np.hstack([outimg]))
                    cv2.waitKey(0)
            
                print "Trial "+str(trial)+" using all algorithms above found "\
                        +str(circle_count)+" circles"
            trial-=1
            
            if trial == 0 and fidx < len(filelst)-1:
                fidx+=1
                trial = 4 
                image = cv2.imread(filelst[fidx])
                print "\n\n\nWorking on image: "+filelst[fidx]
        
main()
