# Liquid-Player

A Media Player which recognises the emotion of the user and plays a song accordingly. Currently supported emotions are:

* Happy
* Sad
* Neutral

The songs have to be kept in three different folders namely happy, sad and neutral and based on the emotion, a random song is played from the corresponding folder. The song is played as long as long as a face is being detected in the feed obtained from the webcam. The moment no face is detected, the song pauses automatically and then resumes when a face is detected.

## Features separating this from an ordinary media player:

* Emotion recognition
* Automatic pause and resume based on face detection

## Hardware requirements:

A mid-ranged GPU is highly recommended for getting a good FPS value of the CNN based face detector. We have developed and tested this throughly on a gaming laptop with a 4GB NVIDIA GeForce GTX 1050 card and an i7 7700HQ CPU with 8GB RAM on Linux Mint 18.3.
