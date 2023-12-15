#####################################################
# Copyright INHA_OSAP_004_Froyo
#
# Use of this source code is governed by an MIT-style
# license that can be found in the LICENSE file or at
# https://opensource.org/licenses/MIT.
#
# Contributors: Lee Seung-Bin
# Latest Updated on 2023-12-15
#####################################################

# CMake 프로그램의 최소 버전
cmake_minimum_required(VERSION 3.11)

project(
    # 프로젝트 명
    INHA_OSAP_004_Froyo

    # 프로젝트 설명
    DESCRIPTION "OpenSourceProgramming Set STL Implementation"

    # 사용 언어
    LANGUAGES CXX
)

# 옵션 설정
set (CMAKE_CXX_FLAGS "-O2 -Wall")

# 라이브러리 설정
find_package(GTest REQUIRED)
message("GTest_INCLUDE_DIRS = ${GTest_INCLUDE_DIRS}")

# 실행 파일 설정
# 실행 파일명은 main으로 설정
add_executable (main main.cc)

# add_executable(unitTestRunner test_runner.cc)
# target_link_libraries(unitTestRunner common_library ${GTEST_LIBRARIES})