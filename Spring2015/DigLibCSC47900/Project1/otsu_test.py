import cv2
from scipy import misc
import numpy as np 
from PIL import Image

#####################################################################
# Javier Pajuelo                                                    #
# Professor Jie Wei                                                 #
#                                                                   # 
# Project 1 - Digital Libraries Spring 2015                         #
# Problem #2 : Adaptive Otsu comparison                             #
# Notes:                                                            #   
# Dependencies are numpy, cv2, scipy, and                           #
# PIL                                                               #
#                                                                   #
# * Adaptive Otsu was made splitting the image matrix in four parts #
#                                                                   #
# * Adaptive Otsu with overlapping matrices was made splitting the  #
# image matrix into 6, the four matrices used before and one for    #
# each row overlapping the other two. e.g,                          #
# [    | ] [ |   ]                                                  #
# [    | ] [ |   ]                                                  #
# [    | ] [ |   ]                                                  #
# the thresholds of overlapping matrices are averaged and assigned  #
# for middle matrix.                                                #
#                                                                   #
# * Outcome: Charts show an improvement in adaptive otsu with       #
# overlapping over the standard adaptive Otsu.                      #
# The global Otsu approach is visibly inferior than the adaptive.   #
#####################################################################


def adaptive_otsu(grayimg_mat):
    print grayimg_mat
    # sliced_otsu = grayimg_mat.copy()
    print "shape mat = ", grayimg_mat.shape 
    r , c = grayimg_mat.shape
    
    # Slice matrix image

    # get upper left quadrant 
    slice1 = grayimg_mat[0:r/2,0:c/2].copy()
    print "slice 1  shape : ", slice1.shape
    
    #cv2.imshow('slice1', slice1)
    #cv2.waitKey(0)

    # get lower left quadrant
    slice2 = grayimg_mat[(r/2)+1:r,0:c/2].copy() 
    #cv2.imshow('slice2', slice2)
    #cv2.waitKey(0)

    print "slice 2  shape : ", slice2.shape

    # get upper right quadrant 
    slice3 = grayimg_mat[0:r/2, (c/2)+1:c].copy()  
    #cv2.imshow('slice3', slice3)
    #cv2.waitKey(0) 
    print "slice 3  shape : ", slice3.shape


    # lower right quadrant 
    # print "sliced mat shape: ", slice.shape ,"\t sliced mat ", slice
    slice4 = grayimg_mat[(r/2)+1:r,(c/2)+1:c].copy()   
    #cv2.imshow('slice4', slice4)
    #cv2.waitKey(0)
    print "slice 4  shape : ", slice4.shape

    # create histogram of submat 
    hist1 = cv2.calcHist([slice1], [0], None, [256],[0,256])
    hist2 = cv2.calcHist([slice2], [0], None, [256],[0,256])
    hist3 = cv2.calcHist([slice3], [0], None, [256],[0,256])
    hist4 = cv2.calcHist([slice4], [0], None, [256],[0,256])

    # otsu thresholds 
    local1_thres = otsu(hist1, slice1.size)    
    local2_thres = otsu(hist2, slice2.size)
    local3_thres = otsu(hist3, slice3.size)
    local4_thres = otsu(hist4, slice4.size)


    print "Local1 Otsu threshold: ",local1_thres,\
        "\nlocal2  = ",local2_thres,\
        "\nlocal3 = ", local3_thres,\
        "\nlocal4 = ", local4_thres
    
    # filter by otsu threshold 
    sliced1_otsu = slice1>=local1_thres
    sliced2_otsu = slice2>=local2_thres
    sliced3_otsu = slice3>=local3_thres
    sliced4_otsu = slice4>=local4_thres
    
    # show all slices 
    # works fine 
    """
    from matplotlib import pyplot as plt
    fig, ax = plt.subplots(2, 2, figsize=(8, 5))
    ax1, ax2, ax3, ax4 = ax.ravel()
    
    ax1.imshow(sliced1_otsu, cmap=plt.cm.gray)
    ax1.set_title('sliced1 ')
    ax1.axis('off')
    
    ax2.imshow(sliced2_otsu, cmap=plt.cm.gray)
    ax2.set_title('sliced2)')
    ax2.axis('off')

    ax3.imshow(sliced3_otsu, cmap=plt.cm.gray)
    ax3.set_title('sliced3)')
    ax3.axis('off')
    
    
    ax4.imshow(sliced4_otsu, cmap=plt.cm.gray)
    ax4.set_title('sliced4)')
    ax4.axis('off')
    plt.show()
    """

    # form matrix again.
    # trying slice matrix 
    # sliced_otsu = [ [None]*r]*c
    #rtmp = r 
    #ctmp = c 

    print "slice dimension ", slice1.shape
    #rtmp , ctmp = sliced_otsu.shape
    
    # sliced_otsu[0:rtmp/2,0:ctmp/2] = sliced1_otsu
    upper_mat = np.concatenate((sliced1_otsu,sliced3_otsu),axis=1)
    lower_mat = np.concatenate((sliced2_otsu, sliced4_otsu),axis=1)
    
    
    print "upper mat : ", upper_mat.shape
    print "lower_mat : ", lower_mat.shape

    sliced_otsu  = np.concatenate((upper_mat,lower_mat),axis=0)


    '''
    #print "sliced final = ", sliced_otsu 

    # get lower left quadrant
    sliced_otsu[(rtmp+1)/2:rtmp,0:ctmp/2] = sliced2_otsu
    print "sliced final = ", sliced_otsu 
    
    # get upper right quadrant 
    sliced_otsu[0:rtmp/2, (ctmp/2)+1:ctmp] = sliced3_otsu
    
    # lower right quadrant 
    sliced_otsu[(rtmp/2)+1:rtmp,(ctmp/2)+1:ctmp] = sliced4_otsu
    
    
    print "sliced final = ", sliced_otsu 

    """
    sliced_otsu = [sliced1_otsu sliced3_otsu,\
            sliced2_otsu sliced4_otsu] 
        


    print "formed otsu : = ", sliced_otsu
    """
    '''
    
    # return binary matrix and threshold 
    # thresholds upleft, up right , downleft, down right
    return sliced_otsu,local1_thres,local3_thres,local2_thres,local4_thres



