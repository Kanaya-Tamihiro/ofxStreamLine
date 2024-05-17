#ifndef LookupGrid_hpp
#define LookupGrid_hpp

#include <vector>
#include <functional>
#include <stdio.h>
#include "Vector.hpp"

class LookupGrid {
public:
    typedef Vector Point;
    
    class Cell {
    public:
        std::vector<Point> points;
        void occupy (Point point);
        bool isTaken (Point p, std::function<bool(double)> checkFunc);
    };
    
    struct Loc {
        int x;
        int y;
    };
    
    double xrange[2];
    double yrange[2];
    int nx, ny;
    double gridSeparation;
    Cell*** cells;
    
    LookupGrid(double xrange[], double yrange[], double gridSeparation);
    ~LookupGrid();
    
    bool isOutside(Point poin);
    void occupyCoordinates(Point point);
    bool isTaken(Point point, std::function<bool(double)> checkFunc);
    Cell* getCellByCoordinates(Point point);
    Loc gridLoc (Point point);
    void clear();
};


#endif /* LookupGrid_hpp */
