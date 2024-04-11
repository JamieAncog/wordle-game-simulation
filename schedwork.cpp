#ifndef RECCHECK
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
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
bool checkFinished(const size_t dailyNeed, DailySchedule& sched, const AvailabilityMatrix& avail);
bool recursiveHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int*& numShifts,
    int day,
    int currFill
);
bool notMax(int worker, int* numShifts, const size_t maxShifts);

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
    int numDays = (int) avail.size();
    int* numShifts = new int[numDays];
    for (int i = 0; i < numDays; i++){
        numShifts[i] = 0;
    }
    bool val = recursiveHelper(avail, dailyNeed, maxShifts, sched, numShifts, 0, 0);
    delete numShifts;
    return val;
}

bool recursiveHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int*& numShifts,
    int day,
    int currFill
){
    //1) If finished state and valid, save solution, return true
    //Check if schedule is full

    if (checkFinished(dailyNeed, sched, avail)){
        return true;
    }
    //2) For each next possible choice
    //For every worker
    vector<Worker_T> dayToFill;
    sched.push_back(dayToFill);
    for (int i = 0; i < (int) avail[day].size(); i++){
        //2A) Apply choice to state
        Worker_T nurse = i;
        bool isAvail = avail[day][i];
        numShifts[i]++;
        dayToFill.push_back(nurse);
        //2B) If choice is valid, recursive call with current state
        if (isAvail && notMax(i, numShifts, maxShifts)){
            if (currFill == (int) avail[day].size()){
                recursiveHelper(avail, dailyNeed, maxShifts, sched, numShifts, day+1, 0);
            }
            else {
                recursiveHelper(avail, dailyNeed, maxShifts, sched, numShifts, day, currFill+1);
            }
        }
        //2C) Remove choice
        dayToFill.pop_back();
        numShifts[i]--;
    }
    //3) Return false
    return false;
}

bool checkFinished(const size_t dailyNeed, DailySchedule& sched, const AvailabilityMatrix& avail){
    bool stat = true;
    if (sched.size() < avail.size()){
        stat = false;
    }
    for (int i = 0; i < (int)sched.size(); i++){
        if (sched[i].size() != dailyNeed){
            stat = false;
        }
    }
    return stat;
}

bool notMax(int worker, int* numShifts, const size_t maxShifts){
    if (numShifts[worker] < (int) maxShifts){
        return true;
    }
    else {
        return false;
    }
}

