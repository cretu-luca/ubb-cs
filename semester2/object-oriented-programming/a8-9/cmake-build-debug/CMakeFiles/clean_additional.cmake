# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\oop_a4_5_kpunkk_67_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\oop_a4_5_kpunkk_67_autogen.dir\\ParseCache.txt"
  "oop_a4_5_kpunkk_67_autogen"
  )
endif()
