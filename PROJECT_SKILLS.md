# VisionPYC 项目 Skills 文档

> 本文档汇总本项目（VisionPYC）的完整上下文，供 AI 助手下次接手时快速恢复状态。
> 更新时间：2026/8/30

---

## 1. 项目身份

**VisionPYC** —— 工业机器视觉检测软件（Windows x64）。

- 技术栈：**Qt 6.5.3 (msvc2019_64) + VS2022 (v143) + OpenCV 4.10.0**
- 目标功能：2D/3D 高度、平面度、定位等算子；海康相机接口；湾测 3D 相机接口；常见通信
- 交互方式：**拖拽式流程编排**（左侧算子库 → 拖入中间流程树 → 右侧图像结果显示）
- 当前状态：**早期 DEMO**，已完成线性流程架构 + 采集图像 + 图像预处理 20 个算子
- **仅支持 Release 编译运行**（OpenCV 为 Release 版库；Debug 已通过 `CV_IGNORE_DEBUG_BUILD_GUARD` 兼容）

## 2. 环境路径（本机）

| 项 | 路径 |
|---|---|
| 项目根 | `e:\010-VisonPYC\VisionPYC\VisionPYC` |
| 工程文件 | `VisionPYC\VisionPYC.vcxproj` / `VisionPYC.sln` |
| OpenCV SDK | `00_SDK\OpenCV`（include + lib，Release 库 `opencv_world4100.lib`） |
| Qt 安装 | `D:\QT6.5.3\6.5.3\msvc2019_64` |
| QtMsBuild | `C:\Users\10644\AppData\Local\QtMsBuild` |
| MSBuild | `D:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe` |
| 验证图片目录 | `C:\Users\10644\Pictures\Saved Pictures`（壁纸 png 可用） |
| Git 远程 | `https://github.com/YChoux-Pan/VisionPYC.git` |

## 3. 架构（2026/8/30 重构后：完全线性流程）

```
GUI 层      NodeSelectorWidget / WorkflowTreeWidget / MainWindow（只持节点ID，不持算法指针）
Core 层     FlowEngine(唯一入口单例)
            ├─ NodeRegistry   静态算子注册表（REGISTER_NODE 宏）
            ├─ FlowModel      线程安全线性节点模型（QMutex）
            └─ FlowWorker     QThread + 工作队列执行器（QueuedConnection 调度）
Common 层   IFlowNode v2（typeKey/displayName/端口描述/参数持久化）
Plugins 层  BaseAlgorithmNode + ImageFilterNode + _3DProcessNode + PreprocessCore
Tools 层    ImageViewWidget(图像显示) / ImageListView / OperatorButton / AutoWrapLabel
```

**已删除**：CoreManager / FlowGraph / GraphExecutor / NodeDataModel / NodeFactory（图引擎全部移除）

### 核心机制
- **数据流自动串联**：节点 i 的输入端口 j ← 节点 i-1 的输出端口 j（类型匹配时）；采集节点无输入端口 = 数据源
- **参数持久化**：每个算子实现 `saveParams()/loadParams()`；`FlowEngine::serializeFlow()/loadFlow()` 保存整个流程为 JSON（`*.vpjson`）
- **线程安全**：FlowModel 内部 QMutex；节点参数 `paramsSnapshot()/setParams()` 加锁；预览图像缓存加锁；CameraInputWidget 图像访问加锁
- **运行期间拒绝编辑**：`runningChanged` 信号禁用流程树和运行按钮
- **结果实时显示**：`nodeFinished` 信号 → MainWindow `displayNodeResult()` → 右侧 ImageViewWidget

### 关键目录
```
VisionPYC/src/
├── Common/   IFlowNode.h, FlowPort.h, NodeData.h(ImageData/ScalarData), GlobalDef.h, INodeData.h, CommonUtils.h
├── Core/     FlowEngine.h/cpp, FlowModel.h/cpp, FlowWorker.h/cpp, NodeRegistry.h/cpp
├── GUI/      WorkflowTreeWidget, NodeSelectorWidget, CollapsibleCategory
├── Plugins/  BaseAlgorithmNode, ImageFilterNode, _3DProcessNode, PreprocessCore(算法核心),
│              CameraInputWidget, PreProcessWidget, RoiWidget, Height3DWidget, Planeness3DWidget
└── Tools/    ImageViewWidget, ImageListView, OperatorButton, AutoWrapLabel
```

## 4. 构建与验证命令（PowerShell）

