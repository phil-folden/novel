# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\text1_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\text1_autogen.dir\\ParseCache.txt"
  "text1_autogen"
  )
endif()
