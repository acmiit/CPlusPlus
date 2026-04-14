# 编译器
CXX := g++

# 编译选项
CXXFLAGS := -std=c++11 -g -Wall -Wextra
INCLUDES := -I./ -I./include
LDFLAGS := -lwfrest -lworkflow -lssl -lcrypto -lcrypt -lpthread

# 目标
TARGETS := CloudiskServer testHash testToken

# 默认目标
.PHONY: all
all: $(TARGETS)

# 主服务器
CloudiskServer: main.o CloudiskServer.o Token.o Hash.o
	$(CXX) $^ -o $@ $(LDFLAGS)

# 测试程序
testHash: Hash.o testHash.o
	$(CXX) $^ -o $@ $(LDFLAGS)

testToken: Token.o testToken.o
	$(CXX) $^ -o $@ $(LDFLAGS)

# 从 .cc 编译 .o
%.o: %.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# 清理
.PHONY: clean
clean:
	rm -f *.o $(TARGETS)

# 调试
.PHONY: vars
vars:
	@echo "CXX: $(CXX)"
	@echo "CXXFLAGS: $(CXXFLAGS)"
	@echo "INCLUDES: $(INCLUDES)"
	@echo "LDFLAGS: $(LDFLAGS)"