```powershell
# 编译 Release（项目根目录执行）
& 'D:\Program Files\Microsoft Visual Studio\18\Community\MSBuild\Current\Bin\MSBuild.exe' `
  'e:\010-VisonPYC\VisionPYC\VisionPYC\VisionPYC.sln' `
  /p:Configuration=Release /p:Platform=x64 `
  /p:QtMsBuild='C:\Users\10644\AppData\Local\QtMsBuild' /m /v:m /nologo

# 编译 Debug（同样参数，Configuration=Debug）

# 核心引擎自检（验证注册表/数据流/序列化/预处理算法/端到端流程）
x64\Release\VisionPYC.exe --selftest

# 读取编译日志（MSBuild 输出为 UTF-16LE，用 Python 解析）
python -c "import sys; sys.stdout.reconfigure(encoding='utf-8'); s=open('build.log','rb').read().decode('utf-16-le','replace'); print('\n'.join([l for l in s.split('\n') if 'error' in l.lower()]))"
```

## 5. 本次已实现功能（2026/8/30）

### 架构重构（commit 358eaad）
- 线性流程架构 + 算子注册表 + QThread 工作队列执行引擎
- IFlowNode v2（typeKey/displayName/端口描述/参数持久化）
- 流程树右键删除/上移/下移，运行状态实时显示

### 功能完善（commit 7f1fbbe）
- **文件菜单**：新建/打开/保存流程（`*.vpjson`）
- **图像预处理 20 个算子**（PreprocessCore，全部 OpenCV 实现）：
  灰度/镜像/旋转/深度转彩色/修改尺寸/均值·中值·高斯滤波/膨胀·腐蚀·开·闭运算/锐化/对比度/亮度/反色/边缘增强/二值化·均值二值化·彩色二值化
- **预处理配置窗口**：动态参数面板 + 执行实时预览 + 确定保存参数
- **采集图像**：修复首次加载 bug，确定保存图像
- **右侧大界面**：QOpenGLWidget → ImageViewWidget，流程结果实时显示

## 6. 新增算子三步（旧代码零改动）

```cpp
// 1. 继承 BaseAlgorithmNode，构造函数签名 explicit Class(QString typeKey = QString())
class GaussianBlurNode : public BaseAlgorithmNode {
public:
    explicit GaussianBlurNode(QString typeKey = QString());
    QString typeKey() const override;      // 注册键
    QString displayName() const override;  // 显示名
    QString category() const override;     // 分类
    QVector<FlowPort> inputPorts() const override;
    QVector<FlowPort> outputPorts() const override;
    bool process() override;               // 算法实现
    QWidget* createConfigWidget() override;
    QJsonObject saveParams() const override;
    void loadParams(const QJsonObject&) override;
};

// 2. 源文件末尾一行注册（自动出现在左侧算子库）
REGISTER_NODE(GaussianBlurNode, "GaussianBlur", "图像处理", "高斯滤波")

// 3. 编译，无需改 MainWindow/WorkflowTreeWidget
```

## 7. 用户偏好与注意事项

- **只编译 Release**（Debug 兼容但非目标）；GUI 是 QApplication + `app.exec()`
- 编译前若有 git 提示文件占用（exe 被锁），先 `Stop-Process -Name VisionPYC,msbuild,cl`
- **不要用 PowerShell 直接改含中文的 .ui/.xml 文件**（GBK 解码会破坏 UTF-8 编码，导致中文乱码 + XML 损坏）——必须用 editor 工具
- git 操作若出现 `index.lock` 残留：删除 `.git\index.lock` 再重试
- 提交后推送：`git push origin refactor/linear-flow:main`（避免 checkout 时 exe 占用问题）
- 右侧/配置窗口图像显示统一用 `ImageViewWidget::updatedisplayMat(cv::Mat)`
- 流程保存文件后缀约定：`*.vpjson`

## 8. 已知待办 / 后续方向

- [ ] **日志系统**：log + dump 崩溃打印 + 内存堆栈监视（README 中规划）
- [ ] ROI 设置算子：真正实现 ROI 提取算法（当前透传）
- [ ] 3D 检测算子：高度检测、平面度检测算法（当前透传）
- [ ] 相机接入：海康相机、湾测 3D 相机
- [ ] 算子参数从 UI 控件完整同步（PreProcessWidget 已做，CameraInputWidget 部分）
- [ ] 流程树节点图标、算子分类展示优化

## 9. Git 状态

- 当前分支：`refactor/linear-flow`（最新 = `origin/main`）
- 本地 `main` 分支停留在旧提交（远程 main 已用 push 方式更新，如需同步本地 main 需处理 exe 占用）
- .gitignore：`.vs/`、`x64/`、`*.log`（构建产物不提交）
