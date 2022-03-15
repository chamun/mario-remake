# About

This repository contains the final project of the Digital Entertainment class
taken at PUCRS university in 2013.

In this class the students learned how to make video-games and the final project
consisted in applying the acquired knowledge to develop a remake of a known
game.

The games should be developed using the [SFML](https://www.sfml-dev.org) library
and the maps should be designed using the [Tiled](https://www.mapeditor.org/)
map editor.

I chose to remake Super Mario World. The physics in this game was completely
written by me.

In 2015 I couldn't compile the project anymore. I can't remember why, but it had
something to do with an update in Ubuntu. I was able to fix it somehow.

It comes with no surprises that in 2022 I couldn't compile the project anymore.
I couldn't even remember which libraries were required to do so.

I'm very proud of the outcome of this project and for some reason I never
published it. I decided to take the effort of fixing it one more time. This
time, inside Docker.

I chose Docker for 3 reasons:

- Make the installation self contained and isolated
- Make it easy for other people to try the project out
- Hopefully being able to easily compile the project in the future

To run the game inside docker, it is necessary that the host system has a
version of the X Window System installed as the container will use X's
forwarding feature to render the game in the host.

The instructions bellow describe how to run the game for Linux and macOS.

For both OS's you'll first need to build the game image:

    bin/build

This process will download all the dependencies that are necessary to compile
and run the game, including the dependencies that are necessary to compile SFML
2.0, which was the version the game was built upon. The final size of the image
is around 520MB. Everything is done inside Docker, so you don't need to worry to
clean it up later.

## Instructions for Linux users

After the image is built, just run:

    bin/run

It will start a container and hook it up with the host's X window system and
sound.

## Instructions for macOS users

For macOS users, a bit more work is required and sound is not supported.

Install [XQuartz](https://www.xquartz.org/) and re-start your machine

    brew install xquartz

Enable IGLX for XQuartz

    defaults write org.xquartz.X11 enable_iglx -bool YES

Start XQuartz and run the game with:

    ./bin/run-macos

## Controls:

- Move left and right: A and D
- Run and jump: J and K

Enjoy!
