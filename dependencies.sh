#!/bin/bash



# Make dependencies dir and cd to it.
if test -e dependencies
then
	cd dependencies
else
	if mkdir dependencies
	then
		cd dependencies
	else
		echo "Failed to make directory dependencies" && exit 1 # Error
	fi # if mkdir dependencies
fi # if test -e dependencies

# Make debug dir and cd to it.
if test -e debug
then
	cd debug
else
	if mkdir debug
	then
		cd debug
	else
		echo "Failed to make directory dependencies/debug" && exit 1 # Error
	fi # if mkdir debug
fi # if test -e debug



# Grab source code.
echo "Grabbing GENGINE sources."
if test -e gengine
then
	cd gengine

	if git pull
	then
		:
	else
		echo "Failed to update gengine source code!" && exit 1 # Error
	fi # if git pull
else
	#if git clone http://localhost:8080/addictgamer/gengine.git gengine
	#if git clone gitlab@localhost:ciprian/gengine.git gengine
	if git clone git@github.com:addictgamer/GEngine.git gengine
	then
		cd gengine
	else
		echo "Failed to clone gengine source code!" && exit 1 # Error
	fi # if git clone http://localhost:8080/addictgamer/gengine.git gengine
fi # if test -3 gengine



# Now make a debug compile of GENGINE's sources.
echo "Compiling GENGINE sources."
if ./lm
then
	:
else
	echo "Error: Failed to compile GENGINE" && exit 1 # Error
fi # if ./lm
cd ..



# Next dependency here.



# Go back to root directory when all done.
cd ..



exit 0 # Success
