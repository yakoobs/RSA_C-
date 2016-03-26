cmake_minimum_required(VERSION 3.3)
project(RSA)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror")

set(SOURCE_FILES main.c RSAAlgorithm/Constants.h RSAAlgorithm/RSAAlgorithm.h RSAAlgorithm/RSAAlgorithm.c RSAAlgorithm/RSAAlgorithm.h)
add_executable(RSA ${SOURCE_FILES})