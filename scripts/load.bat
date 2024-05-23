@echo off

REM 启动 OpenOCD 脚本
start cmd /k "%~dp0start_openocd.bat"

REM 暂停几秒以确保 OpenOCD 启动
timeout /t 5 /nobreak

REM 启动 GDB 脚本
start cmd /k "%~dp0start_gdb.bat"
