
Debian
====================
This directory contains files used to package QUISHd/QUISH-qt
for Debian-based Linux systems. If you compile QUISHd/QUISH-qt yourself, there are some useful files here.

## QUISH: URI support ##


QUISH-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install QUISH-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your QUISH-qt binary to `/usr/bin`
and the `../../share/pixmaps/QUISH128.png` to `/usr/share/pixmaps`

QUISH-qt.protocol (KDE)

