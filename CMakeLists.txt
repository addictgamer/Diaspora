cmake_minimum_required(VERSION 2.6)
project(diaspora)

if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

find_package(CXX11 REQUIRED)
set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAGS}")
set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CXX11_FLAGS}")
set ( CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${CXX11_FLAGS}")
set ( CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${CXX11_FLAGS}")


# Find OpenGL
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

# Find SFML
find_package(SFML 2 COMPONENTS system graphics window audio REQUIRED)

# Find Boost.
find_package(Boost COMPONENTS system filesystem regex REQUIRED)

# And threads.
find_package(Threads)

# Find SQLite
find_package(SQLite REQUIRED)

# Find gengine.
find_package(GEngine REQUIRED)

# Find CEGUI
find_package(CEGUI COMPONENTS OpenGLRenderer REQUIRED)

# Find Libdl #TODO: Windows/mac support.
find_package(Libdl REQUIRED)

find_package(FMOD REQUIRED)

# Add include directories
include_directories(${GLEW_INCLUDE_DIR})
include_directories(${GLM_INCLUDE_DIR})
include_directories(${SFML_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})
include_directories(${SQLITE3_INCLUDE_DIR})
include_directories(${GENGINE_INCLUDE_DIR})
include_directories(${CEGUI_INCLUDE_DIR}/..)
include_directories(${FMOD_INCLUDE_DIR})

# Add the source directory
file(GLOB_RECURSE SOURCE_FILES src/*.cpp src/*.hpp)

add_executable(diaspora ${SOURCE_FILES})

target_link_libraries(diaspora ${OPENGL_LIBRARIES})
target_link_libraries(diaspora ${GLEW_LIBRARIES})
# We need to link to Winsock if we're on Windows
if(WIN32)
  target_link_libraries(diaspora wsock32 ws2_32)
endif()
target_link_libraries(diaspora ${Boost_LIBRARIES})
target_link_libraries(diaspora ${SFML_SYSTEM_LIBRARY_RELEASE} ${SFML_GRAPHICS_LIBRARY_RELEASE} ${SFML_WINDOW_LIBRARY_RELEASE} ${SFML_AUDIO_LIBRARY_RELEASE})
target_link_libraries(diaspora ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(diaspora ${SQLITE3_LIBRARIES})
target_link_libraries(diaspora ${GENGINE_LIBRARIES})
target_link_libraries(diaspora ${CEGUI_LIBRARIES})
target_link_libraries(diaspora ${LIBDL_LIBRARIES})
target_link_libraries(diaspora ${FMOD_LIBRARY})

install(TARGETS diaspora
  RUNTIME DESTINATION bin COMPONENT Runtime
)

install(DIRECTORY data DESTINATION share/diaspora )
