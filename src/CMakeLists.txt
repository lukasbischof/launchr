project(launchr)
include_directories(${PROJECT_SRC_DIR}/src)

set(SOURCES main.cpp utilities.h confloader.c confloader.h)

add_executable(launchr ${SOURCES})