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
  std::cout << "A total of " << totalPacketCount << " packets processed." << std::endl;
}
