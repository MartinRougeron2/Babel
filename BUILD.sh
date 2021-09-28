#!/usr/bin/env bash

cd build && conan install .. && cmake .. -G "Unix Makefiles" && cmake -build . && make