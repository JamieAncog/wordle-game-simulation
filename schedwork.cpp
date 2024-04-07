#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool checkFinished(const size_t dailyNeed, DailySchedule& sched);
bool recursiveHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int day,
    int currFill
);
bool checkMax();

// Add your implementation of schedule() and other helper functions here


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    recursiveHelper(avail, dailyNeed, maxShifts, sched, 0);
}

bool recursiveHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int day,
    int currFill
){
    //1) If finished state and valid, save solution, return true
    //Check if schedule is full

    if (checkFinished(dailyNeed, sched)){
        return true;
    }
    //2) For each next possible choice
    for (int i = 0; i < avail[0].size(); i++){
        //2A) Apply choice to state
        int k = 0;
        int free = avail[day][k];
        while (free != 1 && k < avail[day].size()){
            free = avail[day][k];
            k++;
        }
        sched[day].push_back(free);
        //2B) If choice is valid, recursive call with current state
        if (checkMax()){
            if (currFill == avail[day].size()){
                recursiveHelper(avail, dailyNeed, maxShifts, sched, day+1, 0);
            }
            else {
                recursiveHelper(avail, dailyNeed, maxShifts, sched, day, currFill+1);
            }
        }
        //2C) Remove choice
        sched[day].pop_back();
    }
    //3) Return false
    return false;
}

bool checkFinished(const size_t dailyNeed, DailySchedule& sched){
    bool stat = true;
    for (int i = 0; i < (int)sched.size(); i++){
        if (sched[i].size() != dailyNeed){
            stat = false;
        }
    }
    return stat;
}

bool checkMax(){
    return false;
}

