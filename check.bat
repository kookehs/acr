@echo off

rd /S /Q "C:/Apex/logs/"
mkdir "C:/Apex/logs/"
pushd "C:/Apex/binaries/"
drmemory.exe -batch -brief -logdir C:/Apex/logs/ -- Apex.exe
popd
