This a modification of chip-tool to send the subscrition messtion via websocket
# Modifications

1. src/messaging/ExchangeMgr.h (line 57)
```c++
static uint latestNodeId;
```

2. src/messaging/ExchangeMgr.cpp (line 425)
```c++
uint ExchangeManager::latestNodeId = 999;
```

3. src/messaging/ExchangeMgr.cpp (line 221)
```c++
ExchangeManager::latestNodeId = (uint)session->GetPeer().GetNodeId();
```
4. examples/chip-tool/commands/interactive/InteractiveCommands.h (line 76)
```c++
public:
    static InteractiveServerCommand* instance;
```

5. examples/chip-tool/commands/interactive/InteractiveCommands.h (line 81)
```c++
    InteractiveServerCommand::instance = this;
```

6. examples/chip-tool/commands/interactive/InteractiveCommands.h (line 98)
```c++
public:
    WebSocketServer mWebSocketServer;
```

7. examples/chip-tool/commands/interactive/InteractiveCommands.cpp (line 404)
```c++
InteractiveServerCommand* InteractiveServerCommand::instance = nullptr;
```


8. examples/chip-tool/commands/chusters/ReportCommand.h (line 58 to 75)

```c++
  printf("\n====================================================================\n");
  uint mEndpointId = path.mEndpointId;
  uint mClusterId = path.mClusterId;
  uint mAttributeId = path.mAttributeId;
  
  int8_t tLVElementType = (int8_t)data->ElementType();
    char buf[512];
  sprintf(buf,"{\"node\":%d,\"endpoint\":%d,\"cluster\":%d,\"attribute\":%d,\"mElemLenOrVal\":%ld,\"elementType\":%d}",
  chip::Messaging::ExchangeManager::latestNodeId,
  mEndpointId,
  mClusterId,
  mAttributeId,
  data->mElemLenOrVal,
  tLVElementType
  );
  printf("SENDING: %s\n",buf);
  InteractiveServerCommand::instance->mWebSocketServer.Send(buf);
  printf("====================================================================\n\n");
```
