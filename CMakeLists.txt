cmake_minimum_required (VERSION 2.6)

IF(WIN32)
  LINK_LIBRARIES(ws2_32)
  LINK_LIBRARIES(winmm)
ENDIF()
project (IntWars)

add_subdirectory(dep)
add_subdirectory(gamed)
