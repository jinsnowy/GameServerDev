protoc.exe -I=./Protocol/ --cpp_out=./Include/protocol ./Protocol/Enum.proto
protoc.exe -I=./Protocol/ --cpp_out=./Include/protocol ./Protocol/Struct.proto
protoc.exe -I=./Protocol/ --cpp_out=./Include/protocol ./Protocol/UserProtocol.proto
IF ERRORLEVEL 1 PAUSE