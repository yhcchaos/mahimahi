/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#ifndef DELAY_QUEUE_HH
#define DELAY_QUEUE_HH

#include <queue>
#include <cstdint>
#include <string>
//#include <fstream>
#include <timestamp.hh>
#include "file_descriptor.hh"

class DelayQueue
{
private:
    uint64_t delay_ms_;
    std::queue< std::pair<uint64_t, std::string> > packet_queue_;
    /* release timestamp, contents */
    //std::ofstream log_;
public:
    DelayQueue( const uint64_t & s_delay_ms ) : delay_ms_( s_delay_ms ), packet_queue_() {}//, log_() {
    //    log_.open("/home/yhchaos/mvfst-rl/delay-"+std::to_string(delay_ms_)+std::to_string(timestamp())+".log");
    //    log_ << "#initial timestamp: " << timestamp() << std::endl;
    //}

    void read_packet( const std::string & contents );

    void write_packets( FileDescriptor & fd );

    unsigned int wait_time( void ) const;

    bool pending_output( void ) const { return wait_time() <= 0; }

    static bool finished( void ) { return false; }
};

#endif /* DELAY_QUEUE_HH */
