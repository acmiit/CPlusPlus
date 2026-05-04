#!/bin/bash

cleanup() {
    pkill -9 -f "epoll_server|libevent|main" 2>/dev/null
    sleep 2
}

run_test() {
    local name=$1
    local port=$2
    local cmd=$3

    echo ""
    echo "=========================================="
    echo "Testing: $name (port $port)"
    echo "=========================================="

    eval "$cmd &"
    SERVER_PID=$!
    sleep 2

    if ! ss -tlnp 2>/dev/null | grep -q ":$port "; then
        echo "Server failed to start!"
        kill $SERVER_PID 2>/dev/null
        return 1
    fi

    echo "Server started with PID: $SERVER_PID"

    ab -n 1000000 -c 1000 http://127.0.0.1:$port/ 2>&1 | tee /tmp/result_1m_c1000_${port}.txt

    kill $SERVER_PID 2>/dev/null
    sleep 2
}

cleanup

echo "=========================================="
echo "  100万请求 1000并发 性能测试"
echo "=========================================="

echo ""
echo "正在测试原生 Epoll (端口 8888)..."
run_test "Native Epoll" 8888 "/home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/epoll/epoll_server"

cleanup

echo ""
echo "正在测试协程库 (端口 8080)..."
run_test "Coroutine (6hook)" 8080 "cd /home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/6hook && ./main"

cleanup

echo ""
echo "正在测试 Libevent (端口 8889)..."
run_test "Libevent" 8889 "/home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/libevent/libevent_server_8889"

cleanup

echo ""
echo "=========================================="
echo "           测试结果汇总"
echo "=========================================="
echo ""

for port in 8888 8080 8889; do
    case $port in
        8888) name="Native Epoll" ;;
        8080) name="Coroutine" ;;
        8889) name="Libevent" ;;
    esac

    file="/tmp/result_1m_c1000_${port}.txt"
    if [ -f "$file" ]; then
        echo "=== $name ==="
        grep -E "Requests per second|Time per request|Failed requests|Time taken for tests" "$file" | head -4
        echo ""
    fi
done