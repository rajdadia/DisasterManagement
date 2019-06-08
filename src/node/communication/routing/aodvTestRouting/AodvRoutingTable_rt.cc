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

#include "AodvRoutingTable_rt.h"
#include <iostream>


using namespace std;

AodvRoutingTable::AodvRoutingTable()
{
    table = new list<Route>();//table is empty at the beginning
}

AodvRoutingTable::~AodvRoutingTable()
{
    for(list<Route>::iterator i=table->begin();i!=table->end();++i)
    {
        Route &r = *i;
        if ((r.precursor)!=NULL)
        {
            delete (r.precursor);
        }
    }
    delete table;
}

string AodvRoutingTable::getRouteFromTable(int j)  //Added by diana only for testing since trace() was not working in this file
{
     int k=-1;
     string val1="V";        
    for(list<Route>::iterator i=table->begin();i!=table->end();++i)
    {    
        Route &r = *i;
        k++;
        if (k==j)
            {   
                std::string str = std::to_string(r.priority);
                std::string str1 = std::to_string(r.hopCount);
                
                val1= r.dstIP+":"+r.dtype+":"+ str +":"+str1;            
                
                return val1;
            }

          
    }
    return val1;
}

Route* AodvRoutingTable::searchByDest(string destination,string dtype,int priority) //added by raj on 23/2/19
{
    if(destination=="")
           return NULL;
    
          
    for(list<Route>::iterator i=table->begin();i!=table->end();++i)
    {    
        Route &r = *i;
       // std::trace()<<"@tingTable::searchByDest: r.dstIP, r.dtype, r.priority, destination, dtype, priority "<<r.dstIP<<" "<<r.dtype<<" "<<r.priority<<" "<<destination<<" "<<dtype<<" "<<priority; 
        if(r.dstIP.compare(destination)==0 && r.dtype.compare(dtype)==0 && r.priority == priority)//added by raj on 23/2/19
        {
                return &r;
        }
    }
    return NULL;
}

