#!/bin/bash

# Install dependencies if not already
flatpak remote-add --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
flatpak install flathub org.kde.Platform//5.15

# Intstall application from tar file
tar -xvf repo.tar
flatpak --user --if-not-exists remote-add --no-gpg-verify gnusician-repo repo
flatpak --user install gnusician-repo com.gnusicianproject.gnusician
rm -rf repo/

# Create app directory in home
mkdir -p ~/.gnusician
cp -rn ./export/.gnusician ~/

# Copy desktop file and icons for DE
cp export/com.gnusicianproject.gnusician.desktop ~/.local/share/applications/
cp export/icons/hicolor/512x512/apps/com.gnusicianproject.gnusician.png ~/.local/share/icons/hicolor/512x512/apps/
cp export/icons/hicolor/256x256/apps/com.gnusicianproject.gnusician.png ~/.local/share/icons/hicolor/256x256/apps/
cp export/icons/hicolor/128x128/apps/com.gnusicianproject.gnusician.png ~/.local/share/icons/hicolor/128x128/apps/
cp export/icons/hicolor/64x64/apps/com.gnusicianproject.gnusician.png ~/.local/share/icons/hicolor/64x64/apps/
cp export/icons/hicolor/32x32/apps/com.gnusicianproject.gnusician.png ~/.local/share/icons/hicolor/32x32/apps/
cp export/icons/hicolor/24x24/apps/com.gnusicianproject.gnusician.png ~/.local/share/icons/hicolor/24x24/apps/
cp export/icons/hicolor/16x16/apps/com.gnusicianproject.gnusician.png ~/.local/share/icons/hicolor/16x16/apps/
