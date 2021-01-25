#!/bin/bash

# Remove application and repo
flatpak --user remote-delete gnusician-repo

# Copy desktop file and icons for DE
rm ~/.local/share/applications/com.gnusicianproject.gnusician.desktop
rm ~/.local/share/icons/hicolor/512x512/apps/com.gnusicianproject.gnusician.png
rm ~/.local/share/icons/hicolor/256x256/apps/com.gnusicianproject.gnusician.png
rm ~/.local/share/icons/hicolor/128x128/apps/com.gnusicianproject.gnusician.png
rm ~/.local/share/icons/hicolor/64x64/apps/com.gnusicianproject.gnusician.png
rm ~/.local/share/icons/hicolor/32x32/apps/com.gnusicianproject.gnusician.png
rm ~/.local/share/icons/hicolor/24x24/apps/com.gnusicianproject.gnusician.png
rm ~/.local/share/icons/hicolor/16x16/apps/com.gnusicianproject.gnusician.png
