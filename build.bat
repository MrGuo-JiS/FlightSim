@echo off
chcp 65001
cls
echo ==============================================
echo          FlightSimulator 编译启动脚本
echo ==============================================
echo.

:: 核心命令：直接执行你项目要求的编译指令
mingw32-make -f Makefile.win all

:: 编译成功后自动运行
if %errorlevel%==0 (
    echo.
    echo ✅ 编译成功！
    echo 正在启动飞行模拟器...
    echo.
    cd build\bin
    start FlightSimulator.exe
    cd ..\..
) else (
    echo.
    echo ❌ 编译失败，请检查代码或Makefile
)

echo.
pause
