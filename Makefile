simulatormake: Simulator.cpp Cluster.cpp  JobRequest.cpp ResourceUnit.cpp Scheduler.cpp 
g++ -std=c++11 -o simulator Simulator.cpp Cluster.cpp  JobRequest.cpp ResourceUnit.cpp Scheduler.cpp  