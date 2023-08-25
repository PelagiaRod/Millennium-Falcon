cmake_minimum_required(VERSION 3.17)
project(Tutorial)

set(CMAKE_CXX_STANDARD 14)

include_directories(Project1)
include_directories(sgg)
include_directories(sgg/include)

add_executable(Tutorial
        .idea/workspace.xml
        bin/assets/fb.png
        "bin/assets/galaxy (1).png"
        bin/assets/galaxy.jpg
        bin/assets/Galaxy.png
        bin/assets/heinkel.png
        bin/assets/images.png
        bin/assets/interstellar.png
        bin/assets/spaceship.png
        bin/assets/starship.png
        bin/assets/wingspan.png
        bin/freetype.dll
        bin/glew32.dll
        bin/libFLAC-8.dll
        bin/libmodplug-1.dll
        bin/libmpg123-0.dll
        bin/libogg-0.dll
        bin/libopus-0.dll
        bin/libopusfile-0.dll
        bin/libvorbis-0.dll
        bin/libvorbisfile-3.dll
        bin/Project1.exe
        bin/Project1.iobj
        bin/Project1.ipdb
        bin/Project1.pdb
        bin/SDL2.dll
        bin/SDL2_mixer.dll
        Project1/x64/Release/Project1.tlog/CL.command.1.tlog
        Project1/x64/Release/Project1.tlog/CL.read.1.tlog
        Project1/x64/Release/Project1.tlog/CL.write.1.tlog
        Project1/x64/Release/Project1.tlog/link.command.1.tlog
        Project1/x64/Release/Project1.tlog/link.read.1.tlog
        Project1/x64/Release/Project1.tlog/link.write.1.tlog
        Project1/x64/Release/Project1.tlog/Project1.lastbuildstate
        Project1/x64/Release/Project1.tlog/Project1.write.1u.tlog
        Project1/x64/Release/game.obj
        Project1/x64/Release/main.obj
        Project1/x64/Release/player.obj
        Project1/x64/Release/Project1.exe.recipe
        Project1/x64/Release/Project1.log
        Project1/x64/Release/vc142.pdb
        Project1/config.h
        Project1/game.cpp
        Project1/game.h
        Project1/gameOpject.h
        Project1/main.cpp
        Project1/player.cpp
        Project1/player.h
        Project1/Project1.vcxproj
        Project1/Project1.vcxproj.filters
        Project1/Project1.vcxproj.user
        sgg/include/graphics.h
        sgg/include/scancodes.h
        sgg/lib/sgg.lib
        sgg/lib/sggd.lib
        Tutorial.sln)
