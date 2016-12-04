//
//  resultsC.cc
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "project4.h"

// ***************************************************************************
// * resultsC::resultsC
// *  Constructor for the results container class.  
// ***************************************************************************
resultsC::resultsC() {
  totalPacketCount = 0;
  ethernetIICount = 0;
  eightO2Point3Count = 0;
  iPv4Count = 0;
  iPv6Count = 0;
  arpCount = 0;
  otherNetworkCount = 0;
  iPv4Sum = 0;
  iPv6Sum = 0;
  arpSum = 0;
  iPv4Min = 99999999;
  iPv6Min = 99999999;
  arpMin = 99999999;
  iPv4Max = 0;
  iPv6Max = 0;
  arpMax = 0;
  tcpCount = 0;
  udpCount = 0;
  icmpCount = 0;
  otherTransportCount = 0;
  tcpSum = 0;
  udpSum = 0;
  icmpSum = 0;
  tcpMin = 9999999;
  udpMin = 9999999;
  icmpMin = 9999999;
  tcpMax = 0;
  udpMax = 0;
  icmpMax = 0;
}

void resultsC::giveIPv4Length(int length) {
  if(length > iPv4Max){
    iPv4Max = length;
  }
  if(length < iPv4Min){
    iPv4Min = length;
  }
  iPv4Sum += length;
  iPv4Count++;
}

void resultsC::giveIPv6Length(int length) {
  if(length > iPv6Max){
    iPv6Max = length;
  }
  if(length < iPv6Min){
    iPv6Min = length;
  }
  iPv6Sum += length;
  iPv6Count++;
}

void resultsC::giveARPLength(int length) {
  if(length > arpMax){
    arpMax = length;
  }
  if(length < arpMin){
    arpMin = length;
  }
  arpSum += length;
  arpCount++;
}

void resultsC::giveUDPLength(int length) {
  if(length > udpMax){
    udpMax = length;
  }
  if(length < udpMin){
    udpMin = length;
  }
  udpSum += length;
  udpCount++;
}

void resultsC::giveICMPLength(int length) {
  if(length > icmpMax){
    icmpMax = length;
  }
  if(length < icmpMin){
    icmpMin = length;
  }
  icmpSum += length;
  icmpCount++;
}

void resultsC::giveTCPLength(int length) {
  if(length > tcpMax){
    tcpMax = length;
  }
  if(length < tcpMin){
    tcpMin = length;
  }
  tcpSum += length;
  tcpCount++;
}

// ***************************************************************************
// * displayResults:
// *  This method will be called once, after all the packets have been
// *  processed.  You should use this to print all the statistics you
// *  collected to stdout.
// ***************************************************************************
void resultsC::displayResults() {
  std::cout << "--------------- Data Link Layer ----------------" << std::endl;
  std::cout << "Ethernet II packets: " << ethernetIICount <<  std::endl;
  std::cout << "802.3 packets: " << eightO2Point3Count << std::endl;
  std::cout << std::endl;
  std::cout << "--------------- Network Layer -------------------" << std::endl;
  std::cout << "IPv4- Count: " << iPv4Count << "   Min: " << iPv4Min << "   Max: " << iPv4Max << "   Avg: " << (iPv4Count != 0 ? double(iPv4Sum) / double(iPv4Count) : 0) << std::endl;
  std::cout << "IPv6- Count: " << iPv6Count << "   Min: " << iPv6Min << "   Max: " << iPv6Max << "   Avg: " << (iPv6Count != 0 ? double(iPv6Sum) / double(iPv6Count) : 0) << std::endl;
  std::cout << "ARP- Count: " << arpCount << "   Min: " << arpMin << "   Max: " << arpMax << "   Avg: " << (arpCount != 0 ? double(arpSum) / double(arpCount) : 0) << std::endl;
  std::cout << "Number of other packets: " << otherNetworkCount << std::endl;
  std::cout << std::endl;
  std::cout << "--------------- Transport Layer -----------------" << std::endl;
  std::cout << "TCP- Count: " << tcpCount << "   Min: " << tcpMin << "   Max: " << tcpMax << "   Avg: " << (tcpCount != 0 ? double(tcpSum) / double(tcpCount) : 0) << std::endl;
  std::cout << "UDP- Count: " << udpCount << "   Min: " << udpMin << "   Max: " << udpMax << "   Avg: " << (udpCount != 0 ? double(udpSum) / double(udpCount) : 0) << std::endl;
  std::cout << "ICMP- Count: " << icmpCount << "   Min: " << icmpMin << "   Max: " << icmpMax << "   Avg: " << (icmpCount != 0 ? double(icmpSum) / double(icmpCount) : 0) << std::endl;
  std::cout << "Number of other transport packets: " << otherTransportCount << std::endl;
  std::cout << std::endl;
  std::cout << "A total of " << totalPacketCount << " packets processed." << std::endl;
}
