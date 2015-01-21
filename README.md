parmugit
======

PARallelMUltifurcatingGIbbsTrees - Hierarchical structure in relational data

In this project, carried out at Technical University of Denmark, we implemented a hierarchical relational model in the style of [Schmidt et. al.][1], but with a Bernoulli-likelihood (and appropriate Beta-priors) for simple undirected relational data. 

All of the implementation was done in C++.

Installation and running
-------
The code includes a makefile. To install run "make" in the '/code' directory and this will create the executable "run_parmugit".

From commandline (in the code directory) this can be run by invoking "./run_parmugit $DATA_FILE $NUMBER_OF_ITERATIONS$ $THINNING $OUTPUT_DIR", where the $DATA_FILE is the path to your data (formatted as an edgelist), $THINNING how many samples you want to keep (set to 1 to keep all) and $OUTPUT_DIR is where the results will be written (NB! Needs to already exist when calling the executable). Burn-in will be performed equal to half of the number of iterations specified.


[1]: http://ieeexplore.ieee.org/xpl/login.jsp?tp=&arnumber=6844498&url=http%3A%2F%2Fieeexplore.ieee.org%2Fxpls%2Fabs_all.jsp%3Farnumber%3D6844498