def adaptive_otsu_overlap(grayimg_mat):
    
    print "Inside adaptive otsu overlapping mats\n",grayimg_mat

    print "shape mat = ", grayimg_mat.shape 
    r , c = grayimg_mat.shape
    
    # trying slice matrix 
    slice1 = grayimg_mat[0:r/2,0:c/2].copy()
    print "slice 1  shape : ", slice1.shape
   
    # getting r/4, 3r/4
    # r/2 + r/4 = 3r/4
    slice1_1 = grayimg_mat[ 0:r/2, c/4: 3*c/4].copy()
    #cv2.imshow('slice1', slice1) 
    #cv2.imshow('slice1_1', slice1_1)
    #cv2.waitKey(0)

    # get lower left quadrant
    slice2 = grayimg_mat[(r/2)+1:r,0:c/2].copy() 
    slice2_2 = grayimg_mat[(r/2)+1:r, c/4:3*c/4].copy()
    #cv2.imshow('slice2', slice2) 
    #cv2.imshow('slice2_2', slice2_2)
    #cv2.waitKey(0)
    print "slice 2  shape : ", slice2.shape

    # get upper right quadrant 
    slice3 = grayimg_mat[0:r/2, (c/2)+1:c].copy()  
    #cv2.imshow('slice3', slice3)
    #cv2.waitKey(0) 
    print "slice 3  shape : ", slice3.shape


    # lower right quadrant 
    # print "sliced mat shape: ", slice.shape ,"\t sliced mat ", slice
    slice4 = grayimg_mat[(r/2)+1:r,(c/2)+1:c].copy()   
    #cv2.imshow('slice4', slice4)
    #cv2.waitKey(0)
    print "slice 4  shape : ", slice4.shape

    # create histogram of submat 
    hist1 = cv2.calcHist([slice1], [0], None, [256],[0,256]) 
    hist1_1 = cv2.calcHist([slice1_1], [0], None, [256],[0,256])
    hist2_2 = cv2.calcHist([slice2_2], [0], None, [256],[0,256])
    hist2 = cv2.calcHist([slice2], [0], None, [256],[0,256])
    hist3 = cv2.calcHist([slice3], [0], None, [256],[0,256])
    hist4 = cv2.calcHist([slice4], [0], None, [256],[0,256])

    # call otsu 
    local1_thres = otsu(hist1, slice1.size)
    local1_1_thres = otsu(hist1_1, slice1_1.size)

    local2_thres = otsu(hist2, slice2.size)
    local2_2_thres = otsu(hist2_2, slice2_2.size)

    local3_thres = otsu(hist3, slice3.size)
    local4_thres = otsu(hist4, slice4.size)


    print "Local  Otsu threshold: \n",\
        "==============================\n",\
        "Upper Left Matrix threshold: ", local1_thres,\
        "\nUpper Mid Matrix threshold: ",local1_1_thres,\
        "\nUpper Right Matrix threshold: ", local3_thres,\
        "\nLower Left Matrix threshold: ",local2_thres,\
        "\nLower Mid Matrix threshold: ",local2_2_thres,\
        "\nLower Right Matrix threshold: ", local4_thres
    
    # filter by otsu threshold 

    # Upper right quadrant filter by threshold from otsu
    sliced1_otsu = slice1>=local1_thres 
    # averaging threshold of overlapping mats
    mean1 = (local1_thres+local1_1_thres)/2.0
    print "Overlapping matrices Upper Left and Upper Mid | Mean thresholds between overlaps: ", mean1
    sliced1_1_otsu = slice1_1>=mean1
    
    # lower left quadrant 
    sliced2_otsu = slice2>=local2_thres    
    mean3 = (local2_2_thres+local2_thres)/2.0
    sliced2_1_otsu = slice2_2>= mean3
    print "Overlapping matrices Lower Left and Lower Mid | Mean thresholds between overlaps: ", mean3
    
    # upper right qudrant 
    sliced3_otsu = slice3>=local3_thres
    # get average threshold between overlapping mats
    mean2 = (local3_thres + local1_1_thres)/2.0
    sliced1_2_otsu = slice1_1>=mean2 
    print "Overlapping matrices Upper Mid and  Upper Right | Mean thresholds between overlaps: ", mean2


    # lower right quadrant 
    sliced4_otsu = slice4>=local4_thres
    mean4 = (local2_2_thres+local4_thres)/2.0 
    sliced2_2_otsu = slice2_2>= mean4
    print "Overlapping matrices Lower Mid and  Lower Right | Mean thresholds between overlaps: ", mean4

    print "sliced1 ", sliced1_otsu.shape, "\t sliced1_1 = ", sliced1_1_otsu.shape
    print "sliced3 ", sliced3_otsu.shape, "\t sliced1_2 = ", sliced1_2_otsu.shape
    
    # now merge overlapping mats
    # uppper right quadrant 
    sliced1_otsu[0:r/2, c/4:c/2] = sliced1_1_otsu[0:r/2, 0:c/4]
    # print "sliced1_otsu ", sliced1_otsu 
    
    # upper right quadrant 
    sliced3_otsu[0:r/2, 0:c/4] = sliced1_2_otsu[0:r/2, c/4:c/2]
    
    # lwoer left qudrant 
    sliced2_otsu[(r/2)+1 : r, c/4:c/2] = sliced2_1_otsu[(r/2)+1:r, 0:c/4]

    # lower right quadrant 
    sliced4_otsu[(r/2)+1:r, 0:c/4] = sliced2_2_otsu[(r/2)+1:r, c/4:c/2]
    
    # put everything together 
    upper_mat = np.concatenate((sliced1_otsu,sliced3_otsu),axis=1)
    lower_mat = np.concatenate((sliced2_otsu, sliced4_otsu),axis=1)
    

    sliced_otsu  = np.concatenate((upper_mat,lower_mat),axis=0)
    
    # return binary matrix and threshold 
    return sliced_otsu,local1_thres,mean1,local3_thres,local2_thres,mean3,local4_thres









