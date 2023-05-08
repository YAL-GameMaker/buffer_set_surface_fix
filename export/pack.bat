@echo off

if not exist "buffer_set_surface_fix-for-GMS1" mkdir "buffer_set_surface_fix-for-GMS1"
cmd /C copyre ..\buffer_set_surface_fix.gmx\extensions\buffer_set_surface_fix.extension.gmx buffer_set_surface_fix-for-GMS1\buffer_set_surface_fix.extension.gmx
cmd /C copyre ..\buffer_set_surface_fix.gmx\extensions\buffer_set_surface_fix buffer_set_surface_fix-for-GMS1\buffer_set_surface_fix
cmd /C copyre ..\buffer_set_surface_fix.gmx\datafiles\buffer_set_surface_fix.html buffer_set_surface_fix-for-GMS1\buffer_set_surface_fix\Assets\datafiles\buffer_set_surface_fix.html
cd buffer_set_surface_fix-for-GMS1
cmd /C 7z a buffer_set_surface_fix-for-GMS1.7z *
move /Y buffer_set_surface_fix-for-GMS1.7z ../buffer_set_surface_fix-for-GMS1.gmez
cd ..

pause