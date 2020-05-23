#include "LookupGrid.hpp"
#include <cmath>

void LookupGrid::Cell::occupy (Point point) {
    points.push_back(point);
}

bool LookupGrid::Cell::isTaken (Point p, std::function<bool (double)> checkFunc) {
    for (int i=0; i<points.size(); i++) {
        Point cp = points[i];
        double dx = cp.x - p.x;
        double dy = cp.y - p.y;
        double dist2 = dx*dx + dy*dy;
        if (checkFunc(dist2)) return true;
    }
    return false;
}

LookupGrid::LookupGrid(double xrange[], double yrange[], double gridSeparation) {
    this->xrange[0] = xrange[0];
    this->xrange[1] = xrange[1];
    this->yrange[0] = yrange[0];
    this->yrange[1] = yrange[1];
    this->gridSeparation = gridSeparation;
    this->nx = std::ceil((xrange[1]-xrange[0]) / gridSeparation);
    this->ny = std::ceil((yrange[1]-xrange[0]) / gridSeparation);
    cells = new Cell**[nx];
    for(int i = 0; i < nx; ++i) {
        cells[i] = new Cell*[ny];
    }
    for (int i=0; i<nx; i++) {
        for (int j=0; j<ny; j++) {
            cells[i][j] = new Cell();
        }
    }
}

LookupGrid::~LookupGrid() {
    for (int i=0; i<nx; i++) {
        for (int j=0; j<ny; j++) {
            delete cells[i][j];
        }
        delete[] cells[i];
    }
    delete[] cells;
}

bool LookupGrid::isOutside(Point point) {
    double x = point.x;
    double y = point.y;
    return x < xrange[0] || x > xrange[1] || y < yrange[0] || y > yrange[1];
}

void LookupGrid::occupyCoordinates(Point point) {
    Cell* cell = getCellByCoordinates(point);
    cell->occupy(point);
}

bool LookupGrid::isTaken(Point point, std::function<bool(double)> checkFunc) {
    Loc loc = gridLoc(point);
    for (int col = -1; col < 2; ++col) {
      int currentCellX = loc.x + col;
      if (currentCellX < 0 || currentCellX > nx-1) continue;
      Cell** cellRow = cells[currentCellX];

      for (int row = -1; row < 2; ++row) {
        int currentCellY = loc.y + row;
        if (currentCellY < 0 || currentCellY > ny-1) continue;
        Cell* cell = cellRow[currentCellY];
        if (cell->isTaken(point, checkFunc)) return true;
      }
    }
    return false;
}

LookupGrid::Cell* LookupGrid::getCellByCoordinates(Point point) {
    Loc loc = gridLoc(point);
    Cell** row = cells[loc.x];
    Cell* cell = row[loc.y];
    return cell;
}

LookupGrid::Loc LookupGrid::gridLoc (Point p) {
    int xLoc = std::floor((p[0] - xrange[0]) / gridSeparation);
    int yLoc = std::floor((p[1] - yrange[0]) / gridSeparation);
    Loc loc;
    loc.x = xLoc;
    loc.y = yLoc;
    return loc;
}

void LookupGrid::clear() {
    for (int i=0; i<nx; i++) {
        for (int j=0; j<ny; j++) {
            Cell* cell = cells[i][j];
            cell->points.clear();
        }
    }
}

