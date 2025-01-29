# - Try to find YAML
# Once done this will define
#
#  YAML_FOUND = YAML_FOUND - TRUE
#  YAML_INCLUDE_DIR - include directory for Yaml
#  YAML_LIBRARIES   - the libraries (as targets)

# first look in user defined locations
find_path (YAML_INCLUDE_DIR
  NAMES yaml.h
  PATHS $ENV{SDK_PATH}/local/${LIBC}/include/ $ENV{SDK_PATH}/local/common/include/ /gg/include/ /usr/local/include/ /usr/include
  ENV YAML_INC_DIR
  )

find_library(YAML_LIBRARIES
  NAMES yaml
  PATHS ENV LD_LIBRARY_PATH
  ENV LIBRARY_PATH
  $ENV{SDK_PATH}/local/${LIBC}/lib
  /gg/lib
  /usr/local/lib
  /usr/lib
  ${YAML_INCLUDE_DIR}/../lib
  ENV YAML_LIB_DIR
  )

if(YAML_LIBRARIES AND YAML_INCLUDE_DIR)
  set(YAML_FOUND TRUE)
endif()

