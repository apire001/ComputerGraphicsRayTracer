# cs130-Basic Ray Tracer

CS 130 OpenGL Graphics Ray Tracer Project by Andrew Pirelli

## Introduction

This program performs ray tracing to generate images using object-oriented design. Objects are placed in the image, and contain their own intersection functionality. Current object types that have been implemented are planes, triangles, circles and meshes.

### Requirements For Compilation and Execution:

```
Access to bolt.cs.ucr.edu server
```

### Install Instructions

```
$ git clone https://github.com/apire001/ComputerGraphicsRayTracer.git
$ cd proj-rt-files
$ scons
$ ./ray_tracer -i input.txt #Output is stored in output.png
```

### Known Bugs

* Hierarchy has not been fully implemented yet. Some meshes may have undefined behaviour
