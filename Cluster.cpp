/*
 * Cluster.cpp
 *
 *  Created on: Mar 28, 2015
 *      Author: ravitandon
 */

#include "Cluster.h"

Cluster::Cluster(int numNodes) {
	init(numNodes);
}

Cluster::~Cluster() {
	// TODO Auto-generated destructor stub
}

void Cluster::init(int nNodes){
	numberNodes = nNodes;
	for(int id=1; id<=numberNodes; id++){
		nodeResUnits[id] = 7;
	}
}

void Cluster::addResource(int nodeId, int units){
	nodeResMutex.lock();
	nodeResUnits[nodeId] = nodeResUnits[nodeId] + units;
	nodeResMutex.unlock();
}

void Cluster::removeResource(int nodeId, int units){
	nodeResMutex.lock();
	nodeResUnits[nodeId] = nodeResUnits[nodeId] - units;
	nodeResMutex.unlock();
}

int Cluster::getResource(int units){
	int nodeId = -1;
	nodeResMutex.lock();
	for(int id=1; id<=numberNodes; id++){
		if(nodeResUnits[id]>=units){
			nodeId=id;
			break;
		}
	}
	nodeResMutex.unlock();
	return nodeId;
}

std::vector<JobRequest> Cluster::getNextKJobs(int k){
    vector<JobRequest> jobRequestVec;
    requestVectorLock.lock();
    int len = requestVector.size();
    if(k>len) k=len;
    for(int id=0; id<k; id++){
    	jobRequestVec.push_back(requestVector.at(id));
    }
    requestVector.erase(requestVector.begin(), requestVector.begin()+k);
    requestVectorLock.unlock();
    return jobRequestVec;
}

bool jobSortFunc(JobRequest jr1, JobRequest jr2){
	if(jr1.getFinishTime() == jr2.getFinishTime()){
		return jr1.getUnits()<jr2.getUnits();
	} else {
		return (jr1.getFinishTime() < jr2.getFinishTime());
	}
}

void Cluster::pushJobs(std::vector<JobRequest> vec){
	requestVectorLock.lock();
	for(int id=0; id<vec.size(); id++){
		requestVector.push_back(vec.at(id));
	}
	sortJobQueue();
	requestVectorLock.unlock();
}

void Cluster::sortJobQueue(){ // this is the function that sorts the vector by the finish time
	sort(requestVector.begin(), requestVector.end(), jobSortFunc);
}











