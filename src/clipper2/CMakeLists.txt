cmake_minimum_required(VERSION 3.10)
project(Clipper2 VERSION 1.0.6 LANGUAGES C CXX)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS OFF)

option(BUILD_SHARED_LIBS "Build shared libs" OFF)

include(GNUInstallDirs)

set(CLIPPER2_INC
  Clipper2Lib/include/clipper2/clipper.h
  Clipper2Lib/include/clipper2/clipper.core.h
  Clipper2Lib/include/clipper2/clipper.engine.h
  Clipper2Lib/include/clipper2/clipper.export.h
  Clipper2Lib/include/clipper2/clipper.minkowski.h
  Clipper2Lib/include/clipper2/clipper.offset.h
  Clipper2Lib/include/clipper2/clipper.rectclip.h
)

set(CLIPPER2_SRC
  Clipper2Lib/src/clipper.engine.cpp
  Clipper2Lib/src/clipper.offset.cpp
  Clipper2Lib/src/clipper.rectclip.cpp
)

# 2d version of Clipper2
add_library(Clipper2 ${CLIPPER2_INC} ${CLIPPER2_SRC})

target_include_directories(Clipper2
  PUBLIC Clipper2Lib/include
)

if (WIN32)
  target_compile_options(Clipper2 PRIVATE /W4 /WX)
else()
  target_compile_options(Clipper2 PRIVATE -Wall -Wextra -Wpedantic -Werror)
  target_link_libraries(Clipper2 PUBLIC -lm)

endif()

set_target_properties(Clipper2 PROPERTIES FOLDER Libraries
                                         VERSION ${CREALITYPRINT_VERSION}
                                         SOVERSION ${CREALITYPRINT_VERSION_MAJOR}
                                         PUBLIC_HEADER "${CLIPPER2_INC}"
)

