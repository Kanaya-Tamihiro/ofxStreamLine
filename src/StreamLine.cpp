#include "StreamLine.hpp"

StreamLine::StreamLine (Option* option) {
    this->option = option;
    
    if (option->wideSeparation <= 0) {
        option->wideSeparation = 1.0 / std::max(option->xrange[1] - option->xrange[0], option->yrange[1] - option->yrange[0]);
    }
    if (option->narrowSeparation <= 0) {
        option->narrowSeparation = option->wideSeparation * 0.5;
    }
    
    this->lookupGrid = new LookupGrid(option->xrange, option->yrange, option->wideSeparation);
    stream = new Stream(option->seed, lookupGrid, option);
}

void StreamLine::step() {
    for (int i = 0; i < option->stepsPerIteration; ++i) {
        if (stream == nullptr) return;
        if (stream->next()) {
            addFinishedStream();
            nextStream();
        }
    }
}

void StreamLine::stepAll() {
    while (stream != nullptr) {
        step();
    }
}

void StreamLine::clear() {
    lookupGrid->clear();
    for (int i=0; i<finishedStreams.size(); i++) {
        delete finishedStreams[i];
    }
    delete stream;
    finishedStreams.clear();
    stream = new Stream(option->seed, lookupGrid, option);
}

bool StreamLine::nextStream() {
    while (finishedStreams.size() > 0) {
        Stream* finished = finishedStreams[0];
        Vector seed;
        bool hasSeed = finished->getNextValidSeed(&seed);
        if (hasSeed) {
            stream = new Stream(seed, lookupGrid, option);
            return true;
        } else {
            finishedStreams.erase(finishedStreams.begin());
            delete finished;
        }
    }
    return false;
}

void StreamLine::addFinishedStream() {
    if (stream->points.size() > 1) {
        finishedStreams.push_back(stream);
        stream = nullptr;
        if (option->onStreamAdded != nullptr)
            option->onStreamAdded(&(stream->points));
    }
    else {
        delete stream;
        stream = nullptr;
    }
}

StreamLine::~StreamLine() {
    delete lookupGrid;
    delete stream;
    for (int i=0; i<finishedStreams.size(); i++) {
        delete finishedStreams[i];
    }
    delete option;
}
