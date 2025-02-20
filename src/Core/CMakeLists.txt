set(ProjectName "Core")


ConstructSolutionDirTree( ${CMAKE_CURRENT_SOURCE_DIR} HeadList SrcList)

#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Core)
#include_directories(${CMAKE_CURRENT_SOURCE_DIR})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HeadList} ${SrcList})

add_library(${ProjectName} STATIC ${HeadList} ${SrcList})