void AodvRoutingTable::insertRoute(const std::string& dstIP,unsigned long dstSN,bool state,RoutingFlag flag,int hopCount,const std::string& nextHopAddr,std::list<std::string>* precursor, double lifetime, SimTime pathDelay, double reli,string dtype,int priority, double path_Load)//raj on 29/3/19, load-diana 
{
    Route* r = searchByDest(dstIP,dtype,priority);//raj on 31/1/19
    // Route* r2 = searchByDest(dstIP,"Reliable",priority);//added by raj on 23/2/19
    // Route* r3 = searchByDest(dstIP,"Critical",priority);//added by raj on 23/2/19
    // Route* r4 = searchByDest(dstIP,"Ordinary",priority);//added by raj on 23/2/19

    if(r){
        if(dtype.compare("Delay")==0){
            if (priority==1){
                Route* r1 = searchByDest(dstIP,dtype,1);
                Route* r2 = searchByDest(dstIP,dtype,2);
                if((r1->flag!=VALID || r1->dstSN < dstSN ) && (pathDelay < r1->pDelay)){

                    r2->dstSN = r1->dstSN;
                    r2->hopCount = r1->hopCount;
                    r2->flag = r1->flag;
                    r2->nextHopAddr = r1->nextHopAddr;
                    r2->state = r1->state;
                    r2->reliability=r1->reliability;
                    r2->pDelay = r1->pDelay;
                    r2->path_Load =  r1->path_Load;
                    

                    r1->dstSN = dstSN;
                    r1->hopCount = hopCount;
                    r1->flag = flag;
                    r1->nextHopAddr = nextHopAddr;
                    r1->state = state;
                    r1->reliability=reli;
                    r1->pDelay = pathDelay;
                    r1->path_Load = path_Load; 


                }
                else if((r2->flag!=VALID || r2->dstSN < dstSN ) && (pathDelay < r2->pDelay)){
                    r2->dstSN = dstSN;
                    r2->hopCount = hopCount;
                    r2->flag = flag;
                    r2->nextHopAddr = nextHopAddr;
                    r2->state = state;
                    r2->reliability=reli;
                    r2->pDelay = pathDelay;
                    r2->path_Load = path_Load; 
                }
            }
            else if(priority==2){
                Route* r2 = searchByDest(dstIP,dtype,2);
                if((r2->flag!=VALID || r2->dstSN < dstSN ) && (pathDelay < r2->pDelay)){
                    r2->dstSN = dstSN;
                    r2->hopCount = hopCount;
                    r2->flag = flag;
                    r2->nextHopAddr = nextHopAddr;
                    r2->state = state;
                    r2->reliability=reli;
                    r2->pDelay = pathDelay;
                    r2->path_Load = path_Load; 
                }
            }
            
        }
        

        if(dtype.compare("Reliable")==0){
            if(priority==1){
                Route* r1 = searchByDest(dstIP,dtype,1);
                Route* r2 = searchByDest(dstIP,dtype,2);
                if((r1->flag!=VALID || r1->dstSN < dstSN ) && (reli > r1->reliability)){

                    r2->dstSN = r1->dstSN;
                    r2->hopCount = r1->hopCount;
                    r2->flag = r1->flag;
                    r2->nextHopAddr = r1->nextHopAddr;
                    r2->state = r1->state;
                    r2->reliability=r1->reliability;
                    r2->pDelay = r1->pDelay;
                    r2->path_Load = r1->path_Load; 

                    r1->dstSN = dstSN;
                    r1->hopCount = hopCount;
                    r1->flag = flag;
                    r1->nextHopAddr = nextHopAddr;
                    r1->state = state;
                    r1->reliability=reli;
                    r1->pDelay = pathDelay;
                    r1->path_Load = path_Load; 

                }
                else if((r2->flag!=VALID || r2->dstSN < dstSN ) && (reli > r2->reliability)){
                    r2->dstSN = dstSN;
                    r2->hopCount = hopCount;
                    r2->flag = flag;
                    r2->nextHopAddr = nextHopAddr;
                    r2->state = state;
                    r2->reliability=reli;
                    r2->pDelay = pathDelay;
                    r2->path_Load = path_Load; 
                }

            }
            else if(priority==2){
                Route* r2 = searchByDest(dstIP,dtype,2);
                if((r2->flag!=VALID || r2->dstSN < dstSN ) && (reli > r2->reliability)){
                    r2->dstSN = dstSN;
                    r2->hopCount = hopCount;
                    r2->flag = flag;
                    r2->nextHopAddr = nextHopAddr;
                    r2->state = state;
                    r2->reliability=reli;
                    r2->pDelay = pathDelay;
                    r2->path_Load = path_Load; 
                }
            }
            
        }

        if(dtype.compare("Critical")==0){
            double ms = pathDelay.dbl();
            //double oms = r3->pDelay.dbl();
            int newr = (0.8*ms)+(0.2*reli);   
            //int oldr = (0.8*oms)+(0.2*(r3->reliability));
            double oms1,oms2;
            int oldr1,oldr2;

            if(priority==1){

                Route* r1 = searchByDest(dstIP,dtype,1);
                oms1 = r1->pDelay.dbl();
                oldr1 = (0.8*oms1)+(0.2*(r1->reliability));

                Route* r2 = searchByDest(dstIP,dtype,2);
                oms2 = r2->pDelay.dbl();
                oldr2 = (0.8*oms2)+(0.2*(r2->reliability));

                if((r1->flag!=VALID || r1->dstSN < dstSN ) && (newr > oldr1)){

                    r2->dstSN = r1->dstSN;
                    r2->hopCount = r1->hopCount;
                    r2->flag = r1->flag;
                    r2->nextHopAddr = r1->nextHopAddr;
                    r2->state = r1->state;
                    r2->reliability=r1->reliability;
                    r2->pDelay = r1->pDelay;
                    r2->path_Load = r1->path_Load; 

                    r1->dstSN = dstSN;
                    r1->hopCount = hopCount;
                    r1->flag = flag;
                    r1->nextHopAddr = nextHopAddr;
                    r1->state = state;
                    r1->reliability=reli;
                    r1->pDelay = pathDelay;
                    r1->path_Load = path_Load; 

                }
                else if((r2->flag!=VALID || r2->dstSN < dstSN ) && (newr > oldr2)){
                    r2->dstSN = dstSN;
                    r2->hopCount = hopCount;
                    r2->flag = flag;
                    r2->nextHopAddr = nextHopAddr;
                    r2->state = state;
                    r2->reliability=reli;
                    r2->pDelay = pathDelay;
                    r2->path_Load = path_Load; 
                }

            }
            else if(priority==2){
                Route* r2 = searchByDest(dstIP,dtype,2);
                if((r2->flag!=VALID || r2->dstSN < dstSN ) && (newr > oldr2)){
                    r2->dstSN = dstSN;
                    r2->hopCount = hopCount;
                    r2->flag = flag;
                    r2->nextHopAddr = nextHopAddr;
                    r2->state = state;
                    r2->reliability=reli;
                    r2->pDelay = pathDelay;
                    r2->path_Load = path_Load; 
                }
            }

        }

        if(dtype.compare("Ordinary")==0){

            if (priority==1){
                Route* r1 = searchByDest(dstIP,dtype,1);
                Route* r2 = searchByDest(dstIP,dtype,2);
               // if(r1->flag!=VALID || r1->dstSN < dstSN || (r1->dstSN == dstSN && r1->hopCount > (hopCount + 1))){  added by raj
                if(r1->flag!=VALID || r1->dstSN < dstSN || (r1->dstSN == dstSN &&  r1->path_Load > path_Load )){    // added by diana on 8th June 2019
                    r2->dstSN = r1->dstSN;
                    r2->hopCount = r1->hopCount;
                    r2->flag = r1->flag;
                    r2->nextHopAddr = r1->nextHopAddr;
                    r2->state = r1->state;
                    r2->reliability=r1->reliability;
                    r2->pDelay = r1->pDelay;
                    r2->path_Load = r1->path_Load; 

                    r1->dstSN = dstSN;
                    r1->hopCount = hopCount;
                    r1->flag = flag;
                    r1->nextHopAddr = nextHopAddr;
                    r1->state = state;
                    r1->reliability=reli;
                    r1->pDelay = pathDelay;
                    r1->path_Load = path_Load; 

                }
                else if(r2->flag!=VALID || r2->dstSN < dstSN || (r2->dstSN == dstSN && r2->path_Load > path_Load )){
                    r2->dstSN = dstSN;
                    r2->hopCount = hopCount;
                    r2->flag = flag;
                    r2->nextHopAddr = nextHopAddr;
                    r2->state = state;
                    r2->reliability=reli;
                    r2->pDelay = pathDelay;
                    r2->path_Load = path_Load; 
                }
            }
            else if(priority==2){
                Route* r2 = searchByDest(dstIP,dtype,2);
                if(r2->flag!=VALID || r2->dstSN < dstSN || (r2->dstSN == dstSN && r2->path_Load > path_Load )){
                    r2->dstSN = dstSN;
                    r2->hopCount = hopCount;
                    r2->flag = flag;
                    r2->nextHopAddr = nextHopAddr;
                    r2->state = state;
                    r2->reliability=reli;
                    r2->pDelay = pathDelay;
                    r2->path_Load = path_Load; 
                }
            }
            // if(r1->flag!=VALID || r1->dstSN < dstSN || (r1->dstSN == dstSN && r1->hopCount > (hopCount + 1))){
            //         r4->dstSN = dstSN;
            //         r4->hopCount = hopCount;
            //         r4->flag = flag;
            //         r4->nextHopAddr = nextHopAddr;
            //         if(r->precursor==NULL)
            //             r->precursor=new list<string>();
            //         if(precursor!=NULL)
            //             r->precursor->merge(*precursor);
            //         r4->state = state;
            //         r4->reliability=reli;//added by raj on 23/2/19
            //         r4->pDelay = pathDelay;//added by raj on 23/2/19
            // }
        }
    }


    if(!r) //no route for that dst exists already
    {
        Route nr;//added by raj on 23/2/19
        nr.dstSN = dstSN;
        nr.hopCount = hopCount;
        nr.flag = flag;
        nr.nextHopAddr = nextHopAddr;
        nr.precursor = new list<string>();
        /*if(precursor!=NULL)
            nr.precursor->merge(*precursor);*/
        nr.state = state;
        nr.dstIP = dstIP;
        nr.dtype = "Ordinary";
        nr.priority = priority;
        nr.pDelay = pathDelay;
        nr.reliability = reli;
        nr.path_Load = path_Load; 
        //route.lifetime = active_route_timeout
        table->push_back(nr);

        nr.dstSN = dstSN;
        nr.hopCount = hopCount;
        nr.flag = flag;
        nr.nextHopAddr = nextHopAddr;
        nr.precursor = new list<string>();
        /*if(precursor!=NULL)
            nr.precursor->merge(*precursor);*/
        nr.state = state;
        nr.dstIP = dstIP;
        nr.dtype = "Delay";
        nr.priority = priority;
        nr.pDelay = pathDelay;
        nr.reliability = reli;
        nr.path_Load = path_Load; 
        //route.lifetime = active_route_timeout
        table->push_back(nr);

        nr.dstSN = dstSN;
        nr.hopCount = hopCount;
        nr.flag = flag;
        nr.nextHopAddr = nextHopAddr;
        nr.precursor = new list<string>();
        /*if(precursor!=NULL)
            nr.precursor->merge(*precursor);*/
        nr.state = state;
        nr.dstIP = dstIP;
        nr.dtype = "Reliable";
        nr.priority = priority;
        nr.pDelay = pathDelay;
        nr.reliability = reli;
        nr.path_Load = path_Load; 
        //route.lifetime = active_route_timeout
        table->push_back(nr);

        nr.dstSN = dstSN;
        nr.hopCount = hopCount;
        nr.flag = flag;
        nr.nextHopAddr = nextHopAddr;
        nr.precursor = new list<string>();
        /*if(precursor!=NULL)
            nr.precursor->merge(*precursor);*/
        nr.state = state;
        nr.dstIP = dstIP;
        nr.dtype = "Critical";
        nr.priority = priority;
        nr.pDelay = pathDelay;
        nr.reliability = reli;
        nr.path_Load = path_Load; 
        //route.lifetime = active_route_timeout
        table->push_back(nr);
    }
}

