set PROJECT_PATH=C:\Users\yoon\Documents\UnrealProjects\MyThirdPersonGame\Source\ThirdParty\
xcopy Include\networkengine\*.h %PROJECT_PATH%Include\networkengine\  /S  /Y
xcopy Lib\Release\*.lib %PROJECT_PATH%Lib\  /S  /Y
IF ERRORLEVEL 1 PAUSE