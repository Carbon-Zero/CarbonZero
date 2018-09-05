
Debian
====================
This directory contains files used to package carbonzerod/carbonzero-qt
for Debian-based Linux systems. If you compile carbonzerod/carbonzero-qt yourself, there are some useful files here.

## carbonzero: URI support ##


carbonzero-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install carbonzero-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your carbonzeroqt binary to `/usr/bin`
and the `../../share/pixmaps/carbonzero128.png` to `/usr/share/pixmaps`

carbonzero-qt.protocol (KDE)

