cmake_minimum_required(VERSION 3.7)

project(Frogger)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# target_include_directories(Frogger PRIVATE ./Includes)
include_directories(./Includes)

add_executable(Frogger
    ./Src/CharsetHandler.cpp
    ./Src/CollidableManager.cpp
    ./Src/PipelineElementManager.cpp
    ./Src/PipelineElements
    ./Src/PipelineElements/PE_Background.cpp
    ./Src/PipelineElements/PE_EventHandler.cpp
    ./Src/PipelineElements/PE_Frog.cpp
    ./Src/PipelineElements/PE_MovingBlock.cpp
    ./Src/PipelineElements/PE_QuitHandler.cpp
    ./Src/PipelineElements/PE_River.cpp
    ./Src/PipelineElements/PE_TimeProvider.cpp
    ./Src/PipelineElements/PE_UpperInfo.cpp
    ./Src/SdlScreenHandler.cpp
    ./Src/SdlUtils.cpp
    ./Src/main.cpp
)


target_link_libraries(Frogger ${SDL2_LIBRARIES})