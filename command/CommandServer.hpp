//
//  CommandServer.hpp
//  networkprotocol
//
//  Created by Logan on 1/21/18.
//

#ifndef CommandServer_hpp
#define CommandServer_hpp

#include <boost/asio.hpp>
#include <boost/lockfree/queue.hpp>
#include <boost/signals2.hpp>
#include <iostream>
#include <thread>
#include <vector>

class CommandConnection;
class CommandTicket;

/** The TCP server that listens for commands. When a command is recieved, it is performed. */
class CommandServer {
    
    public:
    
        /**
         * Starts the TCP command server on the specified port.
         *
         * @param port
         * The port that the server should be started on.
         */
        CommandServer(int port);
    
        /** Stops the TCP server */
        ~CommandServer();
    
        /**
         * Registers a particular function to be called when the specified command is called.
         *
         * @param command
         * The command that should call this function.
         *
         * @param function
         * The function to be called when the command is issued.
         *
         * @return
         * A ticket that when deallocated will automatically disconnect this command
         */
        std::shared_ptr<CommandTicket> addCommandConnection(std::string command, const boost::function<void()>& function);
    
        /** Runs all of the queued commands in _command_queue */
        void resolveCommands();
    
    private:
    
        /** Accepts a new incoming connection. */
        void accept();
    
        /** A function that can be used to actually run the server. This is used as the starting point for the thread */
        void runServer();
    
        /**
         * Waits for a new message to be recieved and then handles it accordingly.
         *
         * @param conneciton
         * The conneciton to listen to for a new message.
         */
        void recieveMessage(std::shared_ptr<CommandConnection> connection);
    
        /**
         * Closes the specified connection.
         *
         * @param conneciton
         * The conneciton to close.
         */
        void closeConnection(std::shared_ptr<CommandConnection> connection);
    
        /** The connections to the command server */
        std::vector<std::shared_ptr<CommandConnection>> _connections;

        /** The service that manages the TCP server */
        boost::asio::io_service _io_service;

        /** The object responsible for accepting a connection to the command server */
        boost::asio::ip::tcp::acceptor _acceptor;

        /** The thread that runs the server so it is non-blocking */
        std::thread _thread;
    
        /** A map who's keys correspond to the hashed commands and the values correspond to the signals that should be used for those commands */
        std::map<size_t, boost::signals2::signal<void()>> _signals;
    
        /** The queue of commands that has been recieved from the server that are ready to be resolved on the main thread */
        boost::lockfree::queue<size_t> _command_queue;

};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** A TCP connection to the Commadn Server */
class CommandConnection {
    
    public:
    
        /**
         * Creates a new socket that has not yet been accepted to the TCP server.
         *
         * @param io_service
         * The io service that should control the clients.
         *
         **/
        CommandConnection(boost::asio::io_service& io_service);
    
        /**
         * Gets the socket of this connection.
         *
         * @return
         * The socket for this connection;
         */
        inline boost::asio::ip::tcp::socket& getSocket() { return _socket; }
    
    private:
    
        /** The socket of the TCP connection */
        boost::asio::ip::tcp::socket _socket;
    
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** A class that stores a registration of a command handler. When this is deallocated, the comamnd handler is unregistered */
class CommandTicket {
    
    public:
    
        /**
         * A default constructor so that this can be used as a member and not have to be explicitly initialized in an owner's constructor.
         * Until the other constructor is called, this object will do nothing.
         */
        CommandTicket();
    
        /**
         * Creates a new command ticket that points to a connection.
         *
         * @param connection
         * The connection to the signal in the command server
         */
        CommandTicket(boost::signals2::connection connection);
    
        /** If this Ticket has a connection, disconnects the connection */
        ~CommandTicket();
    
    private:
    
        /** A connection to the signal in the command server. This can be an empty connecition */
        boost::signals2::connection _connection;
    
};

#endif /* CommandServer_hpp */
