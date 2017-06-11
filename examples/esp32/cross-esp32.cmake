#
# CMake Toolchain file for crosscompiling on ARM.
#
# This can be used when running cmake in the following way:
#  cd build/
#  cmake .. -DCMAKE_TOOLCHAIN_FILE=../cross-arm-linux-gnueabihf.cmake
#

# Target operating system name.
set(CMAKE_SYSTEM_NAME Linux)

# Name of C compiler.
set(CMAKE_C_COMPILER "$ENV{CROSS_PATH}/bin/xtensa-esp32-elf-gcc")
set(CMAKE_CXX_COMPILER "$ENV{CROSS_PATH}/bin/xtensa-esp32-elf-g++")

set(ESP_FLAGS "-ffunction-sections -fdata-sections \
  -fstrict-volatile-bitfields \
  -mlongcalls")

set(ESP_GCC_FLAGS "-nostdlib -Wall -Werror \
  -I$ENV{IDF_PATH}/components/mdns/include \
  -I$ENV{IDF_PATH}/components/driver/include \
  -I$ENV{IDF_PATH}/components/spi_flash/include \
  -I$ENV{IDF_PATH}/components/nvs_flash/include \
	-I$ENV{IDF_PATH}/components/tcpip_adapter/include \
	-I$ENV{IDF_PATH}/components/lwip/include/lwip/posix \
	-I$ENV{IDF_PATH}/components/lwip/include/lwip \
	-I$ENV{IDF_PATH}/components/lwip/include/lwip/port \
	-I$ENV{IDF_PATH}/components/esp32/include/ \
	-I$ENV{IDF_PATH}/components/bootloader_support/include/ \
	-I$ENV{IDF_PATH}/components/app_update/include/ \
	-I$(IDF_PATH)/components/soc/esp32/include/ \
  -DDEBUG=0 \
  ${ESP_FLAGS} \
	${LWS_C_FLAGS} -Os \
	-I$ENV{IDF_PATH}/components/nvs_flash/test_nvs_host \
	-I$ENV{IDF_PATH}/components/freertos/include")

  set(CMAKE_C_FLAGS ${ESP_GCC_FLAGS} CACHE STRING "" FORCE)
set(CMAKE_CXX_FLAGS ${ESP_GCC_FLAGS} CACHE STRING "" FORCE)

# Where to look for the target environment. (More paths can be added here)
set(CMAKE_FIND_ROOT_PATH "${CROSS_PATH}")

# Adjust the default behavior of the FIND_XXX() commands:
# search programs in the host environment only.
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)

# Search headers and libraries in the target environment only.
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
