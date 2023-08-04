# Add the cmake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/../cmake)

find_package(pntr)

# Resources
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/)

# pntr_assetsys_test
add_executable(pntr_assetsys_test pntr_assetsys_test.c)
target_link_libraries(pntr_assetsys_test PUBLIC
    pntr
    pntr_assetsys
)
set_property(TARGET pntr_assetsys_test PROPERTY C_STANDARD 99)

# Set up the test
add_test(NAME pntr_assetsys_test COMMAND pntr_assetsys_test)
