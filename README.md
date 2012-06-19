Evolved Hyena Communication
====================================
Code for "A Comparison of a Communication Strategies in Cooperative Learning" from [GECCO 2012](http://www.sigevo.org/gecco-2012/).

Build Requirements
------------------------------------
* [Qt SDK](http://qt.nokia.com/products/) 4.7 or greater (untested with older versions)
* [Randomlib](http://randomlib.sourceforge.net/)
* [ACML 5.1](http://developer.amd.com/libraries/acml/)

Building
------------------------------------

After Qt is installed, type
`qmake`
to create makefiles, followed by
`make`
to build. The executable will be called
`qthyena`.

Alternatively, load `qthyena.pro` into Qt Creator and build/run from there.
Both methods should work on Linux/Windows/OS X.


Configuring
------------------------------------

Parameters for the evolutionary process and input/output settings are found in `globals.h`.
Descriptions for many settings can be found there.

To enable the GUI, set `GUI = true` in `globals.h`.

Descriptions of node types in the vector trees are in `types.h`.


Input
------------------------------------
Settings are set in in `globals.h`.
The executable takes one argument that is used to give output files unique names--for example, an identification number.


Output
------------------------------------
Each time the program is run, it will dump several output files into the directory it is run from.

Below, ID is the single command-line argument passed to the program or 1 otherwise.

* `bestteam_ID.txt` - A project-specific serialization of the best team from the last generation.  This can be loaded for retesting by setting RETEST_GIVEN in globals.h to the filename to load.
* `data_ID.txt` - A CSV file (using spaces instead of commas) containing data collected at the end of each generation during evolution.  Descriptions of each column of data can be found in `pop.cpp` in the `save_data` function.
* `final_ID.txt` - A CSV file (using spaces instead of commas) containing data collected from a set of retests of the best team from the final generation.  Data in each column is similar, but not identical to, data in `data_ID.txt`.
* `finalvideo_ID.txt` - A project-specific file filled with coordinates of agents that can be read and displayed by the Playback feature seen in the program when GUI is true.  These videos are of the retests of the best team from the final generation.
* `hyena_ID.gv` - A [graphviz](http://www.graphviz.org/) file of the first hyena in the best team of last generation's tree.  This may be good for visualizing what the vector trees look like.
* `seed_ID.txt` - A project-specific file containing the seed used by Randomlib.  May be useful to reproduce results exactly.
* `video_ID.txt` - A project-specific file filled with coordinates of agents that can be read and displayed by the Playback feature seen in the program when GUI is true.  These videos are collected during evolution and display the best team at a given generation.


"Video" Playback
------------------------------------
To playback a recorded file, first take note of the filename.
It will be in the form `video_ID.txt` or `finalvideo_ID.txt` as described in Output above.

Then, set `GUI = true` in `globals.h` and recompile.
Run the program.
When the GUI window opens, select "Play Recorded File" on the right.
Select "Browse" and choose the file to play back.
