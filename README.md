## Using avconv
1. installing:
sudo apt-get install libav-tools

2. Converting a video to frames:
avconv -i 2015-05-08-001244.webm -qscale 1 seq/out_%04d.jpg