def main():
    
    print "Starting program ... "

    # ========================
    # using matplot lib 
    
    """
    from matplotlib import pyplot as plt
    gray_img = cv2.imread('nin.jpg', 0)
    # pixels = gray_img.size()
    
    b,bins,patches= plt.hist(gray_img.ravel(),256,[0,256])
    
    plt.xlim([0,255])
    plt.show()
    """
    
    # print "hist = ", hist
    """ 
    print "b = ", b, "\tbins = ", bins, "\tpatches = ", patches 


    # print "Otsu : ", otsu(b,pixels)
    # plt.show()


    rtn = cv2.adaptiveThreshold(gray_img, 255,cv2.ADAPTIVE_THRESH_MEAN_C,\
            cv2.THRESH_BINARY,13, 1 );
    print "rtn = ", rtn 
    cv2.imshow('rtn', rtn)"""
    # ========================
    
    #========================================== 
    """image = cv2.imread('coins-2.jpg')
    output = image.copy() 
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    print gray"""
    #========================================== 

    
    img = cv2.imread('nin.jpg')
    #gray_img = cv2.imread('harewood.jpg', cv2.IMREAD_GRAYSCALE)
    # gray_img = cv2.imread('ebola2.jpg', cv2.IMREAD_GRAYSCALE)
    #gray_img = cv2.imread('ebola.jpeg', cv2.IMREAD_GRAYSCALE)
    # gray_img = cv2.imread('coins-2.jpg', cv2.IMREAD_GRAYSCALE)
    # gray_img = cv2.imread('lenna.png', cv2.IMREAD_GRAYSCALE)
    
    """
    print "gray img read = ", gray_img
    print "size ", gray_img.size
    pixels = gray_img.size
    print "img shape ", gray_img.shape
    """
    grayimg = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY) 
    print "Pixels? ", grayimg.size,"\nShape = ", grayimg.shape
    
    # grayimg.shape returns dimension of picture AKA pixels 
    r,c = grayimg.shape
    
    local1_otsu, upL1,upR1,lwL1,lwR1 = adaptive_otsu(grayimg)
    
    local_otsuoverlap, upL,upM,upR,lwL,lwM,lwR = adaptive_otsu_overlap(grayimg)


    # print "about to show image"
    # cv2.imshow('nin', grayimg)
    # cv2.waitKey(0)
    
    hist = cv2.calcHist([grayimg], [0], None, [256],[0,256])
    # print "hist = ",hist
    ret = otsu(hist, grayimg.size) 
    print "Global Otsu returns: ", ret
    
    threshold = ret
    
    # return a matrix of true and false given satisfaction of threshold
    global_otsu = grayimg>=threshold
    
    from matplotlib import pyplot as plt
    fig, ax = plt.subplots(2, 2, figsize=(8, 5))
    ax1, ax2, ax3, ax4 = ax.ravel()
    
    ax1.imshow(local1_otsu, cmap=plt.cm.gray)
    ax1.set_title("Adaptive Otsu\nLocal Otsu Thresholds: '{0}', '{1}', '{2}', '{3}')".format(upL1,upR1,lwL1,lwR1))
    ax1.axis('off')
    

    ax2.imshow(local_otsuoverlap, cmap=plt.cm.gray)
    ax2.set_title("Adaptive Otsu\nLocal Otsu Overlap (Thresholds:'{0}', '{1}', '{2}', '{3}', '{4}', '{5}')"\
            .format(upL,upM,upR,lwL,lwM,lwR))
    ax2.axis('off')

    ax3.imshow(grayimg, cmap=plt.cm.gray)
    ax3.set_title("Image")
    ax3.axis('off')
    

    ax4.imshow(global_otsu, cmap=plt.cm.gray)
    ax4.set_title('Global Otsu (threshold = %d)' % threshold)
    ax4.axis('off')

    plt.show()
    """

    plt.plot(hist)
    plt.xlim([0,256])
    plt.show()
    plt.close()
    """


    """ 
    print "Starting histogram ... "
    
    #hist = cv2.calcHist([gray_img], [0], None, [256],[0,256])
    
    vals  = gray_img.flatten()
    from matplotlib import pyplot as plt
    b,bins,patches = plt.hist(vals,256)
    print "b = %s , bins = %s , patches = %s ",b,bins,patches
    plt.xlim([0,255])
    plt.show()
    hist = b 
    """
    # trying own histogram
    """ptr = 0 
    histData = []
    maxLevelValue = 0 
    while ptr < len(gray_img):
            h = 0xFF & gray_img[ptr]
            histData[h]+=1
            if histData[h] > maxLevelValue:
                maxLevelValue = histData[h];
            ptr +=1
    """

    """
    # explore hist 
    print "Hist = ", hist
    idx = 0 
    for h in hist:
        # print "idx = ",idx,"\tval=",h
        idx+=1
    """

    #print "calling otsu "
    #print "Otsu out = ", otsu(hist,pixels)

    """
    # workaround for cv2 and matplotlib seg fault 
    from matplotlib import pyplot as plt
    plt.hist(gray_img.ravel(),256,[0,256])
    plt.title('Histogram for gray scale pic')
    plt.show()

    #sleep(10)
    while True:
        #k = cv2.waitKey(33)&0xFF
        # print k
        k = cv2.waitKey(0)&0xFF

        # print "k is ", k
        if k == 27: 
        #if cv2.waitKey(33) == ord('a'):
            break   # ESC key to exit
        elif k == -1:
            continue
        elif k == ord('c'):
            break
        else:
            print k
    
    cv2.destroyAllWindows()
    """


    #lena = misc.imread("lenna.png")
    #type(lena)

    # l = misc.lena()
    #plt.imshow(l,cmap=plt.cm.gray)
    #plt.show()

    #print lena.shape, lena.dtype
    #print "About to show image from file ... "

    # plt.imshow(lena,cmap=plt.cm.gray)       # shows nothing for some reason ... 
    # plt.show()




    # read lena 
    """x = Image.open("lenna.png", 'r')
    x = x.convert('L')                  # gray scale
    a = np.array(x)
    print "a.shape =  ", a.shape

    # call numpy as np 
    y=np.asarray(x.getdata(),dtype=np.float64).reshape((x.size[1],x.size[0]))
    otsu(y, 256)


    y=np.asarray(y,dtype=np.uint8) #if values still in range 0-255! 
    w=Image.fromarray(y,mode='L')
    w.save('out.jpg')
    """

    # will return a numpy array?
    # numpyarray = scipy.misc.imread()




