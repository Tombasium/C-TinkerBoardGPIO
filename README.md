# C-TinkerBoardGPIO
Utilities to access GPIO on tinkerboard. 

Currently is just one C++ application that can be used to send a high signal through a pin of the user's choosing. 

Once compiled you can run the file with the usage "filename xxx" where the "xxx" is the number of the pin (in Tinkerboard language - see the mapping declared near the top of the file for details) that you want to activate.

The program as-is will export that pin, set it to output and high, wait 100ms, set it low then unexport.


The plan is of course to add several more functions - though the basics are now accessible and as much can be done in this as through normal command line operations. 

A pin can be exported, set to "Output" or "input", and can be set to "high" or "low".

Note however that nothing interesting can be done with an input pin - you can set it to input but there are no methods for actually interacting with or reading that data!


# Caveats
Also please note that I am very, very noobish at C++ so please don't judge too harshly my complete lack of understanding of the differences between char\*, char and string, std::string. 

Any corrections are most welcome. 
