"""
Corner detection function for transforming pixel 
location to metric location. This will be used 
for the zero-velocity update algorithm.

@author: William Fife
"""

import numpy as np
from math import tan, cos, radians

# Constants
ALPHA  = 31.8244 # degrees
PIXLES = np.array([640, 480])

def pixel2metric_linear(Alt, Obj_pix, theta_1 = 0., pixles = PIXLES):
    '''
    Transform object position in camera frame to gym frame
    given: Alt - Altitude, Obj_pix - object coord. in camera frame,
    theta_1 - angle between altitude and LOS vector, 
    pixles - Pixle rectangle.
    '''
    H_p = pixles[1]
    H_m = 2*tan(radians(ALPHA)/2.0)*Alt

    O_m = (Obj_pix/H_p)*H_m

    return O_m





