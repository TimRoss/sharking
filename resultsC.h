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

using namespace std;

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
   std::set<string> srcIP;
   std::set<string> dstIP;
   std::set<int> srcUDP;
   std::set<int> dstUDP;
   std::set<int> srcTCP;
   std::set<int> dstTCP;
   int syn;
   int fin;
   int frag;


  public:
   resultsC();
   void incrementPacketCount() { totalPacketCount++; };
   void insertSourceMAC(long double cheese) { mac.insert(cheese); };
   void insertSourceIP(string ip) {srcIP.insert(ip); };
   void insertDestinationIP(string ip) {dstIP.insert(ip); };
   void insertSourceUDPPort(int port) {srcUDP.insert(port);};
   void insertDestinationUDPPort(int port) {dstUDP.insert(port);};
   void insertSourceTCPPort(int port) {srcTCP.insert(port);};
   void insertDestinationTCPPort(int port) {dstTCP.insert(port);};
   void incrementSynCount() {syn++;};
   void incrementFinCount() {fin++;};
   void incrementFragCount() {frag++;};
   
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
