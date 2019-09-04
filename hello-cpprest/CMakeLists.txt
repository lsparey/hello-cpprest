cmake_minimum_required (VERSION 3.8)

find_package(cpprestsdk CONFIG REQUIRED)

add_executable (hello-cpprest "hello-cpprest.cpp" "hello-cpprest.h")

target_link_libraries(hello-cpprest PRIVATE cpprestsdk::cpprest)
