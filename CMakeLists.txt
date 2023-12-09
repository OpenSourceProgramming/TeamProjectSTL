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

add_library(common_library set_avl.cc)

# 실행 파일 설정
# 실행 파일명은 main으로 설정
add_executable (main main.cc)
target_link_libraries(main common_library)

add_executable(unitTestRunner test_runner.cc)
target_link_libraries(unitTestRunner common_library ${GTEST_LIBRARIES})