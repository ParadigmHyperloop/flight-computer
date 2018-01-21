//
//  NRetryProtocol.hpp
//  networkprotocol
//
//  Created by Logan on 1/21/18.
//

#ifndef NRetryProtocol_hpp
#define NRetryProtocol_hpp

#include "RetryProtocol.hpp"

/** A retry protocol that will retry operations n times. If a read or write fails, an error will only be signaled after n retries. */
class NRetryProtocol : public RetryProtocol {
    
    public:
    
        /**
         * Creates a new protocol that will retry reading and writing num_retries number of times before signaling an error
         *
         * @param num_retries
         * The number of times to try read and write operations before signaling an error. This value should be nonzero.
         */
        NRetryProtocol(int num_retries);
    
        /**
         * Writes a message to a socket. If there is a failure, it will be retied n times until signaling a failure.
         *
         * @param socket
         * The socket that the message should be written to.
         *
         * @param message
         * The message that should be written to the socket.
         *
         * @param caller_name
         * The name of the object that is calling this method. By default this is "unnamed_instigator"
         */
        virtual void write(boost::asio::ip::udp::socket& socket, const std::string& message, const std::string& caller_name = "unnamed_instigator") const;
    
        /**
         * Reads a message from a socket. If there is a failure, it will be retied n times until signaling a failure.
         *
         * @param caller_name
         * The name of the object that is calling this method. By default this is "unnamed_instigator"
         *
         * @return
         * The message that was read from the socket.
         */
        virtual std::string read(boost::asio::ip::udp::socket& socket, const std::string& caller_name = "unnamed_instigator") const;
    
    private:
    
        /** The number of times to try read and write operations before signaling an error */
        int _num_retries;
    
};

#endif /* NRetryProtocol_hpp */
