# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Novel_TcpSever_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Novel_TcpSever_autogen.dir\\ParseCache.txt"
  "Novel_TcpSever_autogen"
  )
endif()
