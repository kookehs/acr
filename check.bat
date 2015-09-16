rd /S /Q "C:/Apex/logs/"
mkdir "C:/Apex/logs/"
pushd "C:/Apex/"
drmemory.exe -brief -logdir C:/Apex/logs/ -- Apex.exe
popd
