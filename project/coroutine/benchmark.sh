#!/bin/bash

# 清理函数
cleanup() {
    pkill -9 -f "epoll_server|libevent" 2>/dev/null
    sleep 1
}

# 测试函数
run_test() {
    local name=$1
    local port=$2
    local cmd=$3

    echo ""
    echo "=========================================="
    echo "Testing: $name (port $port)"
    echo "=========================================="

    # 启动服务器
    eval "$cmd &"
    SERVER_PID=$!
    sleep 1

    # 检查服务器是否运行
    if ! ss -tlnp 2>/dev/null | grep -q ":$port "; then
        echo "Server failed to start!"
        kill $SERVER_PID 2>/dev/null
        return 1
    fi

    echo "Server started with PID: $SERVER_PID"

    # 运行ab测试
    ab -n 1000 -c 10 http://127.0.0.1:$port/ 2>&1 | tee /tmp/result_${port}.txt

    # 关闭服务器
    kill $SERVER_PID 2>/dev/null
    sleep 1
}

# 清理
cleanup

echo "=========================================="
echo "     Coroutine Library Benchmark Test"
echo "=========================================="
echo ""

# 1. 测试原生 epoll
run_test "Native Epoll" 8888 \
    "/home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/epoll/epoll_server"

cleanup

# 2. 测试 6hook 协程库
run_test "Coroutine (6hook)" 8080 \
    "cd /home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/6hook && ./main"

cleanup

# 3. 测试 libevent
run_test "Libevent" 8889 \
    "/home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/libevent/libevent_server_8889"

cleanup

echo ""
echo "=========================================="
echo "All tests completed!"
echo "=========================================="