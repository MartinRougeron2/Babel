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

function main()
{
    if [[ $1 == "server" ]]; then
        run_server
    elif [[ $1 == "client" ]]; then
        run_client
    else
        build
    fi
}

main $1