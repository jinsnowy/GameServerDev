xcopy GameServerDev\Engine\*.h Include\Engine  /S  /Y /D
xcopy GameServerDev\Engine\*.hpp Include\Engine  /S  /Y /D

IF ERRORLEVEL 1 PAUSE