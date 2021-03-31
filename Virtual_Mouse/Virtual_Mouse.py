# -*- coding: utf-8 -*-
"""
Created on Tue Jan 16 23:58:20 2018

@author: Sourav
"""

import cv2
import mouse
import numpy as np
import math
import wx 

try:
    del app;
except:
    pass;

def sekil_ciz(event, x, y, flags, param):
    global ix, iy
    if event == cv2.EVENT_LBUTTONDOWN:
        ix, iy = x, y
    elif event == cv2.EVENT_LBUTTONUP:
        x,y
#function to reduce flickering
def isPointClose(x1,y1,x2,y2,scale):
    d=math.sqrt((x1-x2)**2+(y1-y2)**2);
    if d<=scale:     #length<=scale?
        return True;
    else :
        return False;
    
#if __name__ == "__main__":
cap=cv2.VideoCapture(0);    #'http://192.168.0.101:4747/mjpegfeed'); cap에 비디오 캡쳐도구 저장
bg=cv2.flip(cap.read()[1],1);   #카메라 좌우반전
w=np.shape(bg)[1];  #차원 설정
h=np.shape(bg)[0];
bg=bg[1:h-199,250:w].copy();
app=wx.App(False);
(sx,sy)=wx.GetDisplaySize();    #디스플레이 사이즈 sx,sy 저장
########################

#font = cv2.FONT_HERSHEY_SIMPLEX;
#low_range=np.array([123,112,4]);      #hand color thresholds
#high_range=np.array( [250,180,124]);

########################

mouseOn=0;
while True:
    frame=cv2.flip(cap.read()[1],1);
    
    
    roi=frame[1:h-199,250:w].copy();
    temp_roi=roi.copy();
    
    fmask=cv2.absdiff(bg,roi,0);
    fmask=cv2.cvtColor(fmask,cv2.COLOR_BGR2GRAY);
    fmask=cv2.threshold(fmask,10,255,0)[1];
     ####### Morphological Processing #########
    fmask=cv2.erode(fmask,cv2.getStructuringElement(cv2.MORPH_ERODE,(2,2)),iterations=2);
    mask1=cv2.morphologyEx(fmask,cv2.MORPH_CLOSE,\
                           cv2.getStructuringElement(cv2.MORPH_ELLIPSE,(4,4)));
    mask1=cv2.erode(mask1,cv2.getStructuringElement(cv2.MORPH_ERODE,(2,2)),iterations=2);
    cv2.imshow('mask1',mask1);  #mask 창 보여주기 검정 하양으로 인식하고 있는 것을 보여줌
    fg_frame=cv2.bitwise_and(roi,roi,mask=mask1);
    cv2.imshow('fg_frame',fg_frame);    #fg_frame 창 보여주기 인식하고 있는 사물을 제외한 모든 곳을 검정색으로 보여줌
    
    gr_frame=cv2.cvtColor(fg_frame,cv2.COLOR_BGR2GRAY);
    gr_frame=cv2.blur(gr_frame,(10,10));
    bw_frame=cv2.threshold(gr_frame,50,255,0)[1];
    
    ############ Tracking the hand contour 손 인식하는 것을 보여주는 코딩 ################
    
    con=cv2.findContours(bw_frame,cv2.RETR_EXTERNAL,cv2.CHAIN_APPROX_SIMPLE)[0];
    try:
        my_con=max(con,key=cv2.contourArea);
    except:
        my_con=np.array([[[1,0],[1,2],[2,3]]],dtype=np.int32);
        #pass;
    try:
        if cv2.contourArea(my_con)>90:
            
            hull=cv2.convexHull(my_con,True);
            
            leftmost = tuple(hull[hull[:,:,0].argmin()][0]) 
            rightmost = tuple(my_con[my_con[:,:,0].argmax()][0]) 
            topmost = tuple(hull[hull[:,:,1].argmin()][0]) 
            bottommost = tuple(my_con[my_con[:,:,1].argmax()][0])
            
            
            temp=bottommost[0]+30 #getting the bottom middle of the hand
            cv2.line(roi,topmost,(topmost[0],h-280),(0,242,225),2);
            cv2.line(roi,leftmost,(topmost[0],bottommost[1]-80),(0,242,225),2);
            
            cv2.circle(roi,topmost,5,(255,0,0),-1);
            cv2.circle(roi,leftmost,5,(0,120,255),-1);
            cv2.circle(roi,(temp,bottommost[1]),5,(230,0,255),-1);
            ###################### angle calculate #####################
            x1=topmost[0];y1=topmost[1];
            x2=bottommost[0]+20;y2=bottommost[1];
            x3=leftmost[0];y3=leftmost[1];
            m1=(y2-y1)/(x2-x1) #여기오류
            m2=(y3-y2)/(x3-x2)
            tan8=math.fabs((m2-m1)/(1+m1*m2));
            angle=math.atan(tan8)*180/math.pi;
            ############################################################
            
            
            #angle = math.atan2(y2 - y1, x2 - x1) * 180.0 / math.pi;
            length=math.sqrt(math.pow((y2-y1),2)+math.pow((x2-x1),2))
            #print(angle);
            
            if length<50:
                continue
            
            ################### get original pixel location #############
            
            x=sx-((topmost[0]-50)*sx/(w-340));
            y=(topmost[1]*sy/(h-281));
            mouse.move(sx-x,y,absolute=True, duration=.1);


            cv2.putText(roi,str('%d,%d'%(sx-x,y)),topmost, cv2.FONT_HERSHEY_SIMPLEX, .5,(255,255,255),1,cv2.LINE_AA)
            #################### Clicking the mouse ########################
            if angle<15:#손가락 사이 각 체크
                mouse.press(button='left'); # uncomment to activate the left click
                #mouse.double_click(button='left');     #doubleclick
                print('left clicked');          # 유지후에도 움직이는가?
                pass
            else:
                mouse.press(button='left');
                pass
            
    except:
        pass;
    frame[1:h-199,250:w]=roi;
    cv2.rectangle(frame,(150,1),(w-1,h-140),(0,255,0),2);   #첫번쨰->사각형을 그려놓을 이미지 두번째 ->왼쪽 위 조표
    cv2.rectangle(frame,(200,1),(w-40,h-220),(255,0,0),2);  #세번째->오른쪽 아래 좌표 네번째->RGB 다섯번째->선의굵기
    cv2.imshow('frame',frame);
    if cv2.waitKey(2)==ord('r'):    #배경 초기화
        print('Background reset')
        bg=temp_roi;
    elif cv2.waitKey(2)==32:    #스페이스바 2초누르면 종료
        break;
#%%############# Releasing the resources ##############
cv2.destroyAllWindows();
cap.release();




