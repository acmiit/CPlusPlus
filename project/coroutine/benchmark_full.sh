#!/bin/bash

cleanup() {
    pkill -9 -f "epoll_server|libevent|main" 2>/dev/null
    sleep 1
}

run_test() {
    local name=$1
    local port=$2
    local cmd=$3
    local concurrent=$4
    local requests=$5
    local keepalive=$6

    echo ""
    echo "=========================================="
    echo "Testing: $name (port $port)"
    echo "Concurrency: $concurrent, Requests: $requests, Keep-Alive: $keepalive"
    echo "=========================================="

    eval "$cmd &"
    SERVER_PID=$!
    sleep 1

    if ! ss -tlnp 2>/dev/null | grep -q ":$port "; then
        echo "Server failed to start!"
        kill $SERVER_PID 2>/dev/null
        return 1
    fi

    echo "Server started with PID: $SERVER_PID"

    if [ "$keepalive" = "yes" ]; then
        ab -n $requests -c $concurrent -k http://127.0.0.1:$port/ 2>&1 | tee /tmp/result_${port}_c${concurrent}_k.txt
    else
        ab -n $requests -c $concurrent http://127.0.0.1:$port/ 2>&1 | tee /tmp/result_${port}_c${concurrent}.txt
    fi

    kill $SERVER_PID 2>/dev/null
    sleep 1
}

cleanup

echo "=========================================="
echo "  Coroutine Library Benchmark - Full Test"
echo "=========================================="

# 测试参数
CONCURRENT_LEVELS=(10 50 100 200)
REQUESTS=5000

echo ""
echo "========== 1. 高并发短连接测试 =========="

for c in "${CONCURRENT_LEVELS[@]}"; do
    run_test "Native Epoll" 8888 "/home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/epoll/epoll_server" $c $REQUESTS "no"
    cleanup
    run_test "Coroutine (6hook)" 8080 "cd /home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/6hook && ./main" $c $REQUESTS "no"
    cleanup
    run_test "Libevent" 8889 "/home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/libevent/libevent_server_8889" $c $REQUESTS "no"
    cleanup
done

echo ""
echo "========== 2. 长连接测试 (Keep-Alive) =========="

for c in 10 50 100; do
    run_test "Native Epoll (Keep-Alive)" 8888 "/home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/epoll/epoll_server" $c $REQUESTS "yes"
    cleanup
    run_test "Coroutine (Keep-Alive)" 8080 "cd /home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/6hook && ./main" $c $REQUESTS "yes"
    cleanup
    run_test "Libevent (Keep-Alive)" 8889 "/home/yxl/Cplusplus/knowledge_star/coroutine-lib-main/fiber_lib/libevent/libevent_server_8889" $c $REQUESTS "yes"
    cleanup
done

echo ""
echo "=========================================="
echo "All tests completed!"
echo "=========================================="

echo ""
echo "========== 汇总对比 =========="
echo ""

extract_qps() {
    local file=$1
    grep "Requests per second:" $file | awk '{print $4}'
}

extract_latency() {
    local file=$1
    grep "Time per request:" $file | head -1 | awk '{print $4}'
}

echo "高并发短连接测试结果:"
echo "---------------------"
for c in "${CONCURRENT_LEVELS[@]}"; do
    echo ""
    echo "并发数: $c"
    f1="/tmp/result_8888_c${c}.txt"
    f2="/tmp/result_8080_c${c}.txt"
    f3="/tmp/result_8889_c${c}.txt"

    if [ -f "$f1" ]; then
        echo "  Native Epoll:  QPS=$(extract_qps $f1), 延迟=$(extract_latency $f1)ms"
    fi
    if [ -f "$f2" ]; then
        echo "  Coroutine:      QPS=$(extract_qps $f2), 延迟=$(extract_latency $f2)ms"
    fi
    if [ -f "$f3" ]; then
        echo "  Libevent:       QPS=$(extract_qps $f3), 延迟=$(extract_latency $f3)ms"
    fi
done

echo ""
echo "长连接测试结果:"
echo "---------------------"
for c in 10 50 100; do
    echo ""
    echo "并发数: $c (Keep-Alive)"
    f1="/tmp/result_8888_c${c}_k.txt"
    f2="/tmp/result_8080_c${c}_k.txt"
    f3="/tmp/result_8889_c${c}_k.txt"

    if [ -f "$f1" ]; then
        echo "  Native Epoll:  QPS=$(extract_qps $f1), 延迟=$(extract_latency $f1)ms"
    fi
    if [ -f "$f2" ]; then
        echo "  Coroutine:      QPS=$(extract_qps $f2), 延迟=$(extract_latency $f2)ms"
    fi
    if [ -f "$f3" ]; then
        echo "  Libevent:       QPS=$(extract_qps $f3), 延迟=$(extract_latency $f3)ms"
    fi
done