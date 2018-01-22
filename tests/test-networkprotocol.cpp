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

#include <Connection.hpp>
#include <SimpleRetryProtocol.hpp>

/** The port that all of the testing is performed on */
#define PORT 25565

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
         *
         * @param delay
         * The time in milliseconds that the response should be delayed by. By default there is no delay.
         */
        TestServer(boost::asio::io_service& io_service, int port, int num_recieves = 1, const std::chrono::milliseconds& delay = std::chrono::milliseconds(0)) :
                  _delay(delay), _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), port)), _num_recieves(num_recieves) {
        
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
                    
                    std::this_thread::sleep_for(_delay);
                    
                    // Write out the packet we just read, as this is an echo server
                    _socket.send_to(boost::asio::buffer(buffer, packet_size), _remote_endpoint);
                    
                    delete [] buffer;
                    
                    _num_recieves--;
                    if (_num_recieves)
                        listen();
                    
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
    
        /** The time that the return message should be delayed */
        const std::chrono::milliseconds& _delay;
    
        /** The UDP socket that is listened to */
        boost::asio::ip::udp::socket _socket;
    
        /** The endpoint of the server */
        boost::asio::ip::udp::endpoint _remote_endpoint;
    
        /** The number of times that the server should recieve */
        int _num_recieves;
    
};

boost::asio::ip::udp::socket createLocalSocket(boost::asio::io_service& service, int port) {
    
    // Resolve the hostname into an IP that boost can use
    boost::asio::ip::udp::resolver resolver(service);
    boost::asio::ip::udp::resolver::query query(boost::asio::ip::udp::v4(), "localhost", std::to_string(PORT));
    boost::asio::ip::udp::endpoint receiver_endpoint = *resolver.resolve(query);
    
    boost::asio::ip::udp::socket socket(service);
    socket.connect(receiver_endpoint);
    
    return socket;
    
}

BOOST_AUTO_TEST_CASE(testTestServer) {
 
    boost::asio::io_service io_service;
    TestServer server = TestServer(io_service, PORT);

    // Running the server is blocking so add it to a new thread
    std::thread thread([&io_service] { io_service.run(); });

    try {
        
        boost::asio::io_service io_service_client;
        boost::asio::ip::udp::socket socket = createLocalSocket(io_service_client, PORT);

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

BOOST_AUTO_TEST_CASE(testNRetry) {
    
    boost::asio::io_service io_service;
    TestServer server = TestServer(io_service, PORT, 2, std::chrono::milliseconds(TIMEOUT_MILLISECONDS + 1));
    
    // Running the server is blocking so add it to a new thread
    std::thread thread([&io_service] { io_service.run(); });
    
    boost::asio::io_service io_service_client;
    boost::asio::ip::udp::socket socket = createLocalSocket(io_service_client, PORT);
    
    NRetryProtocol protocol(2);
    
    protocol.write(socket, "TEST");
    BOOST_CHECK_EQUAL(strcmp("TEST", protocol.read(socket).c_str()), 0);
    
    protocol.write(socket, "TEST");
    BOOST_CHECK_EQUAL(strcmp("TEST", protocol.read(socket).c_str()), 0);
    
    // Stop the service so the thread can be deallocated
    thread.join();
    
    // Since the TestServer only listens for 1 message, reading should fail
    std::cout << "Expecting network failure...";
    BOOST_CHECK_EQUAL(protocol.read(socket).length(), 0);
    
}

BOOST_AUTO_TEST_CASE(testSimpleRetry) {
    
    boost::asio::io_service io_service;
    TestServer server = TestServer(io_service, PORT, 2);
    
    // Running the server is blocking so add it to a new thread
    std::thread thread([&io_service] { io_service.run(); });
    
    boost::asio::io_service io_service_client;
    boost::asio::ip::udp::socket socket = createLocalSocket(io_service_client, PORT);
    
    SimpleRetryProtocol protocol;
    
    protocol.write(socket, "TEST");
    BOOST_CHECK_EQUAL(strcmp("TEST", protocol.read(socket).c_str()), 0);
    
    protocol.write(socket, "TEST");
    BOOST_CHECK_EQUAL(strcmp("TEST", protocol.read(socket).c_str()), 0);
    
    // Stop the service so the thread can be deallocated
    thread.join();
    
    // Since the TestServer only listens for 1 message, reading should fail
    std::cout << "Expecting network failure...";
    BOOST_CHECK_EQUAL(protocol.read(socket).length(), 0);
    
}

BOOST_AUTO_TEST_CASE(testConnection) {
    
    boost::asio::io_service io_service;
    TestServer server = TestServer(io_service, PORT, 2);
    
    // Running the server is blocking so add it to a new thread
    std::thread thread([&io_service] { io_service.run(); });
    
    std::shared_ptr<RetryProtocol> retry_protocol = std::shared_ptr<RetryProtocol>(new SimpleRetryProtocol);
    Connection connection("localhost", PORT, retry_protocol, "test_connection");
    
    connection.write("TEST");
    BOOST_CHECK_EQUAL(strcmp("TEST", connection.read().c_str()), 0);
    
    connection.write("TEST");
    BOOST_CHECK_EQUAL(strcmp("TEST", connection.read().c_str()), 0);
    
    // Stop the service so the thread can be deallocated
    thread.join();
    
    // Since the TestServer only listens for 1 message, reading should fail
    std::cout << "Expecting network failure...";
    BOOST_CHECK_EQUAL(connection.read().length(), 0);
    
}

