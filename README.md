# PID Controller Project Submission

This repository is copied from the Udacity [repository](https://github.com/udacity/CarND-PID-Control-Project).

## Implementation overview

To control steering angle and speed, I used two PID controllers for steering and speed.


## Hyperparameters optimization method

I used Twiddle.

## Check effect of I controllers

Added `bias` parameter to test the steering I controllers and its optimization.
Successfully drive around the course with bias = 0 and bias = 0.001 for the steering angle.
Observed higher weight when setting bias to 0.001.
