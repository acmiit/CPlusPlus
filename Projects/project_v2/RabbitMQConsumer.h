#ifndef __WD_RABBITMQ_CONSUMER_HPP__
#define __WD_RABBITMQ_CONSUMER_HPP__

#include <string>
#include <memory>
#include <functional>
#include <amqp.h>
#include <amqp_tcp_socket.h>

using MessageCallback = std::function<void(const std::string& message)>;

class RabbitMQConsumer {
public:
    RabbitMQConsumer(const std::string& host, int port,
                     const std::string& username, const std::string& password,
                     const std::string& queue, const std::string& exchange, const std::string& routing_key);
    ~RabbitMQConsumer();

    bool connect();
    void consume(MessageCallback callback);
    void stop();

private:
    std::string _host;
    int _port;
    std::string _username;
    std::string _password;
    std::string _queue;
    std::string _exchange;
    std::string _routing_key;

    amqp_connection_state_t _conn;
    amqp_channel_t _channel;
    bool _connected;
    bool _running;
};

#endif