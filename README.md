░██████╗██████╗░███████╗██╗░░░██╗██████╗░███████╗███╗░░██╗  ███╗░░░███╗███████╗████████╗
██╔════╝██╔══██╗██╔════╝██║░░░██║██╔══██╗██╔════╝████╗░██║  ████╗░████║██╔════╝╚══██╔══╝
╚█████╗░██████╔╝█████╗░░██║░░░██║██████╔╝█████╗░░██╔██╗██║  ██╔████╔██║█████╗░░░░░██║░░░
░╚═══██╗██╔═══╝░██╔══╝░░██║░░░██║██╔══██╗██╔══╝░░██║╚████║  ██║╚██╔╝██║██╔══╝░░░░░██║░░░
██████╔╝██║░░░░░███████╗╚██████╔╝██║░░██║███████╗██║░╚███║  ██║░╚═╝░██║███████╗░░░██║░░░
╚═════╝░╚═╝░░░░░╚══════╝░╚═════╝░╚═╝░░╚═╝╚══════╝╚═╝░░╚══╝  ╚═╝░░░░░╚═╝╚══════╝░░░╚═╝░░░

██╗░░██╗██████╗░██╗░░░██╗██╗░░░░░
██║░██╔╝██╔══██╗██║░░░██║██║░░░░░
█████═╝░██████╔╝██║░░░██║██║░░░░░
██╔═██╗░██╔══██╗██║░░░██║██║░░░░░
██║░╚██╗██║░░██║╚██████╔╝███████╗

Ferran-Hendriks - 2130858

Run program in Debug configuration and x86 (Win32) platform.

Here's how I've got curl to work with Visual Studio 2019 16.7.2:

Download curl zip package from https://curl.haxx.se/download.html (latest verified is: https://curl.haxx.se/download/curl-7.72.0.zip)
Extract downloaded package to a folder of your choice (e.g. C:\curl\)
Open Developer Command Prompt for VS 2017 (see Windows Start menu or %PROGRAMDATA%\Microsoft\Windows\Start Menu\Programs\Visual Studio 2019\Visual Studio Tools\) and cd to C:\curl\winbuild\
Run nmake /f Makefile.vc mode=static. This will build curl as a static library into C:\curl\builds\libcurl-vc-x86-release-static-ipv6-sspi-schannel\
Create a new project in Visual Studio (e.g. a Windows Console Application)
In Project Properties -> VC++ Directories -> Include Directories add C:\curl\builds\libcurl-vc-x86-release-static-ipv6-sspi-schannel\include\
In Project Properties -> VC++ Directories -> Library Directories add C:\curl\builds\libcurl-vc-x86-release-static-ipv6-sspi-schannel\lib\ there
In Project Properties -> Linker -> Input -> Additional Dependencies add libcurl_a.lib, Ws2_32.lib, Crypt32.lib, Wldap32.lib and Normaliz.lib
Try to build a sample program:
#define CURL_STATICLIB
#include <curl\curl.h>

Alternatively you can use vcpkg to install curl:

Get vcpkg from https://github.com/microsoft/vcpkg/archive/2019.08.zip and extract it to a folder of your choice (e.g. C:\vcpkg\)
Open Developer Command Prompt for VS 2017 (see Windows Start menu or %PROGRAMDATA%\Microsoft\Windows\Start Menu\Programs\Visual Studio 2019\Visual Studio Tools\) and cd to C:\vcpkg\
Run bootstrap-vcpkg.bat
Run vcpkg.exe integrate install
Run vcpkg.exe install curl
Create a new C++ project in Visual Studio and you're ready to go - try it with the example above. There's no need to modify project settings.

For more details, visit:
https://stackoverflow.com/questions/53861300/how-do-you-properly-install-libcurl-for-use-in-visual-studio-2017
https://curl.haxx.se/libcurl/