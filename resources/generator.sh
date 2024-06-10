rm -r icons.iconset
mkdir icons.iconset
sips -z 16 16 images/icon.png -o icons.iconset/icon_16x16.png
sips -z 32 32 images/icon.png -o icons.iconset/icon_16x16@2x.png
sips -z 32 32 images/icon.png -o icons.iconset/icon_32x32.png
sips -z 64 64 images/icon.png -o icons.iconset/icon_32x32@2x.png
sips -z 128 128 images/icon.png -o icons.iconset/icon_128x128.png
sips -z 256 256 images/icon.png -o icons.iconset/icon_128x128@2x.png
sips -z 256 256 images/icon.png -o icons.iconset/icon_256x256.png
sips -z 512 512 images/icon.png -o icons.iconset/icon_256x256@2x.png
sips -z 512 512 images/icon.png -o icons.iconset/icon_512x512.png
sips -z 1024 1024 images/icon.png -o icons.iconset/icon_512x512@2x.png
iconutil -c icns icons.iconset -o icons/icon.icns
rm -r icons.iconset
