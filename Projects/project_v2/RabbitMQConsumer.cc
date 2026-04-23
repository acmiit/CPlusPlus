#include "RabbitMQConsumer.h"
#include <iostream>
#include <cstring>

RabbitMQConsumer::RabbitMQConsumer(const std::string& host, int port,
                                   const std::string& username, const std::string& password,
                                   const std::string& queue, const std::string& exchange, const std::string& routing_key)
    : _host(host), _port(port), _username(username), _password(password),
      _queue(queue), _exchange(exchange), _routing_key(routing_key),
      _channel(0), _connected(false), _running(false) {
    _conn = amqp_new_connection();
}

RabbitMQConsumer::~RabbitMQConsumer() {
    stop();
    if (_connected) {
        amqp_channel_close(_conn, _channel, AMQP_REPLY_SUCCESS);
        amqp_connection_close(_conn, AMQP_REPLY_SUCCESS);
    }
    amqp_destroy_connection(_conn);
}

bool RabbitMQConsumer::connect() {
    amqp_socket_t *socket = amqp_tcp_socket_new(_conn);
    if (!socket) {
        std::cerr << "Failed to create TCP socket" << std::endl;
        return false;
    }

    if (amqp_socket_open(socket, _host.c_str(), _port) != AMQP_STATUS_OK) {
        std::cerr << "Failed to open TCP socket" << std::endl;
        return false;
    }

    amqp_rpc_reply_t login_result = amqp_login(_conn, "/", 0, AMQP_DEFAULT_FRAME_SIZE, 0,
                    AMQP_SASL_METHOD_PLAIN, _username.c_str(), _password.c_str());
    if (login_result.reply_type != AMQP_RESPONSE_NORMAL) {
        std::cerr << "Login failed" << std::endl;
        return false;
    }

    _channel = 1;
    amqp_channel_open(_conn, _channel);

    amqp_exchange_declare(_conn, _channel,
                          amqp_cstring_bytes(_exchange.c_str()),
                          amqp_cstring_bytes("direct"),
                          false, true, false, false,
                          amqp_empty_table);

    amqp_queue_declare(_conn, _channel,
                       amqp_cstring_bytes(_queue.c_str()),
                       false, true, false, false,
                       amqp_empty_table);

    amqp_queue_bind(_conn, _channel,
                    amqp_cstring_bytes(_queue.c_str()),
                    amqp_cstring_bytes(_exchange.c_str()),
                    amqp_cstring_bytes(_routing_key.c_str()),
                    amqp_empty_table);

    amqp_basic_qos(_conn, _channel, 0, 1, false);

    _connected = true;
    return true;
}

void RabbitMQConsumer::consume(MessageCallback callback) {
    if (!_connected) {
        if (!connect()) {
            return;
        }
    }

    _running = true;
    amqp_basic_consume(_conn, _channel,
                       amqp_cstring_bytes(_queue.c_str()),
                       amqp_empty_bytes, false, false, false,
                       amqp_empty_table);

    std::cout << "Waiting for messages on queue: " << _queue << std::endl;

    while (_running) {
        amqp_rpc_reply_t res;
        amqp_envelope_t envelope;
        amqp_maybe_release_buffers(_conn);

        struct timeval timeout = {1, 0};
        res = amqp_consume_message(_conn, &envelope, &timeout, 0);

        if (res.reply_type == AMQP_RESPONSE_NORMAL) {
            if (envelope.message.body.len > 0) {
                std::string message(reinterpret_cast<char*>(envelope.message.body.bytes),
                                   envelope.message.body.len);
                std::cout << "Received message: " << message << std::endl;

                try {
                    callback(message);
                } catch (const std::exception& e) {
                    std::cerr << "Callback error: " << e.what() << std::endl;
                }

                amqp_basic_ack(_conn, _channel, envelope.delivery_tag, false);
            }
            amqp_destroy_envelope(&envelope);
        } else if (res.reply_type == AMQP_RESPONSE_LIBRARY_EXCEPTION) {
            if (res.library_error == AMQP_STATUS_TIMEOUT) {
                continue;
            }
            std::cerr << "Library exception: " << res.library_error << std::endl;
            break;
        } else {
            std::cerr << "Unknown error" << std::endl;
            break;
        }
    }
}

void RabbitMQConsumer::stop() {
    _running = false;
}