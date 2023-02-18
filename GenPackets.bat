protoc.exe -I=./Protocol/ --cpp_out=./Include/protocol ./Protocol/Enum.proto
protoc.exe -I=./Protocol/ --cpp_out=./Include/protocol ./Protocol/Struct.proto
protoc.exe -I=./Protocol/ --cpp_out=./Include/protocol ./Protocol/User.proto
IF ERRORLEVEL 1 PAUSE