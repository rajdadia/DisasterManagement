/*
 * @Author: Mathieu MICHEL (http://w3.umons.ac.be/staff/Michel.Mathieu/)
 *
 * Copyright (C) 2013  Mathieu MICHEL
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef ROUTINGTABLE_H_
#define ROUTINGTABLE_H_
#include <vector>
#include <list>
#include <string>
#include <queue>
#include <limits>
#include "CastaliaModule.h"




const SimTime string2simTime(const char* x);//added on 22/1/19
const char * simTime2string(SimTime t);//added on 22/1/19

enum RoutingFlag
{
    UNKNOWN = 0,
    VALID = 1,
    INVALID = 2,
    REPAIRABLE = 3,
    BEING_REPAIRED = 4,
};

typedef struct
{
        std::string dstIP;
        unsigned long dstSN;
        bool state;//Valid Destination Sequence Number flag
        RoutingFlag flag;
        int hopCount;
        std::string nextHopAddr;
        std::list<std::string>* precursor;
        std::string dtype;//raj on 27/1/19
        int priority;//raj on 27/1/19
        double reliability;//raj on 21/2/19
        SimTime pDelay;//raj on 21/2/19
        double path_Load; // diana 
}Route;

struct RouteTimer
{
    double lifetime;
    string destination;
    bool canceled;
    string dtype;
    int priority;
};

struct RouteTimerCompare
{
    bool operator()(const RouteTimer &a,const RouteTimer &b)
    {
        return a.lifetime > b.lifetime ;
    }
};

class AodvRoutingTable
{
private:
        std::list<Route>* table;
        priority_queue <RouteTimer,vector<RouteTimer>,RouteTimerCompare > timers;

public:

        AodvRoutingTable();
        ~AodvRoutingTable();

        Route* searchByDest(std::string destination,string type,int prior);//raj on 31/1/19
        //if the route exists it will be updated, else a new route is inserted
        void insertRoute(const std::string& dstIP,unsigned long dstSN,bool state,RoutingFlag flag,int hopCount,const std::string& nextHopAddr,std::list<std::string>* precursor, double lifetime, SimTime pathDelay, double reli, string dtype, int priority, double load_Val );//added by raj on 29/3/19, load-diana 
        void removeRoute(std::string destination, string dtype, int priority);//added by raj on 23/2/19

        unsigned long getDstSN(std::string destination, string dtype, int priority);//added by raj on 23/2/19
        //the method first checks that the newSN is larger than the current SN
        void setDstSN(std::string destination, unsigned long newSN);//added by raj on 23/2/19

        double getLifetime(std::string destination, std::string detype , int prior );
        void setLifetime(RouteTimer* timer, string dtype, int priority);//added by raj on 23/2/19

        std::string getNextHop(std::string destination, string dtype, int priority);//added by raj on 23/2/19
        void setNextHop(std::string destination, string newNextHop, string dtype, int priority);//added by raj on 23/2/19

        RoutingFlag getFlag(std::string destination, string dtype, int priority);//added by raj on 23/2/19
        void setFlag(std::string destination, RoutingFlag newFlag, string dtype, int priority);//added by raj on 23/2/19

        int getHopCount(std::string destination, string dtype, int priority);//added by raj on 23/2/19
        void setHopCount(std::string destination, int newCount, string dtype, int priority);//added by raj on 23/2/19

        //return the validty of the DstSN
        bool getState(std::string destination, string dtype, int priority);//added by raj on 23/2/19
        void setState(std::string destination, bool valid, string dtype, int priority);//added by raj on 23/2/19

        bool isRouteValid(std::string destination, string dtype, int priority);//added by raj on 23/2/19
        bool isPartRouteValid();

        const RouteTimer* getNextExpiredRoute();
        void clearTimerExpired();
        int getTimersSize();
        void resetTimer(string dest,string detype,int prior);

        const std::list<std::string>& getPrecursors(std::string destination, string dtype, int priority);//added by raj on 23/2/19
        void addPrecursor(std::string destination, std::string precursor, string dtype, int priority);//added by raj on 23/2/19
        void deletePrecursor(std::string destination, std::string precursor, string dtype, int priority);//added by raj on 23/2/19

        //this method will update the affectedDst and affectedPre list
        void setLinkFailure(const char* node, std::list<std::string>* affectedDst, std::list<std::string>* affectedPre);
        //this method update the affectedPre list
        void forwardLinkFailure(const char* node, const std::list<std::string>* affectedDst, std::list<std::string>* affectedPre);//added by raj on 23/2/19

        string getRouteFromTable(int j);
};

#endif /* ROUTINGTABLE_H_ */
