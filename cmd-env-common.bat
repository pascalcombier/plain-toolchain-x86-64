@echo OFF
REM Configure PATH (common tools)
set PATH=%~dp0third-party\bin;%PATH%
REM Configure GDB to find .gdbinit
set HOME=%~dp0src