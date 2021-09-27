@chcp 65001
@echo off
if "%*" == "" (goto empty) else (goto noempty)

:empty
@echo -- params string:
@echo -- mode:
@echo -- file name:
@echo ---+ 06 file mode
@echo ---++ mode = {create, delete}
@echo ---++ file  = file name
goto finish

:noempty
if not "%2" == "" (goto file) else (goto nofile)

:file
if "%1" == "create" goto create
if "%1" == "delete" (goto delete) else (goto failmod)

:failmod
@echo -- params string: %*
@echo -- mode: %1
@echo -- file mode: %2
@echo ---+ novalid mode
goto finish

:nofile
@echo -- params string: %*
@echo -- mode: %1
@echo -- file mode:
@echo ---+ not point file name
goto finish

:create
if exist "%2" (goto filefound) else (goto createfile)

:delete
if exist "%2" (goto deletefile) else (goto nofilefound)

:filefound
@echo -- params string: %*
@echo -- mode: %1
@echo -- file name: %2
@echo ---+ there is file: %2 
goto finish

:nofilefound
@echo -- params string: %*
@echo -- mode: %1
@echo -- file name: %2
@echo ---+ file %2 not found
goto finish

:createfile
copy /b NUL %2
@echo -- params string: %*
@echo -- mode: %1
@echo -- file name: %2
@echo ---+ file %2 is created
goto finish

:deletefile
del %2
@echo -- params string: %*
@echo -- mode: %1
@echo -- file name: %2
@echo ---+ file %2 is deleted
goto finish

:finish
