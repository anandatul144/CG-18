cmake_minimum_required(VERSION 3.0)

set(MY_ADDITIONAL_SOURCES
    # Please add your source files here
    #rt/groups/onlyintersection.cpp
    rt/groups/bvhnode.h
    rt/groups/bvhnode.cpp
    rt/groups/bvh.cpp
    rt/bbox.cpp
    rt/bbox.h
)

set(ASSIGNMENT_SOURCES
    rt/groups/bvh.h
    rt/loaders/obj.cpp
    rt/loaders/obj.h
    ${MY_ADDITIONAL_SOURCES}
    main/a_indexing.cpp
)

file(COPY
    models/cow.obj
    models/cow.mtl
    DESTINATION ${CMAKE_BINARY_DIR}/models
)
