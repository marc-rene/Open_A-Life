@echo off

echo Installing Vulkan API...
timeout 5
cd redist
.\VulkanSDK-1.3.268.0-Installer.exe

echo Installing SDL2...
timeout 5

git clone https://github.com/libsdl-org/SDL.git -b SDL2
cd SDL
mkdir build
cd build
../configure
make
sudo make install