void AodvRoutingTable::removeRoute(string destination, string dtype, int priority)//added by raj on 23/2/19
{
    for(list<Route>::iterator i=table->begin();i!=table->end();)
    {
        Route &r = *i;
        if((r.dstIP.compare(destination)==0)&&(r.dtype.compare(dtype)==0)&&(r.priority == priority))
        {
            //delete &r;
            i=table->erase(i);
        }
        else
            i++;
    }
}

string AodvRoutingTable::getNextHop(string destination, string dtype, int priority)//added by raj on 23/2/19
{
    Route* r = searchByDest(destination,dtype,priority);
    if(r)
    {
        return r->nextHopAddr;
    }
    else
        return "";
}

void AodvRoutingTable::setNextHop(string destination, string newNextHop, string dtype, int priority)//added by raj on 23/2/19
{
    Route *r = searchByDest(destination,dtype,priority);
    if(r)
    {
        r->nextHopAddr = newNextHop;
    }
}

unsigned long AodvRoutingTable::getDstSN(string destination, string dtype, int priority)//added by raj on 23/2/19
{
    Route* r = searchByDest(destination, dtype, priority);

    if(r)
    {
        return r->dstSN;
    }
    else
        return 0;
}

void AodvRoutingTable::setDstSN(string destination, unsigned long newSN)//added by raj on 23/2/19
{

    Route *r1 = searchByDest(destination,"Delay",1);
    if(r1)
    {
        if(r1->dstSN < newSN)
            r1->dstSN = newSN;
    }

    r1 = searchByDest(destination,"Reliable",1);
    if(r1)
    {
        if(r1->dstSN < newSN)
            r1->dstSN = newSN;
    }

    r1 = searchByDest(destination,"Critical",1);
    if(r1)
    {
        if(r1->dstSN < newSN)
            r1->dstSN = newSN;
    }

    r1 = searchByDest(destination,"Ordinary",1);
    if(r1)
    {
        if(r1->dstSN < newSN)
            r1->dstSN = newSN;
    }
}

