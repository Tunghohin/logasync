file(GLOB_RECURSE srcs CONFIGURE_DEPENDS ./*.h)

add_library(spdlog SHARED ${srcs})

target_include_directories(spdlog PUBLIC .)

set_target_properties(spdlog PROPERTIES 
    LINKER_LANGUAGE CXX
    )
