@echo off

pushd ..\build
    g++ -o raytracer -I ../include ../src/*.cpp
popd