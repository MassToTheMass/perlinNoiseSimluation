# Overview

This project simulates perlin noise. The project does so by generating a grid of hidden vectors. Then for each point between those vectors we calculate the distance to the vectors and interpolate those values. After smoothing everything out you will get random noise.

The program currently uses 3d vectors in order to calculate the noise. The third dimension allows us to see the noise evolve. The program travels through the third dimention to see the different frames of noise. There is a limit to the number of frames we draw so when we get to the end we loop back allowing the animation to continue.
