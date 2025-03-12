#!/bin/bash

pushd ..
Setup/Binaries/Premake/Linux/premake5 --cc=clang --file=Build.lua gmake2
read -p "Open A-Life Core uses Valve Game Networking Sockets which requires Windows VCPKG. Want me to download it for you real quick? (Y/n)" choice

if [[ "$choice" =~ ^[Nn]$ ]]; then
    echo "Good Hunting, S.T.A.L.K.E.R!"
    exit 0
fi


VCPKG_DIR="$(pwd)/Core/ThirdParty/ValveNetworking/vcpkg"

echo "Installing VCPKG to $VCPKG_DIR"

echo "Getting the GIT to the "...\Open_A-Life\Core\ThirdParty"
git clone https://github.com/microsoft/vcpkg "$VCPKG_DIR"

# Display recommended build guide for GameNetworkingSockets
echo "To continue on, it's HIGHLY recommended that you follow this guide:"
echo "https://github.com/ValveSoftware/GameNetworkingSockets/blob/master/BUILDING.md"

echo "Good Hunting, S.T.A.L.K.E.R!"


popd
