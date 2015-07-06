# Algorithm Implementation Training

Here test-suites and descriptions of algorithms can be found.  
This could thus be used to practice basic programming, and
simple algorithm implementation. 

The language that is tested is *c++*.

## How to start:
After stepping to the *Training* folder run the command **"./start"**,
followed by the abbreviation of the chosen algorithm.  
A new directory, named with the current date and algorithm-abbreviation,
will be created. This will contain a testing environment for the algorithm,
as well as a started .cpp file, in which the algorithm should be implemented,
following a given interface.  
To test the implementation, run the command "make testrun". 

To get more information about the startup script, run it with the flag **-help**.  
Currently supported algorithms:
- (MaSA):    Maximum subarray
- (BinS): Binary search (Not implemented)
- (StrS): String search
- (DfS):  Depth-first search (Not implemented)
- (BfS):  Bredth-first search (Not implemented)
- (TopS): Topological sort (Not implemented)
- (ConH): Convex hull (Not implemented)


## Creating more tests:
Following are instructions for the creation of other testing algorithms,
or modifications of the testing system.

* Sessions: Folder containing started training sessions
* Suites: Folder containing the test files, and template for those
* Utilities: Folder containing **tt_test** headers, and a template **Makefile**
* start.sh: Script to start a training session

To allow training with a new or modified suite, copy the template in the *Suites* folder,
or modify an existing file. Make sure to rename the file as **<abbreviation>.cpp**, where
the abbreviation is what should be entered when starting a new session.  
Also make sure to fill in all the documentation correctly, and update the startup script.  
A new row will have to be entered into the case of **start.sh**, allowing your new abbreviation. 

