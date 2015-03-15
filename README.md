## LowelMakes CPP Course Project: FocusStacking

### Purpose
The output of this program will be an STL file, which is a vector based 3D format, which will represent the input a series of images taken from an electron microscope.  The intention is so that items of interest found with the electron microscope can be 3D printed, or saved and used for 3d modeling.

### Project Components


__ImageServer:__ Stores sets of images called FocusStacks, and associated post-processing data from various sources. This component acts as a central repository of stacks and 

__AcquisitionSystem:__ Acquires data, controls hardware (e.g. stepper motors) and cameras and creates a package to be sent to ImageServer. If available, physical measurement units are also passed. A simpler acquisition system could use a human to load and identify images and set parameters.

__FocusProcessor:__ Post-processes data to label stacks, partially or fully. Can provide probabilistic information. Can use humans to process data. Real-time transfer of partially processed data for others to review. Identifies method and other information such as who post-processed data.

__3d processor:__ Uses post-processed data stored in server to display point-clouds or reconstructed surfaces in 3D. Can also export data in standard 3d formats to be printed.
Regards


### Links
1. [Electron microscope, fitted for FocusStacking](http://www.savazzi.net/photography/mitutoyo_fs-60.htm)
3. [Focus Stacking, Wikipedia](https://en.wikipedia.org/wiki/Focus_stacking)
3. [Electon Microscope, Wikipedia](https://en.wikipedia.org/wiki/Electron_microscope)
4. [STL file, Wolfram](http://reference.wolfram.com/language/ref/format/STL.html)
5. [Learn Markdown](https://github.com/adam-p/markdown-here/wiki/Markdown-Cheatsheet)
