//
//  resultsC.h
//  Project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#ifndef resultsC_h
#define resultsC_h
#include <set>
#include <math.h>

class resultsC {
  protected:
   int totalPacketCount;

   //data link layer
   int ethernetIICount;
   int eightO2Point3Count;

   //network layer
   int iPv4Count;
   int iPv6Count;
   int arpCount;
   int otherNetworkCount;
   int iPv4Sum;
   int iPv6Sum;
   int arpSum;
   int iPv4Min;
   int iPv6Min;
   int arpMin;
   int iPv4Max;
   int iPv6Max;
   int arpMax;

   //transport layer
   int tcpCount;
   int udpCount;
   int icmpCount;
   int otherTransportCount;
   int tcpSum;
   int udpSum;
   int icmpSum;
   int tcpMax;
   int udpMax;
   int icmpMax;
   int tcpMin;
   int udpMin;
   int icmpMin;


   std::set<long double> mac; //source mac addresses
   std::set<long double> cheese; //destination mac addresses


  public:
   resultsC();
   void incrementPacketCount() { totalPacketCount++; };
   void insertSourceMAC(long cheese) { mac.insert(cheese); };
   int getSize() { return cheese.size(); };
   void insertDestinationMAC(long mac) { cheese.insert(mac); };

   //data link layer
   void incrementEthernetIICount() { ethernetIICount++; };
   void incrementEightO2Point3Count() { eightO2Point3Count++; };

   //network layer
   void incrementOtherNetworkCount() { otherNetworkCount++; };
   void giveIPv4Length(int length);
   void giveIPv6Length(int length);
   void giveARPLength(int length);

   //transport layer
   void incrementOtherTransportCount() { otherTransportCount++; };
   void giveTCPLength(int length);
   void giveUDPLength(int length);
   void giveICMPLength(int length);
   
   void displayResults();
};

#endif
