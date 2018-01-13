# PID Controller Project Submission

This repository is copied from the Udacity [repository](https://github.com/udacity/CarND-PID-Control-Project).

## Implementation overview

To control steering angle and speed, I used two PID controllers for steering and speed.


## Hyperparameters optimization method

I used Twiddle to tune parameters.
After the params are settled, turned off Twiddle and use fixed parameters.
Final parameters chosen:

- coefficient of p: 0.0997
- coefficient of d : 0.806523
- coefficient of i : 0.000783966

Observations in tuning initial parameters given to Twiddle:

Higher coefficient of p makes cars running in a zigzag.
So I set lower value to coefficient of p and higher value to coefficient of d.

## Check effect of I controllers

Added `bias` parameter to test the steering I controllers and its optimization.
Successfully drive around the course with bias = 0 and bias = 0.001 for the steering angle.
Observed higher weight when setting bias to 0.001.
