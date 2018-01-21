//
//  Connection.hpp
//  networkprotocol
//
//  Created by Logan on 1/20/18.
//

#ifndef Connection_hpp
#define Connection_hpp

#include <time.h>

#include "RetryProtocol.hpp"

/** A class for managing a UDP connection to a particular hostname and port. */
class Connection {
    
    public:
    
        /**
         * Creates a new UDP connection to the specified hostname and port. Any reads and writes performed on this connection will be performed in the
         * fashion specified in retry_protocol.
         *
         * @param hostname
         * The hostname of the connection. For instance localhost or 198.168.242.123.
         *
         * @param port
         * The port of the connection.
         *
         * @param retry_protocol
         * The protocol that specifies how messages are written and read from the socket.
         *
         * @param connection_name
         * The name of this connection
         *
         */
        Connection(std::string hostname, int port, std::shared_ptr<RetryProtocol> retry_protocol, std::string connection_name);
    
        /**
         * Writes a message to this connection using the retry protocol.
         *
         * @param message
         * The message to write to the connection.
         *
         */
        void write(const std::string& message) const;
    
        /**
         * Reads a message from the connection using the retry protocol.
         *
         * @return
         * The message that was read from the connection.
         */
        std::string read() const;
    
    private:
    
        /** Connects to the current hostname */
        void connect();
    
        /** The hostname of the server that this connection represents */
        std::string _hostname;
    
        /** The port that this connection is on */
        int _port;
    
        /** The protocol that defines how messages are written and read from the UDP socket */
        std::shared_ptr<RetryProtocol> _retry_protocol;
    
        /** The name of this connection */
        std::string _connection_name;
    
        /** The service that manages the UDP socket */
        boost::asio::io_service _io_service;
    
        /** The UDP socket */
        std::unique_ptr<boost::asio::ip::udp::socket> _socket;
    
        /** The time that the connection was made */
        time_t _connection_time;
    
    
};

#endif /* Connection_hpp */
