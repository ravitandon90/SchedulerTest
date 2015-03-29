/*
 * Scheduler.h
 *
 *  Created on: Mar 28, 2015
 *      Author: ravitandon
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "JobRequest.h"
#include <thread>
#include <vector>
#include "Cluster.h"

class Scheduler {
	Cluster cluster;
	int k;
	std::vector<JobRequest> pendingJobRequests;
	std::vector<ResourceUnit> resourceDispatchRequests;
	int ticks;
	int minUnits;
	int maxUnits;
	int minSteps;
	int maxSteps;
	int jobsPerSecond;

public:
	Scheduler(Cluster c);
	void runScheduler();
	void runDispatcher();
	void runTimeClock();
	void runJobCreator();
	virtual ~Scheduler();
	int getLogicalTime() { return ticks; }

};

#endif /* SCHEDULER_H_ */
