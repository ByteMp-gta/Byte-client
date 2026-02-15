@echo off
call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"

msbuild "%~dp0MyPlugin.sln" /m "/p:Configuration=Debug" "/p:Platform=GTA-SA"