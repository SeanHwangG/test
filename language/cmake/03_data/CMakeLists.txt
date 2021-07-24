cmake_minimum_required(VERSION 3.16)

set(var foo)
message(__________parent)
message(var \t ${var})

add_subdirectory(subdir)

message(__________parent after)
# set(var bar PARENT_SCOPE) to modify
message(var \t ${var})
message(child \t ${child})

include(subdir/CMakeLists.txt)

message(__________include after)
message(var \t ${var})
message(child \t ${child})