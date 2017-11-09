import cv2
import time
import numpy as np

DELAY = 0.01
GRID_FOUND = 0

MORPH = 7
CANNY = 250
CONT_AREA = 6000

# color boundaries for red and green roombas
# color_boundaries = [
#     ([17, 15, 100], [50, 56, 200]) # red
# ]

# grid window
_width = 500.0
_height = 500.0
_margin = 0.0

# read webcam video
video_capture = cv2.VideoCapture(0)

corners = np.array([
    [[_margin, _margin]],
    [[_margin, _height+_margin]],
    [[_width+_margin, _height+_margin]],
    [[_width+_margin, _margin]],
])

pts_dst = np.array(corners, np.float32)

while True:
    ret, input_with_contours = video_capture.read()

    if(ret):

        # convert to grayscale
        gray = cv2.cvtColor(input_with_contours, cv2.COLOR_BGR2GRAY)
        # noise removal while keeping edges sharp
        gray = cv2.bilateralFilter(gray, 1, 10, 100)
        # edge detection
        edges = cv2.Canny(gray, 10, CANNY)
        # find contours
        morphed = cv2.getStructuringElement(cv2.MORPH_RECT, (MORPH, MORPH))
        closed = cv2.morphologyEx(edges, cv2.MORPH_CLOSE, morphed)
        _, contours, h = cv2.findContours(closed, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

        for cont in contours:

            # ignore smaller contour areas
            if cv2.contourArea(cont) > CONT_AREA:
                # approximate polygon (decrease # of line segments)
                approx = cv2.approxPolyDP(cont, 0.1*cv2.arcLength(cont, True), True)

                # if rectangle then assume it's the grid
                if(len(approx) == 4):
                    GRID_FOUND = 1
                    pts_src = np.array(approx, np.float32)
                    h, status = cv2.findHomography(pts_src, pts_dst)
                    # do a perspective transform since skewed due to camera angle
                    grid = cv2.warpPerspective(input_with_contours, h, (int(_width+_margin*2), int(_height+_margin*2)))
                    # draw contours on top of image
                    cv2.drawContours(input_with_contours, [approx], -1, (255,0,0), 2)

                else:
                    pass

        cv2.namedWindow('input_with_contours', cv2.WINDOW_NORMAL)
        cv2.imshow('input_with_contours', input_with_contours)

        if GRID_FOUND:
            cv2.imshow('only grid', grid)

        if cv2.waitKey(27) & 0xFF == ord('q'):
            break

        time.sleep(DELAY)

    else:
        break

video_capture.release()
cv2.destroyAllWindows()
