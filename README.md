# C-TinkerBoardGPIO
Utilities to access GPIO on tinkerboard. 

Currently is just one C++ application that can be used to send a high signal through a pin of the user's choosing. 

Once compiled you can run the file with the usage "filename xxx" where the "xxx" is the 

The plan is to add several functions, but the basics are now built in: 

A pin can be exported, set to "Output" or "input", and can be set to "high" or "low".

(Note however that nothing interesting can be done with an input pin - that functionality does not yet exist!)


# Caveats
Also please note that I am very, very noobish at C++ so please don't judge too harshly my complete lack of understanding of the differences between char\*, char and string, std::string. 

Any corrections are most welcome. 
