# Optional self-checks only: tests are not an assignment deliverable or rubric item.
# Catch2 belongs to the test build only; production targets do not depend on it.
include(FetchContent)

FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.15.3
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(Catch2)

add_executable(craft_tests
    test_math.cpp
)

target_link_libraries(craft_tests PRIVATE
    craft_core
    Catch2::Catch2WithMain
)

list(APPEND CMAKE_MODULE_PATH "${catch2_SOURCE_DIR}/extras")
include(Catch)
catch_discover_tests(craft_tests
    DISCOVERY_MODE PRE_TEST
)
