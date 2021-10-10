#!/usr/bin/env bash

function build()
{
    printf "BUILDING\n"
    cd build
    conan install ..
    cmake .. -G "Unix Makefiles"
    clear
    cmake -build .
    make
    printf "BUILT\n"
}

function run_server()
{
    printf "RUNNING SERVER\n"
    ./build/bin/babel_server
    printf "SERVER STOPPED\n"
}

function run_client()
{
    printf "RUNNING CLIENT\n"
    ./build/bin/babel_client
    printf "CLIENT STOPPED\n"
}

function run_debug_server()
{
    printf "RUNNING SERVER\n"
    valgrind ./build/bin/babel_server
    printf "SERVER STOPPED\n"
}

function run_debug_client()
{
    printf "RUNNING CLIENT\n"
    valgrind ./build/bin/babel_client
    printf "CLIENT STOPPED\n"
}

function main()
{
    if [[ $1 == "server" ]]; then
        run_server
    elif [[ $1 == "client" ]]; then
        run_client
    else
        if [[ $1 == "debug" && $2 == "server" ]]; then
            run_debug_server
        elif [[ $1 == "debug" && $2 == "client" ]]; then
            run_debug_client
        fi
        build
    fi
}

main $1 $2