double AodvRoutingTable::getLifetime(string destination,string detype, int prior)//changed on 15/3/19 raj
{
    RouteTimer* timer;
    double x=0;
    if(!timers.empty())
    {
        timer = (RouteTimer*)&(timers.top());
        for(unsigned int i = 0; i < timers.size(); i++)
        {
				if(!timer[i].canceled && timer[i].destination.compare(destination)==0 && timer[i].lifetime>x && timer[i].dtype.compare(detype)==0 && timer[i].priority == prior)//changed 15/3/19 raj
				{
					x = timer[i].lifetime;
				}
        }
    }
    return x;
}

void AodvRoutingTable::setLifetime(RouteTimer* timer, string dtype, int priority)//added by raj on 23/2/19
{
    Route *r = searchByDest(timer->destination, dtype, priority);
    if(r)
    {
        timers.push(*timer);
    }
}

RoutingFlag AodvRoutingTable::getFlag(string destination, string dtype, int priority)//added by raj on 23/2/19
{
    Route* r = searchByDest(destination,dtype, priority);
    if(r)
    {
        return r->flag;
    }
    else
        return UNKNOWN;
}

void AodvRoutingTable::setFlag(string destination, RoutingFlag newFlag, string dtype, int priority)//added by raj on 23/2/19
{
    Route *r = searchByDest(destination,dtype, priority);
    if(r)
    {
        r->flag = newFlag;
    }
}

