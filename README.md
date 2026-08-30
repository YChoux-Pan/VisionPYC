# VisionPYC
环境搭建，目前使用的是QT6+VS2022+OpenCV
针对于工业检测上的一个软件，包含2D、3D的高度、平面度、定位等等算子，集成常见的通信，集成海康相机接口，3D相机集成湾测，目前还正在完善功能，后续会持续更新搭建更多的算子和功能



2026/5/5
更改了整体的架构，目前现在是拖拽式，树状的形式进行流程，搞了个初步的DEMO,界面上先搞了两个模块，一个是图像检测一个是3D检测，不过还有很多优化的地方，准备先把架构优化好了再进行算子的填充，下一步把流程跑通吧



2026/5/6

增加QSS样式，增加一个采集图像模块，加入opencv库



2025/5/9 
目前对采集图像模块进行了优化，主要是界面方面，需要注意的点是qss的加载是需要按照背景向外加载的，顺序乱了会造成渲染界面的覆盖

前期部分搭建的比较慢，因为我一直再找一个比较好的架构，不过找不到那就先做吧，到后面再陆陆续续优化架构

目前想到的是，还需要建立一个日志打印系统，包含log和dump报错的打印，外加内存堆栈的监视，方便解决内存泄漏问题



2026/5/16

终于有时间更新了，新增了一些ui模板参数的用法，增加SVG图标，新设计好了预处理图像界面

---

2026/8/30 架构重构（线性流程）

- 删除图引擎，完全使用线性流程架构
- 新增算子注册表 NodeRegistry：新增算子只需 1 行 REGISTER_NODE 宏，旧代码零改动
- 新增 FlowEngine 流程引擎：QThread + 工作队列异步执行，UI 不卡顿
- 流程树重构：只持节点 ID，支持右键删除/上移/下移，运行状态实时显示
- 修复采集图像模块 process 分支 bug、OpenCV Debug 配置、跨线程图像访问
- 新增 --selftest 自检模式：验证注册表/数据流/序列化/失败路径


---

## 架构重构（线性流程） — 2026/8/30

### 目标
- 算法模块化：新增算子只需 1 个类 + 1 行注册宏，旧代码零改动
- 删除图引擎，完全使用线性流程
- 异步执行：QThread + 工作队列，不阻塞 UI

### 架构分层
```
GUI 层      NodeSelectorWidget / WorkflowTreeWidget / MainWindow（只持节点ID，不持算法指针）
Core 层     FlowEngine(唯一入口) -> FlowModel(线程安全节点模型) + FlowWorker(工作线程执行器)
             + NodeRegistry(静态算子注册表)
Plugins 层  BaseAlgorithmNode 基类 + ImageFilterNode / _3DProcessNode（注册宏接入）
Common 层   IFlowNode v2（typeKey/displayName/端口描述/参数持久化）
```

### 新增算子三步走
1. 继承 `BaseAlgorithmNode`，实现 `typeKey()/displayName()/category()`、端口、`process()`、`createConfigWidget()`
2. 源文件末尾写一行：`REGISTER_NODE(MyNode, "MyKey", "分类", "显示名")`
3. 编译后左侧算子库自动出现，可直接拖入流程树运行

### 核心机制
- 线性自动串联：节点 i 的输入端口 j ← 节点 i-1 的输出端口 j（类型匹配时）
- 参数持久化：每个算子实现 `saveParams()/loadParams()`，`FlowEngine::serializeFlow()/loadFlow()` 保存整个流程
- 线程安全：FlowModel 内部 QMutex；运行期间 GUI 拒绝编辑（runningChanged 信号禁用流程树）
- 自检：运行 `VisionPYC.exe --selftest` 验证核心引擎（注册表/数据流/序列化/失败路径）

### 运行
- 仅支持 Release|x64 编译运行（OpenCV 为 Release 版库）
- Debug 配置已通过 `CV_IGNORE_DEBUG_BUILD_GUARD` 兼容 Release 版 OpenCV
