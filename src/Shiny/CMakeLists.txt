cmake_minimum_required(VERSION 3.15)
project(Shiny)

add_library(Shiny STATIC
    Shiny.h
    ShinyConfig.h
    ShinyData.h
    ShinyMacros.h
    ShinyManager.c
    ShinyManager.h
    ShinyNode.c
    ShinyNode.h
    ShinyNodePool.c
    ShinyNodePool.h
    ShinyNodeState.c
    ShinyNodeState.h
    ShinyOutput.c
    ShinyOutput.h
    ShinyPrereqs.h
    ShinyTools.c
    ShinyTools.h
    ShinyVersion.h
    ShinyZone.c
    ShinyZone.h
)
