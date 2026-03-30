# Screenshots

这一页专门说明首页里用到的界面图分别在展示什么，避免截图只是摆在 README 里却没有上下文。

## 1. System Flow

![System flow](../images/system-flowchart-original.png)

这张图来自我原始课程说明书里的系统流程图，不是后来为了仓库展示重新补画的。

我当时用它来说明整个系统的主流程，里面覆盖了：

- 传感器初始化和串口设置
- 车辆端连接与控制逻辑
- 服务端数据处理和查询逻辑
- 驾驶端消息框与 CSV 保存链路

## 2. Vehicle Main UI

![Vehicle main UI](../images/car-main-ui.png)

这张图展示的是车辆端主界面。这里集中承接了：

- 实时显示速度、前车距离、前方行人数
- 接收服务端返回的提示信息
- 控制传感器启动、继续、暂停、停止
- 提供数据可视化、文件保存、日志查询等入口

## 3. Data Server UI

![Data server UI](../images/data-server-ui.png)

这张图展示的是服务端界面。这里主要负责：

- 记录客户端连接时间、IP、端口和在线状态
- 展示网络消息记录
- 控制服务器监听端口
- 作为多客户端接入和反馈节点

## 4. Sensor UI

![Sensor UI](../images/sensor-ui.png)

这张图展示的是传感器端界面。这里主要负责：

- 选择传感器类型
- 打开或关闭串口
- 启动模拟数据输出
- 记录传感器日志

这个版本里，传感器数据仍然以模拟为主。这是我当时为了优先验证通信链路而做的取舍。

## 5. CSV Query UI

![CSV query UI](../images/csv-query-ui.png)

这张图展示的是我后来补的查询界面。这里主要负责：

- 按用户、传感器类型、数值范围、时间范围筛选数据
- 回看传感器数据记录
- 让系统从“能发数据”进一步走到“能查询历史记录”

## 6. Vehicle-to-Vehicle Messaging UI

![Vehicle messaging UI](../images/vehicle-messaging-ui.png)

这张图展示的是车辆间通信界面。这里主要负责：

- 查看在线车辆信息
- 选择对方端口进行配对
- 发送消息或共享数据
- 通过服务端辅助端口完成中转通信

我把这部分单独做成一条辅助链路，是因为它和主上传链路解决的是不同问题。
