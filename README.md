# Arduino_UKF_Library
 A  (UKF library for Teensy4/Arduino system (or any real time embedded system in general)
This is a compact Unscented Kalman Filter (UKF) library for Teensy4.0/Arduino system (or real time embedded system in general).
- It's not using Eigen (small source code - more simple to understand).
- It's not using C++ Standard Library/std (for embedded consideration).
- If you set `SISTEM_IMPLEMENTASI` to `SISTEM_EMBEDDED_NO_PRINT` in `konfig.h`, the code is platform agnostic (not using any library beside these C header files: `stdlib.h`, `stdint.h`, and `math.h`).
- There's no malloc/new/free dynamic memory allocation for real time application (but using heavy stack local variables, so you need to run it through static memory analyzer if you are really concern about hard real time application).


# The Background
The Extended Kalman Filter is the de facto industrial ...
Unscented Kalman Filter...

This library is made with specific goal for educational purpose (I've made decision to sacrifice speed to get best code readability I could get) while still capable of tackling real-time control system implementation (the code is computed in less than **300 us**! See *Some Benchmark* section below).

Without further ado, first some definition:
![UKF Definition](UKF_Definition.png "Click to maximize if the image rescaling make you dizzy")



LOREM IPSUM DOLOR SI AMET LOREM IPSUM DOLOR SI AMET LOREM IPSUM DOLOR SI AMET LOREM IPSUM DOLOR SI AMET LOREM IPSUM DOLOR SI AMET 



![UKF Calculation](UKF_Calculation.png "Click to maximize if the image rescaling make you dizzy")
