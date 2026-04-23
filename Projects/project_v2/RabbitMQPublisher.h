#ifndef __WD_RABBITMQ_PUBLISHER_HPP__
#define __WD_RABBITMQ_PUBLISHER_HPP__

#include <string>
#include <memory>
#include <amqp.h>
#include <amqp_tcp_socket.h>

class RabbitMQPublisher {
public:
    RabbitMQPublisher(const std::string& host, int port,
                      const std::string& username, const std::string& password,
                      const std::string& exchange, const std::string& routing_key);
    ~RabbitMQPublisher();

    bool connect();
    bool publish(const std::string& message);

private:
    std::string _host;
    int _port;
    std::string _username;
    std::string _password;
    std::string _exchange;
    std::string _routing_key;

    amqp_connection_state_t _conn;
    amqp_channel_t _channel;
    bool _connected;
};

#endif