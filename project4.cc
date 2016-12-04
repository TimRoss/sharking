//
//  project4.cpp
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "project4.h"
int COUNT = 0;

// ****************************************************************************
// * pk_processor()
// *  Most of the work done by the program will be done here (or at least it
// *  it will originate here). The function will be called once for every 
// *  packet in the savefile.
// ****************************************************************************
void pk_processor(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
  COUNT++;
  resultsC* results = (resultsC*)user;
  results->incrementPacketCount();
  
  int len = 0;
  int tlen = 0;
  int ethernetHeaderLength = 0;
  int networkHeaderLength = 0;
  char etherType = 'o';
  int protocol = -1;
  int lenTypeSum; // length vs Type field sum

  // Data Link Layer
  lenTypeSum = int(packet[12]) * 256 + int(packet[13]);

  if(lenTypeSum <= 1500){ // 802.3
    //not really sure yet
  }
  else if(lenTypeSum >= 1536){
    ethernetHeaderLength = 14;
    if(int(packet[12]) == 8){
      if(int(packet[13]) == 0){ // IPv4
	etherType = '4';
      }
      else if(int(packet[13]) == 6){ // ARP
	etherType = 'a';
      }
    }
    else if(int(packet[12]) == 134){
      if(int(packet[13]) == 221){ //IPv6
	etherType = '6';
      }
    }
  }

  // Network Layer
  switch(etherType){
  case '4': //ipv4
    len = int(packet[ethernetHeaderLength + 2]) * 256 + int(packet[ethernetHeaderLength + 3]);
    protocol = int(packet[ethernetHeaderLength + 9]);
    networkHeaderLength = ethernetHeaderLength + (int(packet[ethernetHeaderLength]) % 16);
    break;
  case '6': //ipv6
    len = int(packet[ethernetHeaderLength + 4]) * 256 + int(packet[ethernetHeaderLength + 5]);
    protocol = int(packet[ethernetHeaderLength + 6]);
    networkHeaderLength = ethernetHeaderLength + 40;
    break;
  case 'a': //arp
    len = 60;
    protocol = 0;
    networkHeaderLength = ethernetHeaderLength + 28;
    break;
  }

  // Transport Layer

  switch(protocol){
  case 0: //ARP
    break;
  case 1: //ICMP
    tlen = len - 8;
    break;
  case 6: //TCP
    tlen = len - (int(packet[networkHeaderLength + 12]) - (int(packet[networkHeaderLength + 12]) % 16)) / 4;
    break;
  case 17: //UDP
    tlen = len - 8;
    break;
  case 58: //ipv6 ICMP
    tlen = len - 8;
    break;
  }


  //increment ethernetII vs 802.3
  if(lenTypeSum >= 1536){
    results->incrementEthernetIICount();
  }
  else if(lenTypeSum <= 1500){
    results->incrementEightO2Point3Count();
  }

  switch(etherType){
  case 'o':
    results->incrementOtherNetworkCount();
    break;
  case '4':    
    results->giveIPv4Length(len);
    break;
  case '6':
    results->giveIPv6Length(len);
    break;
  case 'a':
    results->giveARPLength(len);
    break;
  }

  switch(protocol){
  case 0:
    //ARP, does not get counted
    break;
  case 1:
    std::cout << COUNT << std::endl;
    results->giveICMPLength(tlen);
    break;
  case 6:
    results->giveTCPLength(tlen);
    break;
  case 17:
    results->giveUDPLength(tlen);
    break;
  case 58:
    results->incrementOtherTransportCount();
    break;
  }

  //Part Two

  results->insertDestinationMAC(int(packet[0]) * pow(256, 5) + int(packet[1]) * pow(256,4) + int(packet[2]) * pow(256, 3) +int(packet[3]) * pow(256, 2) + int(packet[4]) * pow(256,1) + int(packet[5]));
  results->insertSourceMAC(int(packet[6]) * pow(256, 5) + int(packet[7]) * pow(256,4) + int(packet[8]) * pow(256, 3) +int(packet[9]) * pow(256, 2) + int(packet[10]) * pow(256,1) + int(packet[11]));

  

  return;
}


// ****************************************************************************
// * main()
// *  You should not have to worry about anything if you don't want to. 
// *  My code will open the file, initalize the results container class,
// *  call pk_processor() once for each packet and the finally call
// *  the displayResutls() method.
// ****************************************************************************
int main (int argc, const char * argv[])
{

  
  // **********************************************************************
  // * The program is called with a single argument, the name of the
  // * pcap save file to read.
  // **********************************************************************
  if (argc != 2) {
     std::cerr << "useage: project4 <filename>" << std::endl;
     exit(EXIT_FAILURE);
  }


  // **********************************************************************
  // * Instantiate the results class.  
  // **********************************************************************
  resultsC* results = new resultsC();



  // **********************************************************************
  // * Attempt to open the file.
  // **********************************************************************
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *PT;

  bzero(errbuf,PCAP_ERRBUF_SIZE);
  if ((PT = pcap_open_offline(argv[1],errbuf)) == NULL ) {
    std::cerr << "Unable to open pcap file: " << argv[1] << "\n"
         << pcap_geterr(PT) << std::endl;
    exit(EXIT_FAILURE);
  }

  if (strlen(errbuf) > 0)
    std::cerr << "Warning: pcap_open_offiline: " << pcap_geterr(PT) << std::endl;



  // **********************************************************************
  // * The dispatcher will call the packet processor once for packet
  // * in the capture file.
  // **********************************************************************
  int pk_count;
  if ((pk_count = pcap_dispatch(PT, -1, pk_processor, (u_char *)results)) < 0) {
    std::cerr << "Error calling dispatcher: " << pcap_geterr(PT) << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "Dispatcher finished with " << pk_count << " packets left in the queue." << std::endl;


  // **********************************************************************
  // * File your report here.
  // **********************************************************************
  results->displayResults();
  exit(EXIT_SUCCESS);
}


