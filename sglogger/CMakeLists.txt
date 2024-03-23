file(GLOB_RECURSE srcs CONFIGURE_DEPENDS ./*.h)

add_library(sglogger SHARED ${srcs})

target_include_directories(sglogger PUBLIC .)

set_target_properties(sglogger PROPERTIES 
    LINKER_LANGUAGE CXX
    )
