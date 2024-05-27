cmake_minimum_required(VERSION 3.10)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(join_server VERSION ${PROJECT_VESRION})

find_package(Boost REQUIRED COMPONENTS asio)

add_executable(join_server 
	server/join_server.cpp
)

set_target_properties(join_server PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(join_server
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(join_server PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(join_server
    ${Boost_LIBRARIES}
)

if (MSVC)
    target_compile_options(join_server PRIVATE
        /W4
    )
else ()
    target_compile_options(join_server PRIVATE
        -Wall -Wextra -pedantic -Werror
    )

endif()
