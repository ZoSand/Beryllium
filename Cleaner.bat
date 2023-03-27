@echo off

rmdir /s /q Build
rmdir /s /q .vs
rmdir /s /q .idea

del /s /q *.vcxproj
del /s /q *.vcxproj.filters
del /s /q *.vcxproj.user
del /s /q *.sln