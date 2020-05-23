#include "Stream.hpp"
#include <cmath>

const Vector Stream::ZERO_VECTOR = Vector(0, 0);

Stream::Stream(Vector start, LookupGrid* grid, Option* option) {
    this->option = option;
    points.push_back(start);
    head = start;
    this->start = start;
    state = FORWARD;
    this->ownGridSeparation = option->dt * 0.9;
    ownGrid = new LookupGrid(option->xrange, option->yrange, ownGridSeparation);
    this->grid = grid;
    
    double wideSeparation = option->wideSeparation;
    isShorterThanStreamWideSeparation = [wideSeparation](double dist2) {
        return dist2 < wideSeparation * wideSeparation;
    };
    
    double narrowSeparation = option->narrowSeparation;
    isShorterThanStreamNarrowSeparation = [narrowSeparation](double dist2) {
        return dist2 < narrowSeparation * narrowSeparation;
    };
    
    double ownGridSeparation = this->ownGridSeparation;
    hasCollisionToOwnStream = [ownGridSeparation](double dist2) {
       return dist2 < ownGridSeparation * ownGridSeparation;
   };
}

bool Stream::isSame(double a, double b) {
    return std::fabs(a - b) < 1e-4;
}

bool Stream::getNextValidSeed(Vector* seed) {
    int size = points.size();
    while (lastCheckedSeed < size - 1) {
        lastCheckedSeed++;
        Vector p = points[lastCheckedSeed];
        Vector v = getVelocity(p);
        Vector cp = {p[0] - v[1] * option->wideSeparation, p[1] + v[0] * option->wideSeparation};
        if (!grid->isOutside(cp) && !grid->isTaken(cp, isShorterThanStreamWideSeparation)) {
            lastCheckedSeed--;
            (*seed)[0] = cp[0];
            (*seed)[1] = cp[1];
            return true;
        }
        Vector op = {p[0] + v[1] * option->wideSeparation, p[1] - v[0] * option->wideSeparation};
        if (!grid->isOutside(op) && !grid->isTaken(op, isShorterThanStreamWideSeparation)) {
            (*seed)[0] = op[0];
            (*seed)[1] = op[1];
            return true;
        }
    }
    return false;
}

bool Stream::next() {
    while (true) {
        if (state == FORWARD) {
            Vector point;
            bool hasForward = growForward(&point);
            if (hasForward) {
                points.push_back(point);
                ownGrid->occupyCoordinates(point);
                head = point;
                bool shouldPause = notifyPointAdded(point);
                if (shouldPause) return false;
            } else {
                if (option->forwardOnly) {
                    state = DONE;
                } else {
                    head = start;
                    state = BACKWARD;
                }
            }
        }
        if (state == BACKWARD) {
            Vector point;
            bool hasBackward = growBackward(&point);
            if (hasBackward) {
                points.insert(points.begin(), point);
                ownGrid->occupyCoordinates(point);
                head = point;
                bool shouldPause = notifyPointAdded(point);
                if (shouldPause) return false;
            } else {
                state = DONE;
            }
        }
        if (state == DONE) {
            for (int i=0; i<points.size(); i++) {
                grid->occupyCoordinates(points[i]);
            }
            return true;
        }
    }
    return false;
}

bool Stream::growForward(Vector* result) {
    Vector velocity = rk4(head, option->dt);
    if (velocity == ZERO_VECTOR) return false;
    return growByVelocity(head, velocity, result);
}

bool Stream::growBackward(Vector* result) {
    Vector velocity = rk4(head, option->dt);
    if (velocity == ZERO_VECTOR) return false;
    return growByVelocity(head, velocity * -1, result);
}

bool Stream::growByVelocity(Vector pos, Vector velocity, Vector* result) {
    Vector candidate = pos + velocity;
    if (grid->isOutside(candidate)) return false;
    if (grid->isTaken(candidate, isShorterThanStreamNarrowSeparation)) return false;
    if (ownGrid->isTaken(candidate, hasCollisionToOwnStream)) return false;
    (*result)[0] = candidate[0];
    (*result)[1] = candidate[1];
    return true;
}

bool Stream::notifyPointAdded(Vector point) {
    bool shouldPause = false;
    if (option->onPointAdded != nullptr) {
      Vector prev = points[state == FORWARD ? points.size() - 2 : 1];
      shouldPause = option->onPointAdded(point, prev);
    }
    return shouldPause;
}

Vector Stream::getVelocity (Vector point) {
    Vector p = option->vectorFunc(point);
    p.normalize();
    return p;
}

Vector Stream::rk4(Vector point, double dt) {
    Vector k1 = getVelocity(point);
    Vector k2 = getVelocity(point + k1 * (dt*0.5));
    Vector k3 = getVelocity(point + k2 * (dt*0.5));
    Vector k4 = getVelocity(point + k3 * dt);
    return k1*(dt/6) + k2*(dt/3) + k3*(dt/3) + k4*(dt/6);
}

Stream::~Stream() {
    delete ownGrid;
}
