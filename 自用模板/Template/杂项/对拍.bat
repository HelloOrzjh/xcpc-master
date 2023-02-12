@echo off
:loop
随机数据生成.exe
暴力.exe
正解.exe
fc 暴力.out 正解.out
if not errorlevel 1 goto loop
pause
:end
