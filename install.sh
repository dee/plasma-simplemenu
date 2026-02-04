#!/bin/sh

# clean up cache
# rm -rf ~/.cache/plasmashell
# rm -rf ~/.local/share/plasma/plasmoids/org.kde.plasma.simplemenu
# kquitapp6 plasmashell && kstart plasmashell

# build
cd build/Desktop-Release
sudo ninja install
cd ../..
kquitapp6 plasmashell && sleep 1 && kstart plasmashell && echo "✅ Done!"
