cmake_minimum_required(VERSION 3.25)
project(finn.no-copy)

set(CMAKE_CXX_STANDARD 17)

add_executable(test main.cpp  source/BruktTing.cpp source/BruktTing.h source/nyting.cpp source/nyting.h source/kunder.cpp source/kunder.h source/kunde.cpp source/kunde.h source/kategorier.cpp source/kategorier.h source/kategori.cpp source/kategori.h source/enum.h source/const.h source/LesData3.cpp source/LesData3.h source/Funksjoner.cpp source/Funksjoner.h)
