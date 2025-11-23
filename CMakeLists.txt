cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(NotSoFastWorking_engine)

set(CMAKE_CXX_STANDARD 23)
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
include_directories(Render/include)
include_directories(ECS/include)
include_directories(ECS/Systems)
include_directories(Engine/include)

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
        Render/include/Camera.h
        Render/src/Camera.cpp
)

set(RENDERER_SOURCES
        Render/include/Camera.h
        Render/src/Camera.cpp
        Render/include/Renderer.h
        Render/src/Renderer.cpp
        Render/include/TextureManager.h
        Render/src/TextureManager.cpp
)

set(ECS_SOURCES
        ECS/include/CoreComponents.h
        ECS/include/System.h
        ECS/include/EntityManager.h
        ECS/include/ComponentArray.h
        ECS/src/EntityManager.cpp
        ECS/include/SystemManager.h
        ECS/Systems/PanningSystem.h
        ECS/include/ComponentManager.h
        ECS/Systems/DrawableSystem.h
        ECS/Systems/ZoomingSystem.h
        ECS/include/Entity.h
)

set(ENGINE_SOURCES
        Engine/include/Engine.h
        Engine/src/Engine.cpp
        Engine/include/Layer.h
        Engine/include/Event.h
        Engine/include/InputEvents.h
        Engine/include/WindowEvents.h
        Engine/include/Level.h
)

add_executable(${PROJECT_NAME} main.cpp
        ${UTILS_SOURCES}
        ${RENDERER_SOURCES}
        ${ECS_SOURCES}
        ${ENGINE_SOURCES}
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
        Render/include
)

target_link_libraries(tests
        GTest::gtest_main
        raylib
)

include(GoogleTest)
gtest_discover_tests(tests)