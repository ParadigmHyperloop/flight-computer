//
//  test-command.cpp
//  networkprotocol
//
//  Created by Logan on 1/21/18.
//

#include <boost/test/unit_test.hpp>
#include <CommandServer.hpp>

/** The port that all of the testing is performed on */
#define PORT 25565

/** The number of milliseconds to sleep for after sending the command to the server to check if it worked */
#define CLIENT_SLEEP 15

bool command_called = false;

void command() { command_called = true; }

BOOST_AUTO_TEST_CASE(testTestCommandServer) {
    
    CommandServer server(PORT);
    std::shared_ptr<CommandTicket> ticket = server.addCommandConnection("TEST", &command);
    
    boost::asio::io_service io_service;
    
    // Resolve the hostname into an IP that boost can use
    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::tcp::v4(), "localhost", std::to_string(PORT));
    boost::asio::ip::tcp::endpoint receiver_endpoint = *resolver.resolve(query);
    
    boost::asio::ip::tcp::socket socket(io_service);
    socket.connect(receiver_endpoint);
    
    socket.send(boost::asio::buffer("TEST"));
    
    // Sleep for a little while so we give the server time to get the command
    std::this_thread::sleep_for(std::chrono::milliseconds(CLIENT_SLEEP));
    server.resolveCommands();
    BOOST_CHECK(command_called);
    
    // Test command removal when ticket is deallocated
    command_called = false;
    ticket.reset();
    
    socket.send(boost::asio::buffer("TEST"));
    
    // Sleep for a little while so we give the server time to get the command
    std::this_thread::sleep_for(std::chrono::milliseconds(CLIENT_SLEEP));
    server.resolveCommands();
    BOOST_CHECK(!command_called);
    
}
