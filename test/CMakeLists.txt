include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

set(SOURCES *.cpp)

add_executable(tests ${SOURCES})
target_link_libraries(tests PRIVATE gtest_main)
