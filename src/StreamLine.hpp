#ifndef StreamLine_hpp
#define StreamLine_hpp

#include <stdio.h>
#include "Option.hpp"
#include "Stream.hpp"
#include "LookupGrid.hpp"
#include "Vector.hpp"

class StreamLine {
public:
    Option* option;
    LookupGrid* lookupGrid;
    std::vector<Stream*> finishedStreams;
    Stream* stream;
    
    StreamLine(Option* option);
    ~StreamLine();
    void step();
    void stepAll();
    void clear();
    bool nextStream();
    void addFinishedStream();
};

#endif /* StreamLine_hpp */
