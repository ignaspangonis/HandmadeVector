cmake_minimum_required(VERSION 3.15)
project(ObjektinisProgramavimas_4)

set(CMAKE_CXX_STANDARD 14)

add_executable(ObjektinisProgramavimas_4
        .idea/misc.xml
        .idea/modules.xml
        .idea/ObjektinisProgramavimas-4.iml
        .idea/vcs.xml
        .idea/workspace.xml
        .gitattributes
        .gitignore
        LICENSE
        README.md src/main.cpp src/container.cpp src/container.h src/func.cpp src/func.h src/Student.cpp src/Student.h Vector.h)
