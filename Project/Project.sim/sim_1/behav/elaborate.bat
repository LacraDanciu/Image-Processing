@echo off
set xv_path=E:\\Vivado\\Vivado\\2016.4\\bin
call %xv_path%/xelab  -wto aaf535a1b7ae465ebdc005cb20c85e2b -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L secureip --snapshot DIVISION_behav xil_defaultlib.DIVISION -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
