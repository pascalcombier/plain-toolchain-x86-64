@echo OFF
REM Configure PATH
set PATH=%~dp0third-party\bin\mingw64\bin;%PATH%
REM Configure the environment
CALL "%~dp0cmd-env-common.bat"
CALL "%~dp0cmd-USER-ENVIRONMENT.bat"