int AodvRoutingTable::getHopCount(string destination, string dtype, int priority)//added by raj on 23/2/19
{
    Route *r = searchByDest(destination, dtype, priority);
    if(r)
    {
        return r->hopCount;
    }
    else
        return 0;
}

void AodvRoutingTable::setHopCount(string destination, int newCount, string dtype, int priority)//added by raj on 23/2/19
{
    Route *r = searchByDest(destination, dtype, priority);
    if(r)
    {
        r->hopCount = newCount;
    }
}

bool AodvRoutingTable::getState(string destination, string dtype, int priority)//added by raj on 23/2/19
{
    Route *r = searchByDest(destination, dtype, priority);
    if(r)
    {
        return r->state;
    }
    else
        return false;
}

void AodvRoutingTable::setState(string destination, bool valid, string dtype, int priority)//added by raj on 23/2/19
{
    Route *r = searchByDest(destination,dtype,priority);
    if(r)
    {
        r->state = valid;
    }
}

bool AodvRoutingTable::isRouteValid(string destination, string dtype, int priority)//added by raj on 23/2/19
{
    Route *r = searchByDest(destination,dtype,priority);
    if(r && r->flag==VALID)
            return true;
    else
        return false;
}

//check if the node is part of a valid route
bool AodvRoutingTable::isPartRouteValid()
{
    for(list<Route>::iterator i=table->begin();i!=table->end();++i)
    {
        Route &r = *i;
        if(isRouteValid(r.dstIP,r.dtype,r.priority) && r.precursor->size()!=0)
        {
                return true;
        }
    }
    return false;
}

