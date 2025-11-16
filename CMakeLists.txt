cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(NotSoFastWorking_engine)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_FLAGS_DEBUG "/Zi /Od /RTC1")
set(CMAKE_CXX_FLAGS_RELEASE "/O2")

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
)

include_directories(Utils/include)
include_directories(Renderer/include)
include_directories(ECS/include)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
    endif()
endif()

# Our Project

set(UTILS_SOURCES
        Utils/include/QuadTree.h
        Utils/include/Vector.h
        Utils/include/Rectangle.h
        Utils/src/Rectangle.cpp
        Renderer/include/Camera.h
        Renderer/src/Camera.cpp
)

set(RENDERER_SOURCES
        Renderer/include/Camera.h
        Renderer/src/Camera.cpp
)

set(ECS_SOURCES
        ECS/include/GameObject.h
        ECS/include/Component.h
        ECS/src/GameObject.cpp
)

add_executable(${PROJECT_NAME} main.cpp
        ${UTILS_SOURCES}
        ${RENDERER_SOURCES}
        ${ECS_SOURCES}
        Examples/FollowingCamera.h
)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)


# Для Windows: предотвращает переопределение флагов компилятора родительского проекта
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Тестовый исполняемый файл
add_executable(tests
        Tests/UtilsTest.cpp
        ${UTILS_SOURCES}
)

target_include_directories(tests PRIVATE
        Utils/include
        Renderer/include
)

target_link_libraries(tests
        GTest::gtest_main
        raylib
)

include(GoogleTest)
gtest_discover_tests(tests)