# PID Controller Project Submission

This repository is copied from the Udacity [repository](https://github.com/udacity/CarND-PID-Control-Project).

## Implementation overview

To control steering angle and speed, I used two PID controllers for steering and speed.

# Describe the effect each of the P, I, D components had in your implementation.

P controller make counter steering proportional to the CTE.
Steering angle proportional to the CTE is intuitive solution.
However only with the P controller, it is hard to stabilize driving.
Car won't turns until the CTE get large and when it turns, steering angle is too large
so that it makes zigzag driving and finally cause overshoot.

Short [video](https://youtu.be/A6ItIZPolXY) shows how P controller works.
(P = 0.2, I = 0, D = 0)


D controller makes counter steering proportional to the CTE difference.
It helps to mitigate the issue of P controller described above.
When the P controller makes a sharp turn, D controller makes a counter to it.

Short [video](https://www.youtube.com/HrnMVpECeRI) shows how D controller mitigates the issue in P controller.
(P = 0.2, I = 0, D = 0.4)

I controller makes counter steering proportional to the sum of CTE.
It is a countermeasure of systematic bias.
For example, if the car alignment is not adjusted well and turn to bit right
when steering angle is 0, sum of CTE will be increasing (decreasing, depending on how we define coordinate)
because the CTE has a bias to the right turn.
The experiment in this project is described in [the later section](#check-effect-of-i-controllers).

## Hyperparameters optimization method

I used Twiddle to tune parameters.
After the params are settled, turned off Twiddle and use fixed parameters.
Final parameters chosen:

- coefficient of p: 0.0997
- coefficient of d : 0.806523
- coefficient of i : 0.000783966

## Check effect of I controllers

Added `bias` parameter to test the steering I controllers and its optimization.
Successfully drive around the course with bias = 0 and bias = 0.001 for the steering angle.
Observed higher weight when setting bias to 0.001.
