@echo off

pushd ..
Setup\Binaries\Premake\Windows\premake5.exe --file=Build.lua vs2022

setlocal
:PROMPT
CHOICE /N /M "Open A-Life Core uses Valve Game Networking Sockets which requires Windows VCPKG. Want me to download it for you real quick? (Y/n)"%1

IF ERRORLEVEL ==2 GOTO END
IF ERRORLEVEL ==1 GOTO SETUP_GNS

:SETUP_GNS

cd /d "%~dp0..\Core\ThirdParty\ValveNetworking"

echo Installing VCPKG to %cd%

echo Getting the GIT to the "...\Open_A-Life\Core\ThirdParty\ValveNetworking"
git clone https://github.com/microsoft/vcpkg "%cd%\vcpkg"

CALL .\vcpkg\bootstrap-vcpkg.bat

echo To continue on, it's HIGHLY recommended that you follow this guide https://github.com/ValveSoftware/GameNetworkingSockets/blob/master/BUILDING.md

REM Locate Visual Studio Developer Command Prompt... Cry if not found
set VS_DEV_CMD="C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\Tools\VsDevCmd.bat"

REM Check if the Developer Command Prompt exists
if not exist %VS_DEV_CMD% (
    echo Couldn't find Visual Studio Developer Command Prompt at %VS_DEV_CMD%
    echo Please get yourself a copy of Visual Studio 2022...
    pause
    GOTO END
)

CALL %VS_DEV_CMD% && .\vcpkg\vcpkg install --triplet=x64-windows
CALL %VS_DEV_CMD% && cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DBUILD_EXAMPLES=ON -DBUILD_TESTS=ON -DUSE_STEAMWEBRTC=ON
CALL %VS_DEV_CMD% && msbuild GameNetworkingSockets.sln /p:Configuration=Release /p:Platform=x64

:END
echo Good Hunting S.T.A.L.K.E.R!
endlocal
popd
pause