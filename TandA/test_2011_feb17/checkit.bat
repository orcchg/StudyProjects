@ECHO OFF
rem Windows
rem Automatic check system scriprt for offline testing
set TASK_DIR=tasks
set SOLUTION_DIR=solutions
set EXE_DIR=%~dp0
set EXE_DIR=%EXE_DIR%\%SOLUTION_DIR%

rem Check for correct number of parameters
if "%2" == "" (
	echo Usage: %0 chapter task_number
	echo For example: %0 arr 00
	exit /b 1
)

set SUBDIR=%1
set TASKID=%SUBDIR%_%2

set EXE_FILE=%EXE_DIR%\%TASKID%.exe
echo %EXE_FILE%
pushd %TASK_DIR%\%SUBDIR%\%TASKID%\tests
for %%f in (*.dat) do (
	%EXE_FILE% < %%~nf.dat > tmp.out
	fc /w /a tmp.out %%~nf.ans || goto error_exit
rem 	echo %errorlevel% QQQ
rem	if NOT ERRORLEVEL 0 ( 
rem		echo TEST %%~nf FAILED
rem		goto error_exit 
rem	) else 	echo ....................... TEST %%~nf OK
)	
del tmp.out
popd 
exit /b 0


:error_exit
echo TEST FAILED =================================
popd
exit /b 1