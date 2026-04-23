INCLUDES:=./  ./include
SRCS:=$(wildcard *.cc)
LIBS:=  -lwfrest -lworkflow -lssl -lcrypto -lcrypt -fno-rtti -lalibabacloud-oss-cpp-sdk -lcurl -lpthread -lrabbitmq
OBJS:=$(patsubst %.cc, %.o, $(SRCS))
SERVER:= CloudiskServer

# 目标 : 依赖
$(SERVER): main.o CloudiskServer.o Token.o Hash.o RabbitMQPublisher.o OssBackup.o
	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

%.o:%.cc
	g++ -c $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

BACKUP:=BackupWorker
$(BACKUP): BackupWorker.o RabbitMQConsumer.o OssBackup.o RabbitMQPublisher.o
	g++ $^ -o $@ -Wl,--no-as-needed $(LIBS) $(addprefix -I, $(INCLUDES)) -g

HASH:=testHash
TOKEN:=testToken

$(HASH): Hash.o testHash.o
	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

$(TOKEN): Token.o testToken.o
	g++ $^ -o $@ $(LIBS) $(addprefix -I, $(INCLUDES)) -g

echo:
	echo $(INCLUDES)
	echo $(SRCS)

clean:
	rm -rf $(OBJS) $(SERVER) $(HASH) $(TOKEN) $(BACKUP)
