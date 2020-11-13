project(3DMesher)

set(HEADER_FILES
        Evaluator.h
        MeditReader.h)


set(SOURCE_FILES
        Evaluator.cpp
        MeditReader.cpp)


# You get to pick a type of library, STATIC, SHARED, or MODULE. If you leave this choice off, the value of BUILD_SHARED_LIBS will be used to pick between STATIC and SHARED.
add_library(Evaluator_lib ${SOURCE_FILES} ${HEADER_FILES})