# - Try to find
# Once done this will define
#
#  LZ4_FOUND = LZ4_FOUND - TRUE
#  LZ4_INCLUDE_DIR - include directory for LZ4
#  LZ4_LIBRARY   - the library

# first look in user defined locations
find_path (LZ4_INCLUDE_DIR
  NAMES lz4.h
  PATHS $ENV{SDK_PATH}/local/${LIBC}/include/liblz4/ $ENV{SDK_PATH}/local/common/include/liblz4/ /gg/include/liblz4/ /usr/local/include/ /usr/include
  ENV LZ4_INC_DIR
  )

find_library(LZ4_LIBRARY
  NAMES liblz4.a lz4
  PATHS ENV LD_LIBRARY_PATH
  ENV LIBRARY_PATH
  $ENV{SDK_PATH}/local/${LIBC}/lib
  /gg/lib
  /usr/local/lib
  /usr/lib
  ${LZ4_INCLUDE_DIR}/../lib
  ENV LZ4_LIB_DIR
  )

if(LZ4_LIBRARY AND LZ4_INCLUDE_DIR)
  set(LZ4_FOUND TRUE)
endif()

