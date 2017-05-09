@echo off
set xv_path=E:\\Vivado\\Vivado\\2016.4\\bin
call %xv_path%/xelab  -wto aaf535a1b7ae465ebdc005cb20c85e2b -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L secureip --snapshot MULTIPLY_func_synth xil_defaultlib.MULTIPLY xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
