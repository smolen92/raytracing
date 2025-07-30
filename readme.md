# Raytracing image generator

A simple raytracing image generator based on https://raytracing.github.io/books/RayTracingInOneWeekend.html

## Compilation 

1. clone the repository
2. run make 
```bash
make
```

## Usage

```bash
ray.out -o=<filename> -t=<thread_count>
```

filename specified must have .bmp or .ppm extension, if no filename is specified output is saved to file output.bmp

if thread count isn't specified or wrong input is entered (string instead of integer, more thread than are available) half of available thread will be used
if all keyword is used as parameter, all available threads are used
