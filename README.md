# Perlin Noise Simulator

## Overview
This project implements a 3D Perlin noise simulator.  

It generates a grid of hidden vectors and calculates interpolated distances for each point between the vectors. Smoothing these values produces natural-looking random noise.  

The third dimension allows the noise to evolve over time. The program animates through this third dimension frame by frame, looping when it reaches the end to create a continuous animation.

---

## Usage
1. Run the `pixels` program on a Linux system with **SFML** installed.  
2. The program will prompt for:
   - **Detail**: number of pixels between each vector (higher values → smoother noise)  
   - **Vectors per dimension**: number of vectors along each axis (higher values → larger noise grid)  
   
> ⚠ Increasing these values significantly will increase computation time exponentially.

---

## Examples

[<img src="manyVectors.gif" width="320" alt="Perlin Noise Demo With Many Vectors">](10x50perlinNoiseVideo.mp4)  
[<img src="detailed.gif" width="320" alt="Perlin Noise Demo With Detail">](50x10perlinNoiseVideo.mp4)

---

## Tech Stack
- C++  
- SFML for visualization  
- Custom Perlin noise implementation
