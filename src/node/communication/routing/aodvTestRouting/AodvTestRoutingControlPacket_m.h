//
// Generated file, do not edit! Created by nedtool 4.6 from src/node/communication/routing/aodvTestRouting/AodvTestRoutingControlPacket.msg.
//

#ifndef _AODVTESTROUTINGCONTROLPACKET_M_H_
#define _AODVTESTROUTINGCONTROLPACKET_M_H_

#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0406
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



// cplusplus {{
#include "RoutingPacket_m.h"
// }}


const SimTime string2simTime(const char* x);//added by raj
const char * simTime2string(SimTime t);//added by raj
/**
 * Class generated from <tt>src/node/communication/routing/aodvTestRouting/AodvTestRoutingControlPacket.msg:30</tt> by nedtool.
 * <pre>
 * packet PacketRREQ extends RoutingPacket
 * {
 *     bool flagJ;
 *     bool flagR;
 *     bool flagG;
 *     bool flagD;
 *     bool flagU;
 *     int hopCount;
 *     int rreqID;
 *     string dstIP;
 *     unsigned long dstSN;
 *     string srcIP;
 *     unsigned long srcSN;
 *     double lifetime;
 * }
 * </pre>
 */
class PacketRREQ : public ::RoutingPacket
{
  protected:
    bool flagJ_var;
    bool flagR_var;
    bool flagG_var;
    bool flagD_var;
    bool flagU_var;
    int hopCount_var;
    int rreqID_var;
    opp_string dstIP_var;
    unsigned long dstSN_var;
    opp_string srcIP_var;
    unsigned long srcSN_var;
    double lifetime_var;
    SimTime propDelay;//added a new parameter by Raj 19/10/18

  private:
    void copy(const PacketRREQ& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const PacketRREQ&);

