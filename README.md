# Gnusician

Gnusician is an open-source project aimed at being a platform for learning 
to play the guitar. Our goal is to create an app for GNU/Linux that is 
capable of loading score/tab files of existing formats and registering 
in real time if notes are played correctly.

## Building the app
To build the app, you need the following tools:
* cmake
* make
* g++
* qt 5.15 libraries

You can get all the tools from your distros repo. 
For example in debian based distros, run the following:

    sudo apt install make cmake g++ qttools5-dev

With all the required tools installed, build the project with cmake:

    cd gnusician
    mkdir build
    cd build
    cmake ../
    make -j4

## Building the app with flatpak
Alternatively you can build the app using flatpak-builder. Flatpak is a 
cross-distro package managment system. To build flatpak apps you need 
the flatpak and flatpak-builder packages:

    sudo apt install flatpak flatpak-builder

Once you have these packages you can build the flatpak repo by running the
shell script `buildRelease.sh` in the flatpak directory. The app will be built 
automatically. After this all you need to do is install the package by running 
the script `installRepo.sh` from the flatpak/release directory.
The app should now appear in your DE's app drawer. Alternitively you can run it
by running `runGnusician.sh`.

## Running the app
If you have built the app using cmake, then just run the generated
executable with `./gnusician`. If you have built the app using flatpak, the app
should appear in your DE's application drawer.

## Acknowledgements
- work in progress

## Licence
- work in progress