void AodvRoutingTable::clearTimerExpired()
{
   timers.pop();
}
void AodvRoutingTable::resetTimer(string dest, string detype,int prior)
{
    RouteTimer* timer;
    if(!timers.empty())
    {
        timer = (RouteTimer*)&(timers.top());
        for(unsigned int i = 0; i < timers.size(); i++)
        {
            if(timer[i].destination.compare(dest)==0 && timer[i].dtype.compare(detype)==0 && timer[i].priority==0)
            {
                timer[i].canceled = true;
                return;
            }
        }
    }

}

int AodvRoutingTable::getTimersSize()
{
    return timers.size();
}

const RouteTimer* AodvRoutingTable::getNextExpiredRoute()
{
   return &(timers.top());
}

const std::list<string>& AodvRoutingTable::getPrecursors(string destination, string dtype, int priority)//added by raj on 23/2/19
{
    Route *r = searchByDest(destination,dtype, priority);
    if(r)
    {
        return *(r->precursor);
    }
    else
        return *(new list<string>());
}

void AodvRoutingTable::addPrecursor(string destination, string precursor, string dtype, int priority)//added by raj on 23/2/19
{
    Route *r = searchByDest(destination,dtype,priority);
    if(r)
    {
        if(r->precursor==NULL)
            r->precursor=new list<string>();

        for(list<string>::iterator i = r->precursor->begin();i!=r->precursor->end();++i)
        {
            string temp = *i;
            if(temp==precursor)
                    return;
        }
        r->precursor->push_back(precursor);
    }
}

void AodvRoutingTable::deletePrecursor(string destination, string precursor, string dtype, int priority)//added by raj on 23/2/19
{
    Route *r = searchByDest(destination,dtype,priority);
    if(r)
    {
        r->precursor->remove(precursor);
    }
}

void AodvRoutingTable::setLinkFailure(const char* node, list<string>* affectedDst, list<string>* affectedPre)
{
    //we look for all the routes which have node has next-hop
    for(list<Route>::iterator i=table->begin();i!=table->end();++i)
    {
        Route &r = *i;
        if(r.nextHopAddr.compare(string(node)) == 0 && r.flag==VALID)
        {
            r.flag=INVALID;
            r.dstSN++;
            affectedPre->insert(affectedPre->begin(),r.precursor->begin(),r.precursor->end());
            affectedDst->push_front(r.dstIP);
        }
    }
    affectedDst->unique();
    affectedPre->unique();
}

void AodvRoutingTable::forwardLinkFailure(const char* node, const list<string>* affectedDst, list<string>* affectedPre)//added by raj on 23/2/19
{
    //we look for all the routes which have node has next-hop
    for(list<string>::const_iterator i=affectedDst->begin();i!=affectedDst->end();++i)
    {
        Route *r = searchByDest(*i,"Delay",1);//for loop to be added
        if(r && (r->nextHopAddr.compare(string(node))) == 0 && r->flag==VALID)
        {
            r->flag=INVALID;
            affectedPre->insert(affectedPre->begin(),r->precursor->begin(),r->precursor->end());
        }

        r = searchByDest(*i,"Reliable",1);
        if(r && (r->nextHopAddr.compare(string(node))) == 0 && r->flag==VALID)
        {
            r->flag=INVALID;
            affectedPre->insert(affectedPre->begin(),r->precursor->begin(),r->precursor->end());
        }

        r = searchByDest(*i,"Critical",1);
        if(r && (r->nextHopAddr.compare(string(node))) == 0 && r->flag==VALID)
        {
            r->flag=INVALID;
            affectedPre->insert(affectedPre->begin(),r->precursor->begin(),r->precursor->end());
        }

        r = searchByDest(*i,"Ordinary",1);
        if(r && (r->nextHopAddr.compare(string(node))) == 0 && r->flag==VALID)
        {
            r->flag=INVALID;
            affectedPre->insert(affectedPre->begin(),r->precursor->begin(),r->precursor->end());
        }
    }
    affectedPre->unique();
}
