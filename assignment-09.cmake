cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
)

set(ASSIGNMENT_SOURCES
    rt/integrators/volumeintegrator.h
    rt/integrators/volumeintegrator.cpp
    rt/solids/solid_volume.h
    rt/solids/homogenousvolumebox.h
    rt/solids/homogenousvolumebox.cpp
    rt/solids/homogenousvolumesphere.h
    rt/solids/homogenousvolumesphere.cpp
    rt/solids/perlinvolumesphere.h
    rt/solids/perlinvolumesphere.cpp
    rt/solids/plasma.h
    rt/solids/plasma.cpp   
    main/a_lighting_volume.cpp
    main/plasma_globe.cpp
    rt/solids/glowsphere.cpp
    rt/solids/glowsphere.h


 
    ${MY_ADDITIONAL_SOURCES}
   
)

