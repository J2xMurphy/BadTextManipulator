# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TextManipulator_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TextManipulator_autogen.dir\\ParseCache.txt"
  "TextManipulator_autogen"
  )
endif()
