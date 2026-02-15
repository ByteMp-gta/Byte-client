@echo off

if defined VSINSTALLDIR (
    call "%VSINSTALLDIR%\VC\Auxiliary\Build\vcvars64.bat"
) else (
    call "C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
    echo VSINSTALLDIR not defined, assuming msbuild is in PATH...
)


msbuild "%~dp0MyPlugin.vcxproj" /m /p:Configuration=DebugGTA-SA /p:Platform=Win32