# Otsu translation from pseudocode
# taken from wikipedia
# http://en.wikipedia.org/wiki/Otsu's_method
def otsu(histogram, total):
    """
    @param histogram 	It's a 256 eleemnt histogram of a grayscale image
			different gray-levels
    @param total	number of pixels in image
	
    @return 		outputs the threshold for the image
    """	
    sum = 0.0
    # idx = 0.0
    # for hidx in histogram:
    for idx in range(0,256):
        sum += idx*histogram[idx]
        # print "idx ", idx,"\thistogram = ", histogram[idx],"\tsum ", sum 
        #sum += idx*hidx
        # idx+=1

    sumB = 0.0
    wB = 0.0
    wF = 0.0
   
    
    max = 0.0
    between = 0.0
    threshold1 = 0.0
    threshold2 = 0.0
     
    idx = 0.0 

    # print "Hisogram: ", histogram 
    
    # for hidx in histogram:
    for idx in range(0,256):
        
        #print "histogram[",idx,"] = ",histogram[idx]

        wB += histogram[idx]
        #print "wB = ", wB

        if wB==0:
            continue
        wF = total - wB
        #print "total (", total,")\nwF = ", wF

        if wF==0:
            break

        sumB += idx*histogram[idx]
        #sumB += idx*hidx

        mB = sumB/wB
        mF = (sum - sumB)/wF
        between = wB* wF*(mB-mF)* (mB-mF)
        
        #print "between = ", between, " >= max=",max
        if between>=max:
           
            threshold1 = idx
            #print "threshold1 = ", threshold1 

            if between>max:
                threshold2=idx
            
            #print "thresh 1 ", threshold1, "\t threshold2 ",threshold2
            max = between
        
        #idx+=1
    
    return (threshold1+ threshold2)/2.0
    

main()
