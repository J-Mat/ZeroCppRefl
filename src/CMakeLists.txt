set(ProjectName "Test")

ConstructSolutionDirTree( ${CMAKE_CURRENT_SOURCE_DIR} HeadList SrcList HppList)

add_subdirectory(Core)

target_include_directories(Core
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/src/Core
)

add_executable(${ProjectName} main.cpp)

target_link_libraries(${ProjectName} PRIVATE Core)

