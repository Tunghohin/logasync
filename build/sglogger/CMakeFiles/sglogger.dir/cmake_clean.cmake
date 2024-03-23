file(REMOVE_RECURSE
  "libsglogger.pdb"
  "libsglogger.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/sglogger.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
