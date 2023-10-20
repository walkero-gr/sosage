cmake_minimum_required (VERSION 3.2)
project (SCAP)

## Use C++17 and load local CMake modules
set(CMAKE_CXX_STANDARD 17)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../cmake")

set(SCAP_DEPENDENCIES_OKAY true)
set(SCAP_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/../../include")
set(SCAP_LINK_LIBRARIES "")
set(SCAP_COMPILE_DEFINITIONS "")

find_package(LZ4 REQUIRED)
if (LZ4_FOUND)
  list(APPEND SCAP_INCLUDE_DIRECTORIES ${LZ4_INCLUDE_DIR})
  list(APPEND SCAP_LINK_LIBRARIES ${LZ4_LIBRARY})
else()
  message(STATUS "LZ4 is required and not found")
  set(SCAP_DEPENDENCIES_OKAY false)
endif()

find_package(SDL2 REQUIRED)
if (SDL2_FOUND)
  list(APPEND SCAP_INCLUDE_DIRECTORIES ${SDL2_INCLUDE_DIR})
  list(APPEND SCAP_LINK_LIBRARIES ${SDL2_LIBRARY})
else()
  message(STATUS "SDL2 is required and not found")
  set(SCAP_DEPENDENCIES_OKAY false)
endif()

find_package(SDL2_image REQUIRED)
if (SDL2_IMAGE_FOUND)
  list(APPEND SCAP_INCLUDE_DIRECTORIES ${SDL2_IMAGE_INCLUDE_DIR})
  list(APPEND SCAP_LINK_LIBRARIES ${SDL2_IMAGE_LIBRARIES})
else()
  message(STATUS "SDL2 Image is required and not found")
  set(SCAP_DEPENDENCIES_OKAY false)
endif()

find_package(SDL2_ttf REQUIRED)
if (SDL2_ttf_FOUND)
  list(APPEND SCAP_INCLUDE_DIRECTORIES ${SDL2_TTF_INCLUDE_DIR})
  list(APPEND SCAP_LINK_LIBRARIES ${SDL2_TTF_LIBRARIES})
else()
  message(STATUS "SDL2 TTF is required and not found")
  set(SCAP_DEPENDENCIES_OKAY false)
endif()

set(SCAP_SRC
  "../../src/Sosage/Component/Base.cpp"
  "../../src/Sosage/Component/Ground_map.cpp"
  "../../src/Sosage/Third_party/LZ4.cpp"
  "../../src/Sosage/Third_party/SDL.cpp"
  "../../src/Sosage/Third_party/SDL_file.cpp"
  "../../src/Sosage/Utils/asset_packager.cpp"
  "../../src/Sosage/Utils/Packaged_asset_manager.cpp"
  "../../src/Sosage/Utils/Bitmap_2.cpp"
  "../../src/Sosage/Utils/binary_io.cpp"
  "../../src/Sosage/Utils/color.cpp"
  "../../src/Sosage/Utils/conversions.cpp"
  "../../src/Sosage/Utils/error.cpp"
  "../../src/Sosage/Utils/geometry.cpp"
  "../../src/Sosage/Utils/image_split.cpp"
  "../../src/Sosage/Utils/profiling.cpp")

add_executable("SCAP" "SCAP.cpp" ${SCAP_SRC})
target_include_directories(SCAP PUBLIC ${SCAP_INCLUDE_DIRECTORIES})
target_link_libraries(SCAP ${SCAP_LINK_LIBRARIES} "tbb")
target_compile_definitions(SCAP PUBLIC
  ${SCAP_COMPILE_DEFINITIONS}
  "SOSAGE_SCAP" "SOSAGE_PACKAGED")
