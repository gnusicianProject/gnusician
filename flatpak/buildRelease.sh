#!/bin/bash
flatpak remote-add --if-not-exists flathub https://dl.flathub.org/repo/flathub.flatpakrepo
flatpak install flathub org.kde.Platform//5.15
flatpak install flathub org.kde.Sdk//5.15

flatpak-builder --repo=repo --force-clean build-dir com.gnusicianproject.gnusician.json

tar -czvf release/repo.tar repo
rm -rf repo
