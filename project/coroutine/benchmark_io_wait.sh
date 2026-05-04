#!/bin/bash

cleanup() {
    pkill -9 -f "epoll_server|libevent|main" 2>/dev/null
    sleep 2
}

run_test() {
    local name=$1
    local port=$2
    local cmd=$3
    local requests=$4
    local concurrent=$5

    echo ""
    echo "=========================================="
    echo "Testing: $name (port $port)"
    echo "Requests: $requests, Concurrency: $concurrent"
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

    ab -n $requests -c $concurrent http://127.0.0.1:$port/ 2>&1 | tee /tmp/result_io_${port}.txt

    kill $SERVER_PID 2>/dev/null
    sleep 2
}

cleanup

echo "=========================================="
echo "  IO等待模拟性能测试 (每请求10ms等待)"
echo "  100万请求 1000并发"
echo "=========================================="

echo ""
echo "正在测试协程库 (端口 8080)..."
run_test "Coroutine (1 thread + hook)" 8080 "cd /home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/6hook && ./main" 1000000 1000

cleanup

echo ""
echo "正在测试 Epoll+ThreadPool (端口 8888, 1线程)..."
run_test "Epoll+ThreadPool (1 thread)" 8888 "/home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/epoll_threadpool/epoll_server" 1000000 1000

cleanup

echo ""
echo "=========================================="
echo "           测试结果对比"
echo "=========================================="
echo ""

for port in 8080 8888; do
    case $port in
        8080) name="协程库 (1线程+hook)" ;;
        8888) name="Epoll+线程池 (1线程)" ;;
    esac

    file="/tmp/result_io_${port}.txt"
    if [ -f "$file" ]; then
        echo "=== $name ==="
        grep -E "Requests per second|Time per request|Failed requests|Time taken for tests|Transfer rate" "$file" | head -5
        echo ""
    fi
done