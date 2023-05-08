@echo off
set dllPath=%~1
set solutionDir=%~2
set projectDir=%~3
set arch=%~4
set config=%~5

echo Running post-build for %config%

set extName=buffer_set_surface_fix
set dllName=buffer_set_surface_fix
set gmlDir14=%solutionDir%buffer_set_surface_fix.gmx
set ext14=%gmlDir14%\extensions\%extName%
set dllRel=%dllName%.dll
set cppRel=%dllName%.cpp
set cppPath=%ext14%\%cppRel%
set gmlPath=%ext14%\*.gml
set docName=%extName%.html
set docPath=%solutionDir%export\%docName%

echo Copying documentation...
if not exist "%gmlDir14%\datafiles" mkdir "%gmlDir14%\datafiles"
copy /Y %docPath% "%gmlDir14%\datafiles\%docName%"

where /q gmxgen
if %ERRORLEVEL% EQU 0 (
	
	echo Combining the source files...
	type "%projectDir%*.h" "%projectDir%*.cpp" >"%cppPath%" 2>nul
	
	echo Running GmxGen...
	
	gmxgen "%ext14%.extension.gmx" ^
	--copy "%dllPath%" "%dllRel%:%arch%"

) else (

	echo Copying DLLs...
	copy /Y "%dllPath%" "%ext14%\%dllRel%"

	echo postBuild.bat: Warning N/A: Could not find GmxGen - extensions will not be updated automatically. See https://github.com/YAL-GameMaker-Tools/GmxGen for setup.
)