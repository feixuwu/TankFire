node.exe js\ProtoTool.js ..\..\GameServer\src\13Z\GSProto\GSMessage.js ts GSProto
copy /y GSProto.d.ts ..\GameServer\src\13Z\GSProto


node.exe js\ProtoTool.js ..\..\GameServer\src\lpmj\LpmjProto.js ts LpmjProto
copy /y LpmjProto.d.ts ..\GameServer\src\lpmj\
copy /y ..\GameServer\src\lpmj\LpmjProto.js ..\GameServer\js\lpmj\

pause