# Quantlab
Quantlab Project
Pranav Srinivasan

 Quantlab Take Home Assignment

This code takes in an input file in the form of a csv called input.csv. This input
represents stock trades and is of the form (time, symbol, quantity price). Using this data
the code returns an output csv file of the form symbol, <symbol>,<MaxTimeGap>,<Volume>, <WeightedAveragePrice>,<MaxPrice>.

Code parses using a stringstream and converts into a vector of strings. Then interate through the 
vector and map a vector of ints to the symbol as a key. THen calculate values by iterating through the 
vector of ints. Finally use an ofstream to output to csv file.

Time Taken 1 hr 30 mins
