/* -*-mode:c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

#include <limits>

#include "delay_queue.hh"
#include "timestamp.hh"

using namespace std;

void DelayQueue::read_packet( const string & contents )
{
    //timestamp() returns ms, so ms->us
    //uint64_t  enqueue_time = timestamp() + delay_ms_ * 1000;
    //packet_queue_.emplace( enqueue_time, contents );
    //log_ << timestamp() << " + " << contents.size() << " out time: "  << std::to_string(enqueue_time) << std::endl;
    packet_queue_.emplace( timestamp() + delay_ms_ * 1000, contents );
}

void DelayQueue::write_packets( FileDescriptor & fd )
{
    while ( (!packet_queue_.empty())
            && (packet_queue_.front().first <= timestamp()) ) {
        fd.write( packet_queue_.front().second );
        //uint64_t  dequeue_time = timestamp();
        //log_ << dequeue_time << " - " << packet_queue_.front().second.size() << " out: "  << packet_queue_.front().first << " - " << dequeue_time -  packet_queue_.front().first << std::endl;
        packet_queue_.pop();
    }
}

unsigned int DelayQueue::wait_time( void ) const
{
    if ( packet_queue_.empty() ) {
        return numeric_limits<uint16_t>::max();
    }

    const auto now = timestamp();

    if ( packet_queue_.front().first <= now ) {
        return 0;
    } else {
        return packet_queue_.front().first - now;
    }
}
