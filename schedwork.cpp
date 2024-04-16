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
bool isSchedTwice(int n, Worker_T id, DailySchedule& sched, int day, int count);
void printDay(DailySchedule &sched, int day);
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
    if (sched.size() == avail.size())
    {
        if (checkFinished(dailyNeed, sched, avail)){
            return true;
        }
        else {
            return false;
        }
    }
    //2) For each next possible choice
    //For every worker

    if (sched.empty()){
        cout << "Moved to day 0" << endl;
        vector<Worker_T> dayToFill;
        sched.push_back(dayToFill);
    }
    else if (sched[day].size() >= dailyNeed){
        printDay(sched, day);
        cout << "Moved to day " << day+1 << endl;
        vector<Worker_T> dayToFill;
        sched.push_back(dayToFill);
        day++;
    }

    printDay(sched, day);

    for (int i = 0; i < (int) avail[0].size(); i++){
        //2A) Apply choice to state
        Worker_T nurse = i;
        cout << "Try Worker " << i << endl;
        bool isAvail = avail[day][i];
        sched[day].push_back(nurse);
        shiftCount[i]++;
        //2B) If choice is valid, recursive call with current state
        if (isAvail && shiftCount[i] <= (int) maxShifts && !isSchedTwice(0, nurse, sched, day, 0)){
            printDay(sched, day);
            return recursiveHelper(avail, dailyNeed, maxShifts, sched, shiftCount, day);
        }
        if (!isAvail){
            cout << "Not available" << endl;
        }
        if (shiftCount[i] > (int) maxShifts){
            cout << "Max shifts" << endl;
        }
        if (isSchedTwice(0, nurse, sched, day, 0)){
            cout << "Already scheduled" << endl;
        }
        //2C) Remove choice
        cout << "Remove Worker " << i << endl;
        sched[day].pop_back();
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

bool isSchedTwice(int n, Worker_T id, DailySchedule& sched, int day, int count){
    count = 0;
    for (int i = 0; i < (int) sched[day].size(); i++){
        if (sched[day][i] == id){
            count++;
        }
    }
    if (count >= 2){
        return true;
    }
    else {
        return false;
    }
}

void printDay(DailySchedule &sched, int day){
    cout << endl;
    cout << "Day " << day << " Schedule: ";
    for (int i = 0; i < (int) sched[day].size(); i++){
        cout << sched[day][i] << " ";
    }
    cout << endl;
}


