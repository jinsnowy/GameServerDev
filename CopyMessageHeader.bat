xcopy GameServerDev\MessageLib\*.h Include\Protocol /S  /Y
xcopy GameServerDev\MessageLib\*.hpp Include\Protocol /S  /Y

IF ERRORLEVEL 1 PAUSE