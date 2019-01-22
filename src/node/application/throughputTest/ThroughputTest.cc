/****************************************************************************
 *  Copyright: National ICT Australia,  2007 - 2011                         *
 *  Developed at the ATP lab, Networked Systems research theme              *
 *  Author(s): Athanassios Boulis, Yuriy Tselishchev                        *
 *  This file is distributed under the terms in the attached LICENSE file.  *
 *  If you do not find this file, copies can be found by writing to:        *
 *                                                                          *
 *      NICTA, Locked Bag 9013, Alexandria, NSW 1435, Australia             *
 *      Attention:  License Inquiry.                                        *
 *                                                                          *
 ****************************************************************************/

#include "ThroughputTest.h"

Define_Module(ThroughputTest);

void ThroughputTest::startup()
{
	packet_rate = par("packet_rate");
	recipientAddress = par("nextRecipient").stringValue();	 	
	startupDelay = par("startupDelay");
	

	packet_spacing = packet_rate > 0 ? 1 / float (packet_rate) : -1;
	dataSN = 0;

	if (packet_spacing > 0 && recipientAddress.compare(SELF_NETWORK_ADDRESS) != 0)
	{	
		trace()<<"Starting application layer for every node except 0";//raj
		setTimer(SEND_PACKET, packet_spacing + startupDelay);
	}
	else
	{
		trace() << "Only for node 0, starting application layer.";
		sendCmessageSugar();//calling this fucntion to send the Sugar cMessage to the network layer by raj on 6/11/18.
	}

	declareOutput("Packets received per node");
}

void ThroughputTest::fromNetworkLayer(ApplicationPacket * rcvPacket,
		const char *source, double rssi, double lqi)
{
	int sequenceNumber = rcvPacket->getSequenceNumber();
	
	if (recipientAddress.compare(SELF_NETWORK_ADDRESS) == 0) {
		trace() << "Received packet #" << sequenceNumber << " from node " << source; 
		collectOutput("Packets received per node", atoi(source));
	// Packet has to be forwarded to the next hop recipient
	} else {
		ApplicationPacket* fwdPacket = rcvPacket->dup();
		trace()<<"please ignore....2"<<recipientAddress.c_str();//raj
		// Reset the size of the packet, otherwise the app overhead will keep adding on
		fwdPacket->setByteLength(0);
		toNetworkLayer(fwdPacket, recipientAddress.c_str());
	}
}

void ThroughputTest::timerFiredCallback(int index)
{
	switch (index) {
		case SEND_PACKET:{
			trace() << "Sending packet #" << dataSN;
			toNetworkLayer(createGenericDataPacket(0, dataSN), par("nextRecipient"));
			dataSN++;
			setTimer(SEND_PACKET, packet_spacing);
			break;
		}
	}
}

// This method processes a received carrier sense interupt. Used only for demo purposes
// in some simulations. Feel free to comment out the trace command.
void ThroughputTest::handleRadioControlMessage(RadioControlMessage *radioMsg)
{
	switch (radioMsg->getRadioControlMessageKind()) {
		case CARRIER_SENSE_INTERRUPT:
			trace() << "CS Interrupt received! current RSSI value is: " << radioModule->readRSSI();
                        break;
	}
}

//adding the function void sendCmessageSugar() here which will send the Cmessage Sugar to the network layer to generate the packet sugar by raj on 6/11/18.
void ThroughputTest::sendCmessageSugar()
{
	cMessage * sugar = new cMessage("Sugar packet", SUGAR);
	toNetworkLayer(sugar);
}
