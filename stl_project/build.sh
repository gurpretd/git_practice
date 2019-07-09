#!/bin/bash
set -e 
g++ -c --std=c++11 stl_lib/stl_wrapper.cpp -o out/stl_wrapper.o -I /usr2/c_gdhami/cpp_practice/git_practice/stl_project/include
g++ -c --std=c++11 stl_lib/map_stl.cpp -o out/map_stl.o -I /usr2/c_gdhami/cpp_practice/git_practice/stl_project/include
g++ -c --std=c++11 stl_lib/vector_stl.cpp -o out/vector_stl.o -I /usr2/c_gdhami/cpp_practice/git_practice/stl_project/include
ar rD out/libstl.a out/map_stl.o out/stl_wrapper.o out/vector_stl.o
g++  --std=c++11 app/application.cpp -o out/application.exe  -I /usr2/c_gdhami/cpp_practice/git_practice/stl_project/include -L/usr2/c_gdhami/cpp_practice/git_practice/stl_project/out -lstl



#clang-format-5.0 -i app/*
#clang-format-5.0 -i include/*
#clang-format-5.0 -i stl_lib/*
set +e
/usr2/c_gdhami/lint_cpp/codingstyle/cpplint.py  stl_lib/*
/usr2/c_gdhami/lint_cpp/codingstyle/cpplint.py  app/*
/usr2/c_gdhami/lint_cpp/codingstyle/cpplint.py  include/*

dos2unix  stl_lib/* app/* include/*
