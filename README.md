# gunz-chain
This project is to make gunz live forever using blockchain imutability. We hope to attain this goal by merging refined gunz client and server, decentralising data management using open source ethereum  blockchain technologie,  applying security patchs regularly, creating a validation censensus base on a gunz "fair-play" algorithme to reward players a tradable token.  If you are interested in making gunz living forever storing it's data on a blockchain and rewarding it's players tradable crypto tokens, then up on the team and help us make gunz great again. 

# gunz-chain Source
It's based on open-gunz, itself based on refined gunz. The goal of this project is to make gunz completely decentralized by using Ethereum open source blockchain technology. Also we aim to reward player with a cryptocurrency that is in term exchangeable on decentralized exchange (DEX) and centralized exchange (CEX). 

This is the Gunz-Chain source repo for GunZ.exe, MatchServer.exe, and associated game tools. It was forked from the Refined GunZ source (https://github.com/Asunaya/RefinedGunz) and updated by the International GunZ (http://igunz.net) private server developers. Then CryptoAdvised forked it to make Gunz a blockchain.

# Building the source for the first time

## Windows:
Requisites:

* GCC x64 Windows: http://tdm-gcc.tdragon.net/download
* CMake 3.7 or later: Download the latest release from https://cmake.org/download/ under "Binary distributions." In the installer, select "Add CMake to the system PATH for all users". [Picture here](https://i.imgur.com/rQHLXX8.png).
* Visual Studio 2017 with Windows XP support and ATL/MFC support free Community edition: https://www.visualstudio.com/downloads/.
  - In the installer, select the `Desktop development with C++,` and on the right under `Summary,` select `Windows XP support for C++` and `MFC and ATL support (x86 and x64)`. [Picture here](https://i.imgur.com/BqXoiXu.png).
* OPENSSL: Download and install in `C:\OpenSSL-Win32` from [here](https://mega.nz/#!jLQWAQBJ!nT3v1FDHO80ikOmzsBZrImUpyh5ozE9mYnxdGXDDKWA)
  - For "copy OpenSSL DLLs to" prompt, choose "The Windows system directory".
  - Next download vs2017 OpenSSL files from [here](https://mega.nz/#!HfwCkIJa!UYvC9Sv2S24PFwHYEzWfrHevISTf1AmD9LuEMI8Yhco)
  - Delete everything in `C:\OpenSSL-Win32` and replace it with the vs2017 files.
* Zlib Download: From [here](https://mega.nz/#!LepTgbTT!AHdYH0Kil1jxaINwhbm5uh7VtjKtcx6vMz6WZVHpCOU) and extract that on your system `C:\Program Files (x86)\zlib`.
  - Update the build-win32.bat file with the correct zlib folder locations on the `call cmake -G` line in notepad.

To build, run `build-win32.bat` in source folder. Wait until it says "Build succeeded" with possibly some warnings in yellow.
Go to `\source\build\win32\bin\Release` or `\source\install` to find final build files.

### Optional: Removing warning MSB8051 during build process
Warning MSB8051: Support for targeting Windows XP is deprecated and will not be present
in future releases of Visual Studio.

To disable the warning open  
`C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\IDE\VC\VCTargets\Platforms\Win32\PlatformToolsets\v141_xp\Toolset.targets`

Replace:  `<VCMessage Code="MSB8051" Type="Warning" Condition="'$(XPDeprecationWarning)' != 'false'" />`  
With:     `<VCMessage Code="MSB8051" Type="Warning" Condition="'$(XPDeprecationWarning)' == 'false'" />`  

## Linux:
Requisites:

* Install the following packages: 
    - sudo apt install cmake
    - sudo apt install zlib1g-dev
    - sudo apt install build-essential checkinstall zlib1g-dev -y
    - sudo apt-get install -y libsodium-dev
    - apt-get install libssl-dev
    - sudo apt-get install libsqlite3-dev
    - sudo apt-get install libasio-dev
    - sudo apt-get install libcurl4-openssl-dev
    - sudo apt-get install libsystemd-dev

To build, run `build-linux.sh` in source folder.

If you are using Windows Subsystem for Linux, and the source is somwhere in `/mnt/c`, during compilation you might get messages saying that some packages are missing. But, if everything is set correctly it should still compile fine. To avoid these messages all together, compile from somwhere in the Windows Subsystem for Linux for example: `/opt/igunz/source`

# Launching local test client for the first time
Requisites:

* Download the server and client files.
	- [Client files](https://github.com/open-gunz/client)
	- [Server files](https://github.com/open-gunz/server)
* Retrieve updated files from `\source\build\win32\bin\Release` and replace GunZ.exe, Launcher.exe, and MatchServer.exe in their respective client/server folders.
* Change IP to `127.0.0.1` in config file --> `C:\Users\[username]\Documents\International GunZ\config.xml`.
* In the server folder, open `server.ini` file in notepad:
  - Change the following: `FREELOGINIP`, `KEEPERIP`, `MONITORIP`, `DBAgentIP` to `127.0.0.1`.
* Launch MatchServer.exe from the server folder.
* Run GunZ.exe from client folder (DO NOT USE Launcher.exe as it will downgrade to what is placed on the website for patching).
* You can also run GunZ.exe on Linux using Wine. Currently everything seems to work, but text rendering is broken and text is unreadable.
* Register a test account within the client and login.

# Contact
Feel free to post any issue in the issues section.  
You can also reach us on our discord via [this](https://discord.gg/5QzQmHdzpe) link.

# Credits
[CryptoAdvised](https://github.com/CryptoAdvised/)(https://github.com/CryptoAdvised/gunz-chain/)

[Crawly](https://github.com/Asunaya) (https://github.com/Asunaya/RefinedGunz)

[SuhBruh](https://github.com/suhbruh) (https://igunz.net)

[Michael Steshenko](https://github.com/Michael-Steshenko) (https://igunz.net)

ThievingSix (https://igunz.net)
