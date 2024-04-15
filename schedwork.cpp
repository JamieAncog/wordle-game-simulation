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
bool alrSched(int n, Worker_T id, DailySchedule& sched, int day);
bool recursiveHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int*& shiftCount,
    int day
);

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
    int numWorkers = (int) avail.size();
    int* shiftCount = new int[numWorkers];
    for (int i = 0; i < numWorkers; i++){
        shiftCount[i] = 0;
    }
    bool val = recursiveHelper(avail, dailyNeed, maxShifts, sched, shiftCount, 0);
    delete [] shiftCount;
    return val;
}

bool recursiveHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    int*& shiftCount,
    int day
){
    //1) If finished state and valid, save solution, return true
    //Check if schedule is full
    if (checkFinished(dailyNeed, sched, avail)){
        return true;
    }
    //2) For each next possible choice
    //For every worker

    if (sched.empty()){
        cout << "Moved to day 0" << endl;
        vector<Worker_T> dayToFill;
        sched.push_back(dayToFill);
    }
    else if (sched[day].size() == dailyNeed && sched.size() < avail.size()){
        cout << "Moved to day " << day+1 << endl;
        vector<Worker_T> dayToFill;
        sched.push_back(dayToFill);
        day++;
    }

    for (int i = 0; i < (int) avail[0].size(); i++){
        //2A) Apply choice to state
        Worker_T nurse = i;
        cout << "Try Worker " << i << endl;
        bool isAvail = avail[day][i];
        sched[day].push_back(nurse);
        shiftCount[i]++;
        //2B) If choice is valid, recursive call with current state
        if (isAvail && shiftCount[i] <= (int) maxShifts && !alrSched(0, nurse, sched, day)){
            recursiveHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day);
        }
        //2C) Remove choice
        sched[day].pop_back();
        cout << "Remove Worker " << i << endl;
        shiftCount[i]--;
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

bool alrSched(int n, Worker_T id, DailySchedule& sched, int day){
    if (n < (int) sched[day].size()){
        if (sched[day][n] == id){
            return true;
        }
        n++;
        alrSched(n, id, sched, day);
    }
    return false;
}


