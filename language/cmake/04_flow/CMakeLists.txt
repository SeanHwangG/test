cmake_minimum_required(VERSION 3.16)
project(04_flow)

function(func arg)
    if(DEFINED arg)
        message(${arg} " is defined")
    else()
        message(${arg} " Not defined") # just a string replacement
    endif()
endfunction()

macro(macr arg)
    if(DEFINED arg) 
        message(${arg} " is defined")
    else()
        message(${arg} " Not defined") # just a string replacement
    endif()
endmacro()

func(HI)
macr(HI)