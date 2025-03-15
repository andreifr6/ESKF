//
// Created by mmaximo on 28/10/2015.
//

#ifndef CLOCK_H
#define CLOCK_H

class Clock {
public:
    Clock();

    virtual ~Clock();

    /**
     * The number of seconds elapsed since the epoch
     * (1/1/1970 00:00:00 UTC) until logging event was created. */
    static double getTime();
};


#endif //CLOCK_H
