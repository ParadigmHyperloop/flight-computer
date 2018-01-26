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
#include <Error.hpp>
#include <iostream>
#include <memory>

/** The timeout in milliseconds for raw read and write operations */
#define TIMEOUT_MILLISECONDS 5

/** The abstract base class for all retry protocols. Subclasses of this class are responsible for handling UDP writes and reads */
class RetryProtocol {
    
    public:
    
        /**
         * Creates a new RetryProcol with an error handler that will be used if there is an error reading or writing
         * to the socket.
         *
         * @param error_handler
         * The error handler to be used in the event of an error
         */
        RetryProtocol(std::shared_ptr<ErrorHandler> error_handler);
    
        /**
         * Writes a message to a socket. This method uses the specific RetryProtocol subclass' behavior.
         *
         * @param socket
         * The socket that the message should be written to.
         *
         * @param message
         * The message that should be written to the socket.
         *
         * @param instigator
         * The instigator that is responsible if an error is raised
         */
        virtual void write(boost::asio::ip::udp::socket& socket, const std::string& message, const ErrorInstigator* instigator = nullptr) const = 0;
    
        /**
         * Reads a message from a socket. This method uses the specific RetryProtocol subclass' behavior.
         *
         * @param caller_name
         * The instigator that is responsible if an error is raised
         *
         * @return
         * The message that was read from the socket.
         */
        virtual std::string read(boost::asio::ip::udp::socket& socket, const ErrorInstigator* instigator = nullptr) const = 0;
    
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
         *
         * @param failure_message
         * A string describing what failed.
         *
         * @param caller_name
         * The instigator that is responsible for the error that is being signaled
         */
        void signalFailure(const std::string& failure_source, const ErrorInstigator* instigator) const;
    
    private:
    
        /** The handler that is used to signal an error if there is one */
        std::shared_ptr<ErrorHandler> _error_handler;
    
};

#endif /* RetryProtocol_hpp */
