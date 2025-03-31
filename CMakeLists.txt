cmake_minimum_required(VERSION 3.5.0)


project(stm32f4xx_tftlcd_update 
  LANGUAGES ASM C CXX
)

set(EXECUTABLE ${PROJECT_NAME}.elf)
set(LINKER_FILE ${CMAKE_SOURCE_DIR}/src/STM32F407IGTX_FLASH.ld)

# 해당 폴더의 파일만 찾는다.
file(GLOB SRC_FILES CONFIGURE_DEPENDS
  src/*.c
)

# 해당 폴더를 포함해서 하위 폴더까지의 파일도 찾는다.
file(GLOB_RECURSE SRC_FILES_RECURSE CONFIGURE_DEPENDS
  src/Core/*.c
  src/Core/bsp/*.c
  src/Core/bsp/Src/*.c
  src/Drivers/*.c
)

# Build the executable based on the source files
add_executable(${EXECUTABLE}  
  ${SRC_FILES}
  ${SRC_FILES_RECURSE}

  src/Core/Startup/startup_stm32f407igtx.s
  )

target_compile_definitions(${EXECUTABLE} PRIVATE
    -DSTM32F407xx
)

# List of includ directories
target_include_directories(${EXECUTABLE} PRIVATE
  src 
  src/Core/Inc
  src/Core/bsp
  src/Core/bsp/Inc
  src/Drivers/CMSIS/Device/ST/STM32F4xx/Include
  src/Drivers/CMSIS/Include
  src/Drivers/STM32F4xx_HAL_Driver/Inc
  )

# Compiler options
target_compile_options(${EXECUTABLE} PRIVATE
  -mcpu=cortex-m4
  -mthumb
  
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard

  -fdata-sections
  -ffunction-sections

  -Wall
  -O0
  -g3
  )

# Linker options
target_link_options(${EXECUTABLE} PRIVATE
  -T${LINKER_FILE}
  -mcpu=cortex-m4
  -mthumb
  -mfpu=fpv4-sp-d16
  -mfloat-abi=hard
  -specs=nano.specs
  -lc
  -lm
  -Wl,-Map=${PROJECT_NAME}.map,--cref
  -Wl,--gc-sections
  -Xlinker -print-memory-usage -Xlinker
)

if(CMAKE_OBJCOPY)
  add_custom_command(
      TARGET ${EXECUTABLE} POST_BUILD
      COMMAND ${CMAKE_OBJCOPY} -O binary ${EXECUTABLE} ${PROJECT_NAME}.bin
      COMMAND ${CMAKE_OBJCOPY} -O ihex ${EXECUTABLE} ${PROJECT_NAME}.hex
      COMMENT "Generating .bin and .hex files"
  )
else()
  message(WARNING "CMAKE_OBJCOPY not found. Cannot generate .bin and .hex files.")
endif()