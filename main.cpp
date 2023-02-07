#include <iostream>
#include <cstring>
#include <cstdlib>
#include <tins/tins.h>
#include <tins/dot11/dot11_data.h>

using namespace std;
using namespace Tins;
int packet_count = 0;

void usage() {
	printf("syntax: SignalStrength <interface> <mac> \n");
	printf("sample: SignalStrength mon0 00:11:22:33:44:55 \n");
}

bool signalStrength(const PDU &pdu, string mac) {
  packet_count++;
  const RadioTap &data = pdu.rfind_pdu<RadioTap>();
  int dbm_signal = data.dbm_signal();
  cout << "[" << packet_count <<"] Transmitter Mac Address:" << mac << "		Signal PWR: " << dbm_signal << endl;
  return true;
}

int main(int argc, char* argv[]) {

	if(argc != 3) {
		usage();
		return -1;
	}

	string interface = argv[1];
    string mac = argv[2];

	cout << "==========================================================================" << endl;
	cout << "[+] START" << endl;
	cout << "[+] Signal Strength of WiFi Checking" << endl;
	cout << "==========================================================================" << endl;
	
	SnifferConfiguration config;
    config.set_promisc_mode(true);
    
	char filter[100];
	sprintf(filter, "ether host %s", mac.c_str());
	config.set_filter(filter);
    Sniffer sniffer(interface, config);

	try {
		sniffer.sniff_loop(bind(signalStrength, placeholders::_1, mac));
	} catch (std::exception& e) {
		cerr << "[ERROR] Failed to start SignalStrength on interface " << interface << endl;
		return -1;
	}

    return 0;
}