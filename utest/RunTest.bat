REM Start unit tests

cd %~dp0
set UTESTDIR=%CD%

REM Save project directory path
cd ..
set PROJECT_DIR=%CD%
cd %UTESTDIR%

cd "%VC100%\VC"
call vcvarsall.bat

cd "%UTESTDIR%"
nmake
