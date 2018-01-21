//
//  RetryProtocol.hpp
//  networkprotocol
//
//  Created by Logan on 1/20/18.
//

#ifndef RetryProtocol_hpp
#define RetryProtocol_hpp

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <iostream>
#include <memory>

/** The timeout in milliseconds for raw read and write operations */
#define TIMEOUT_MILLISECONDS 5

/** The abstract base class for all retry protocols. Subclasses of this class are responsible for handling UDP writes and reads */
class RetryProtocol {
    
    public:
    
        /**
         * Writes a message to a socket. This method uses the specific RetryProtocol subclass' behavior.
         *
         * @param socket
         * The socket that the message should be written to.
         *
         * @param
         * message
         * The message that should be written to the socket.
         */
        virtual void write(boost::asio::ip::udp::socket& socket, const std::string& message) const = 0;
    
        /**
         * Reads a message from a socket. This method uses the specific RetryProtocol subclass' behavior.
         *
         * @return
         * The message that was read from the socket.
         */
        virtual std::string read(boost::asio::ip::udp::socket& socket) const = 0;
    
    protected:
    
        /**
         * Performs a write on a socket. This does not need to be implemented by subclasses, as it should be used to perform a single write.
         *
         * @param socket
         * The socket that the message should be written to.
         *
         * @param
         * message
         * The message that should be written to the socket.
         *
         * @param success
         * A boolean to be set based on whether or not this succeeds or not.
         */
        void rawWrite(boost::asio::ip::udp::socket& socket, const std::string& message, bool& success) const;
    
        /*
         * Performs a read on a socket. This does not need to be implemented by subclasses, as it should be used to perform a single read.
         *
         * @param socket
         * The socket that the message should be written to.
         *
         * @param success
         * A boolean to be set based on whether or not this succeeds or not.
         *
         * @return
         * The message that was read from the socket.
         */
        std::string rawRead(boost::asio::ip::udp::socket& socket, bool& success) const;
    
        /**
         * Signals that there was either a read or write failure. This is NOT called if rawRead or rawWrite failed, but subclasses should call this
         * as they deem necessary.
         */
        void signalFailure() const;
    
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** A simple retry protocol. If a read or write fails, an error will be signaled immediately. */
class SimpleRetryProtocol : public RetryProtocol {
    
public:
    
    /**
     * Writes a message to a socket. If there is an error, failure is signaled.
     *
     * @param socket
     * The socket that the message should be written to.
     *
     * @param
     * message
     * The message that should be written to the socket.
     */
    virtual void write(boost::asio::ip::udp::socket& socket, const std::string& message) const;
    
    /**
     * Reads a message from a socket.  If there is an error, failure is signaled.
     *
     * @return
     * The message that was read from the socket.
     */
    virtual std::string read(boost::asio::ip::udp::socket& socket) const;
    
};

#endif /* RetryProtocol_hpp */
