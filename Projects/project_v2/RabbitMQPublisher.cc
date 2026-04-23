#include "RabbitMQPublisher.h"
#include <iostream>

RabbitMQPublisher::RabbitMQPublisher(const std::string& host, int port,
                                     const std::string& username, const std::string& password,
                                     const std::string& exchange, const std::string& routing_key)
    : _host(host), _port(port), _username(username), _password(password),
      _exchange(exchange), _routing_key(routing_key), _channel(0), _connected(false) {
    _conn = amqp_new_connection();
}

RabbitMQPublisher::~RabbitMQPublisher() {
    if (_connected) {
        amqp_channel_close(_conn, _channel, AMQP_REPLY_SUCCESS);
        amqp_connection_close(_conn, AMQP_REPLY_SUCCESS);
    }
    amqp_destroy_connection(_conn);
}

bool RabbitMQPublisher::connect() {
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

    _connected = true;
    return true;
}

bool RabbitMQPublisher::publish(const std::string& message) {
    if (!_connected) {
        if (!connect()) {
            return false;
        }
    }

    amqp_basic_properties_t props;
    props._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
    props.content_type = amqp_cstring_bytes("application/json");
    props.delivery_mode = 2;

    int ret = amqp_basic_publish(_conn, _channel,
                                  amqp_cstring_bytes(_exchange.c_str()),
                                  amqp_cstring_bytes(_routing_key.c_str()),
                                  false, false, &props,
                                  amqp_cstring_bytes(message.c_str()));

    if (ret != AMQP_STATUS_OK) {
        std::cerr << "Publish failed: " << ret << std::endl;
        _connected = false;
        return false;
    }
    return true;
}