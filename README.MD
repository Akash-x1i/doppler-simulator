# Doppler Simulator

A lightweight interactive visualizer of the Doppler effect built in C89 using Raylib. It demonstrates how sound waves compress or stretch as a moving sound source approaches or recedes from an observer, with controls to adjust both the object's velocity and wave frequency in real time.

## Snapshots:

### Mach 0.5
![Mach 0.5, 4 Hz](snapshots/Mach_0.5.png)



### Mach 1.0
![alt text](snapshots/Mach_1.png)



### Mach 2.0
![Mach 2, 5 Hz](snapshots/Mach_2.png)



### Stack
- **Language:** C (C89)
- **Framework / runtime:** Raylib (2D graphics library)


### How to run it
Compile with gcc and link Raylib:
```bash
gcc doppler.c -o doppler -lraylib
./doppler
```
`NOTE: Requires Raylib to be installed on your system.`

**Controls:**
- Arrow keys: Move the sound source
- Shift + Up/Down: Adjust object speed (Mach number)
- Ctrl + Up/Down: Change wave frequency
- I: Toggle help display

### How it fits together:

 The program runs a real-time loop that spawns concentric waves at the position of a moving object, then propagates those waves outward. The object moves on a 2D canvas in response to keyboard input. When the object moves faster (higher Mach number), the waves bunch up in the direction of motion, visually demonstrating the Doppler effect. All parameters—frequency, object speed, and wave propagation—are displayed live in an on-screen legend.