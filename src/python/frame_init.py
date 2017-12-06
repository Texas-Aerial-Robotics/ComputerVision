"""
Initialize rotation matrix from local
N-E-D (N) frame to Gym (G) frame 

@author: William Fife
"""

from math import sin, cos, radians
import numpy as np

def T_N_G(mag_phi, MAG_TRANS = False):

    if MAG_TRANS:
        theta = radians(360 - mag_phi)

        return np.array([[ cos(theta), sin(theta), 0],
                         [-sin(theta), cos(theta), 0],
                         [     0     ,     0     , 1]])
    
    mag_phi = radians(mag_phi)
    return np.array([[ cos(mag_phi), sin(mag_phi), 0],
                     [-sin(mag_phi), cos(mag_phi), 0],
                     [       0     ,       0     , 1]])


if __name__=="__main__":

    """
    create a test by initializing multiple magnetometer
    readings and transforming a position vector.
    """

    pos          = np.array([0.0, 5.0, 0.0]).reshape((3,1))
    mag_readings = [0.0, 30.0, 45.0, 60.0, 90.0]

    print "NED position magnitude: " + str(np.linalg.norm(pos))
    print ""
    for theta in mag_readings:
        T       = T_N_G(theta, MAG_TRANS = False)
        new_pos = np.dot(T, pos)
        print new_pos
        print ""
        print "Angle: " + str(theta)
        print ""
        print "Magnitude: " + str(np.linalg.norm(new_pos))
        print "-----------------------------------------------------------------"

    
