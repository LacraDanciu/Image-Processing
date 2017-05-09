@echo off
set xv_path=E:\\Vivado\\Vivado\\2016.4\\bin
call %xv_path%/xsim MULTIPLY_func_synth -key {Post-Synthesis:sim_1:Functional:MULTIPLY} -tclbatch MULTIPLY.tcl -log simulate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
