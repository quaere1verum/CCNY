import cv2
from scipy import misc

# import matplotlib.pyplot as plt

import numpy as np 
from PIL import Image

############################################
# Javier Pajuelo
# Professor Jie Wei
# 
# Project 1 - Digital Libraries Spring 2015
# Problem #4 : Coin Recognition
############################################
def main():
    # read coin 
    # image = cv2.imread('uk-coins.jpg')
    # image = cv2.imread('coins-2.jpg')
    # image = cv2.imread('coins.jpg')
    image = cv2.imread('coinstacked.jpg')
    
    
    # cv2.imshow('gray ', gray)
    # cv2.show()
    
    output = image.copy() 
    
    # aid recognition 
    '''
    image = cv2.medianBlur(image,5 )
    
    # adding more aid to recognition
    # smoothing edges and make gray image more recognizable
    image = cv2.GaussianBlur(image,(5,5),0) 

    # smooth image prevent false circles
    image = cv2.bilateralFilter(image,9,75,75)
    '''


    """
    plt.subplot(121),plt.imshow(image,cmap = 'gray')
    plt.title('Original Image'), plt.xticks([]), plt.yticks([])
    plt.subplot(122),plt.imshow(edges,cmap = 'gray')
    plt.title('Edge Image'), plt.xticks([]), plt.yticks([])
    plt.show()
    """
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    
    gray = cv2.medianBlur(gray,5 )
    # gray = cv2.GaussianBlur(gray,(5,5),0) 
    gray = cv2.bilateralFilter(gray,9,75,75)



    print "About to show image gray scale ... "
    cv2.imshow('Gray', gray)
    
    # print "print image = ", gray.size
    # size = gray.size/
    """"
    vals  = gray_img.flatten()

    from matplotlib import pyplot as plt
    counts, bins = plt.hist(vals,range(257))

    # plot histogram centered on values 0..255
    plt.bar(bins[:-1] - 0.5, counts, width=1, edgecolor='none')
    plt.xlim([-0.5, 255.5])
    plt.show()
    """
    #===============================================================
    # detect circles in the image
    # 1.6 , 150 
    '''
    img = cv2.imread('uk-coins.jpg',0)
    img = cv2.medianBlur(img,5)
    cimg = cv2.cvtColor(img,cv2.COLOR_GRAY2BGR)
    gray = img 

    circles = cv2.HoughCircles(gray, cv2.cv.CV_HOUGH_GRADIENT, 1, 20, 
            param1=50, param2=30, minRadius=0, maxRadius=0)

    circles = np.uint16(np.around(circles))
    for i in circles[0,:]:
            # draw the outer circle
        cv2.circle(cimg,(i[0],i[1]),i[2],(0,255,0),2)
                    # draw the center of the circle
        cv2.circle(cimg,(i[0],i[1]),2,(0,0,255),3)

    cv2.imshow('detected circles',cimg)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    '''
    #===============================================================

    circles = cv2.HoughCircles(gray, cv2.cv.CV_HOUGH_GRADIENT, 1.2, 100)
            #\
            #param1=50,param2=30,minRadius=0,maxRadius=gray.size/2)

    # print "circles = ", circles 

    # ensure at least some circles were found
    if circles is not None:
        # convert the (x, y) coordinates and radius of the circles to integers
        circles = np.round(circles[0, :]).astype("int")

        # loop over the (x, y) coordinates and radius of the circles
        for (x, y, r) in circles:
            # draw the circle in the output image, then draw a rectangle
            # corresponding to the center of the circle
            
            cv2.circle(output, (x, y), r, (111, 255, 0), 4)
            # cv2.circle(output, (x, y), r, (0, 255, 0), 4)
            cv2.rectangle(output, (x - 5, y - 5), (x + 5, y + 5),\
                    (0, 128, 255), -1)

        # show the output image

        cv2.imshow("image\toutput", np.hstack([output]))
        #cv2.imshow("image\toutput", np.hstack([image, output]))
        cv2.waitKey(0)

main()
