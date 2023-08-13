cmake -DCMAKE_GENERATOR_PLATFORM=x64 -B %cd%\build\ -S %cd%
echo "copy resource"
xcopy res build\res\ /Y
pause