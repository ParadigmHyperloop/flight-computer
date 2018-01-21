//
//  test-networkprotocol.cpp
//  networkprotocol
//
//  Created by Logan on 1/20/18.
//

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <memory>
#include <thread>

#include <RetryProtocol.hpp>

/** A simple UDP server that will echo any message that it recieves */
class TestServer {
    
    public:
    
        /**
         * Starts a new UDP server on the specified port that will echo anything it recieves.
         *
         * @param io_service
         * The boost asio service that controls the server
         *
         * @param port
         * The port that the serve should start listening on
         */
        TestServer(boost::asio::io_service& io_service, int port) : _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)) {
        
             // At this point the server is started (explicitly initialized) so we need to listen for the message
            listen();
            
        }
    
    private:
    
        /** Starts listening for a message. When a message is recieved the handler is then called */
        void listen() {
            
            _socket.async_receive_from(boost::asio::null_buffers(), _remote_endpoint ,boost::bind(&TestServer::recieve, this,
                                                                                                  boost::asio::placeholders::error,
                                                                                                  boost::asio::placeholders::bytes_transferred));
            
        }
    
        /**
         * Called when the server recieves something from the socket. It will immediately send what it recieves back.
         *
         * @param error
         * The error code that was returned by boost
         *
         * @param size
         * The size in bytes of the recieved message
         */
        void recieve(const boost::system::error_code& error, std::size_t bytes) {
            
            if (!error || error == boost::asio::error::message_size) {
                
                // We did not use boost to read the buffer, so we manually read it
                size_t bytes_available = _socket.available();
                char* buffer = new char[bytes_available];
                
                boost::system::error_code read_error;
                size_t packet_size = _socket.receive_from(boost::asio::buffer(buffer, bytes_available), _remote_endpoint, 0, read_error);
                
                // Ensure that there was not an error actually reading
                if (!error) {
                    
                    std::cout << "TestServer got a message from the socket\n";
                    
                    // Write out the packet we just read, as this is an echo server
                    _socket.send_to(boost::asio::buffer(buffer, packet_size), _remote_endpoint);
                    
                    delete [] buffer;
                    
                } else {
                    
                    // There was an error reading from the socket so we throw an exception, ensuring to delete the buffer
                    delete [] buffer;
                    throw std::runtime_error("TestServer error reading from socket. Error:  " + error.message());
                
                }
                
                
                
            } else {
                
                // There was an error reading from the socket so we throw an exception
                throw std::runtime_error("TestServer error reading from socket. Error:  " + error.message());
                
            }
            
        }
    
        /** The UDP socket that is listened to */
        boost::asio::ip::udp::socket _socket;
    
        /** The endpoint of the server */
        boost::asio::ip::udp::endpoint _remote_endpoint;
    
};

BOOST_AUTO_TEST_CASE(testTestServer) {
 
    boost::asio::io_service io_service;
    TestServer server = TestServer(io_service, 25565);

    // Running the server is blocking so add it to a new thread
    std::thread thread([&io_service] { io_service.run(); });

    boost::asio::io_service io_service_client;

    // The server is running, conenct to it
    boost::asio::ip::udp::resolver resolver(io_service_client);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "localhost", "25565");
    boost::asio::ip::udp::endpoint receiver_endpoint = *resolver.resolve(query);

    boost::asio::ip::udp::socket socket(io_service);

    boost::system::error_code error;

    try {

        socket.connect(receiver_endpoint);

        // Send a test message
        socket.send(boost::asio::buffer("TEST"));

        // Create a fixed size buffer because we expect the response to be the same length as the string we sent
        std::shared_ptr<char> buffer = std::shared_ptr<char>(new char[5]);
        socket.receive(boost::asio::buffer(buffer.get(), 5));

        BOOST_CHECK_EQUAL(strcmp("TEST", buffer.get()), 0);

    } catch (std::exception& e) {

        std::cout << e.what() << std::endl;

        // Test something that will fail so we get pointed right to here, meaning there was an error with the test server
        BOOST_CHECK_EQUAL(0, 1);

        // The service needs to be force stopped so we can finish the program
        io_service.stop();

    }

    // Stop the service so the thread can be deallocated
    thread.join();
    
}

BOOST_AUTO_TEST_CASE(testSimpleRetry) {
    
    boost::asio::io_service io_service;
    TestServer server = TestServer(io_service, 25565);
    
    // Running the server is blocking so add it to a new thread
    std::thread thread([&io_service] { io_service.run(); });
    
    boost::asio::io_service io_service_client;
    
    // The server is running, conenct to it
    boost::asio::ip::udp::resolver resolver(io_service_client);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "localhost", "25565");
    boost::asio::ip::udp::endpoint receiver_endpoint = *resolver.resolve(query);
    
    boost::asio::ip::udp::socket socket(io_service);
    socket.connect(receiver_endpoint);
    
    SimpleRetryProtocol protocol;
    
    protocol.write(socket, "TEST");
    BOOST_CHECK_EQUAL(strcmp("TEST", protocol.read(socket).c_str()), 0);
    
    // Stop the service so the thread can be deallocated
    thread.join();
    
    // Since the TestServer only listens for 1 message, reading should fail
    std::cout << "Expecting network failure...";
    BOOST_CHECK_EQUAL(protocol.read(socket).length(), 0);
    
}
