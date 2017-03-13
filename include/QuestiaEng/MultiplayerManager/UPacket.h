#ifndef PACKET_H
#define PACKET_H

struct pkt
{
    //packet
    enum Header
    {
        //init client
        clientTcp = 1, clientUdpTest = 2, clientLogin = 3,
        //init server
        svrResp = 7,
        //in game entities
        other = 10, player = 11, playerContainer = 12, entity = 13, entityContainer = 14
    };
};

// used for udp packets
struct UPacket
{
public:
    UPacket() = default;
    ~UPacket() = default;
};

#endif // PACKET_H