  public:
    PacketRREQ(const char *name=NULL, int kind=0);
    PacketRREQ(const PacketRREQ& other);
    virtual ~PacketRREQ();
    PacketRREQ& operator=(const PacketRREQ& other);
    virtual PacketRREQ *dup() const {return new PacketRREQ(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual bool getFlagJ() const;
    virtual void setFlagJ(bool flagJ);
    virtual bool getFlagR() const;
    virtual void setFlagR(bool flagR);
    virtual bool getFlagG() const;
    virtual void setFlagG(bool flagG);
    virtual bool getFlagD() const;
    virtual void setFlagD(bool flagD);
    virtual bool getFlagU() const;
    virtual void setFlagU(bool flagU);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual int getRreqID() const;
    virtual void setRreqID(int rreqID);
    virtual const char * getDstIP() const;
    virtual void setDstIP(const char * dstIP);
    virtual unsigned long getDstSN() const;
    virtual void setDstSN(unsigned long dstSN);
    virtual const char * getSrcIP() const;
    virtual void setSrcIP(const char * srcIP);
    virtual unsigned long getSrcSN() const;
    virtual void setSrcSN(unsigned long srcSN);
    virtual double getLifetime() const;
    virtual void setLifetime(double lifetime);
    virtual SimTime getpropDelay() const;//added by Raj 19/10/18
    virtual void setpropDelay(SimTime x);// added by Raj 19/10/18
};

inline void doPacking(cCommBuffer *b, PacketRREQ& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, PacketRREQ& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>src/node/communication/routing/aodvTestRouting/AodvTestRoutingControlPacket.msg:46</tt> by nedtool.
 * <pre>
 * packet PacketRREP extends RoutingPacket
 * {
 *     bool flagR;
 *     bool flagA;
 *     int prefixSz;
 *     int hopCount;
 *     string dstIP;
 *     unsigned long dstSN;
 *     string originIP;
 *     double lifetime;
 * 
 *     int rreqID;
 * }
 * </pre>
 */
class PacketRREP : public ::RoutingPacket
{
  protected:
    bool flagR_var;
    bool flagA_var;
    int prefixSz_var;
    int hopCount_var;
    opp_string dstIP_var;
    unsigned long dstSN_var;
    opp_string originIP_var;
    double lifetime_var;
    int rreqID_var;

  private:
    void copy(const PacketRREP& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const PacketRREP&);

  public:
    PacketRREP(const char *name=NULL, int kind=0);
    PacketRREP(const PacketRREP& other);
    virtual ~PacketRREP();
    PacketRREP& operator=(const PacketRREP& other);
    virtual PacketRREP *dup() const {return new PacketRREP(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual bool getFlagR() const;
    virtual void setFlagR(bool flagR);
    virtual bool getFlagA() const;
    virtual void setFlagA(bool flagA);
    virtual int getPrefixSz() const;
    virtual void setPrefixSz(int prefixSz);
    virtual int getHopCount() const;
    virtual void setHopCount(int hopCount);
    virtual const char * getDstIP() const;
    virtual void setDstIP(const char * dstIP);
    virtual unsigned long getDstSN() const;
    virtual void setDstSN(unsigned long dstSN);
    virtual const char * getOriginIP() const;
    virtual void setOriginIP(const char * originIP);
    virtual double getLifetime() const;
    virtual void setLifetime(double lifetime);
    virtual int getRreqID() const;
    virtual void setRreqID(int rreqID);
};

inline void doPacking(cCommBuffer *b, PacketRREP& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, PacketRREP& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>src/node/communication/routing/aodvTestRouting/AodvTestRoutingControlPacket.msg:60</tt> by nedtool.
 * <pre>
 * packet PacketHELLO extends RoutingPacket
 * {
 *     double lifetime;
 * }
 * </pre>
 */
class PacketHELLO : public ::RoutingPacket
{
  protected:
    double lifetime_var;

  private:
    void copy(const PacketHELLO& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const PacketHELLO&);

  public:
    PacketHELLO(const char *name=NULL, int kind=0);
    PacketHELLO(const PacketHELLO& other);
    virtual ~PacketHELLO();
    PacketHELLO& operator=(const PacketHELLO& other);
    virtual PacketHELLO *dup() const {return new PacketHELLO(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual double getLifetime() const;
    virtual void setLifetime(double lifetime);
};

inline void doPacking(cCommBuffer *b, PacketHELLO& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, PacketHELLO& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>src/node/communication/routing/aodvTestRouting/AodvTestRoutingControlPacket.msg:65</tt> by nedtool.
 * <pre>
 * packet PacketRREPack extends RoutingPacket
 * {
 *     double lifetime;
 * }
 * </pre>
 */
class PacketRREPack : public ::RoutingPacket
{
  protected:
    double lifetime_var;

  private:
    void copy(const PacketRREPack& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const PacketRREPack&);

  public:
    PacketRREPack(const char *name=NULL, int kind=0);
    PacketRREPack(const PacketRREPack& other);
    virtual ~PacketRREPack();
    PacketRREPack& operator=(const PacketRREPack& other);
    virtual PacketRREPack *dup() const {return new PacketRREPack(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual double getLifetime() const;
    virtual void setLifetime(double lifetime);
};

inline void doPacking(cCommBuffer *b, PacketRREPack& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, PacketRREPack& obj) {obj.parsimUnpack(b);}

/**
 * Class generated from <tt>src/node/communication/routing/aodvTestRouting/AodvTestRoutingControlPacket.msg:70</tt> by nedtool.
 * <pre>
 * packet PacketRERR extends RoutingPacket
 * {
 *     bool flagN;
 *     int destCount;
 *     double lifetime;
 *     string unreachableDstIP[];
 *     unsigned long unreachableDstSN[];
 * }
 * </pre>
 */
class PacketRERR : public ::RoutingPacket
{
  protected:
    bool flagN_var;
    int destCount_var;
    double lifetime_var;
    opp_string *unreachableDstIP_var; // array ptr
    unsigned int unreachableDstIP_arraysize;
    unsigned long *unreachableDstSN_var; // array ptr
    unsigned int unreachableDstSN_arraysize;

  private:
    void copy(const PacketRERR& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const PacketRERR&);

  public:
    PacketRERR(const char *name=NULL, int kind=0);
    PacketRERR(const PacketRERR& other);
    virtual ~PacketRERR();
    PacketRERR& operator=(const PacketRERR& other);
    virtual PacketRERR *dup() const {return new PacketRERR(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual bool getFlagN() const;
    virtual void setFlagN(bool flagN);
    virtual int getDestCount() const;
    virtual void setDestCount(int destCount);
    virtual double getLifetime() const;
    virtual void setLifetime(double lifetime);
    virtual void setUnreachableDstIPArraySize(unsigned int size);
    virtual unsigned int getUnreachableDstIPArraySize() const;
    virtual const char * getUnreachableDstIP(unsigned int k) const;
    virtual void setUnreachableDstIP(unsigned int k, const char * unreachableDstIP);
    virtual void setUnreachableDstSNArraySize(unsigned int size);
    virtual unsigned int getUnreachableDstSNArraySize() const;
    virtual unsigned long getUnreachableDstSN(unsigned int k) const;
    virtual void setUnreachableDstSN(unsigned int k, unsigned long unreachableDstSN);
};

inline void doPacking(cCommBuffer *b, PacketRERR& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, PacketRERR& obj) {obj.parsimUnpack(b);}


#endif // ifndef _AODVTESTROUTINGCONTROLPACKET_M_H_

