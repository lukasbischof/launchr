include_directories(${PROJECT_SRC_DIR}/src)

set(SOURCES main.cpp utilities.h
        confloader.c confloader.h
        Configuration.cpp Configuration.h
        LaunchCommand.cpp LaunchCommand.h
        ConfigurationError.cpp ConfigurationError.h)

add_definitions(-DDEBUG=1)
add_executable(launchr ${SOURCES})
