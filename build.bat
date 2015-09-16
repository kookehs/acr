@echo off

rd /S /Q "C:/Apex/binaries/"
mkdir "C:/Apex/binaries/"

pushd "C:/Apex/src/Apex/"
copy * "C:/Apex/binaries/"
popd

pushd "C:/Apex/binaries/"

rem Comment: -D for constants and macros
rem Comment: -EHsc for exception handling
rem Comment: -FC for full file paths in error messages
rem Comment: -Fe for renaming executable
rem Comment: -MT for multithreaded executable
rem Comment: -O2 for fast code
rem Comment: -w for warning suppression
rem Comment: -Zi for full debugging information
cl -EHsc -FC -Zi -w -MT -DSFML_STATIC -FeApex.exe -IC:/Apex/include * advapi32.lib flac.lib freetype.lib gdi32.lib jpeg.lib ogg.lib openal32.lib opengl32.lib sfml-audio-s.lib sfml-graphics-s.lib sfml-network-s.lib sfml-system-s.lib sfml-window-s.lib user32.lib vorbis.lib vorbisenc.lib vorbisfile.lib winmm.lib ws2_32.lib

del *.cpp

popd
