# STM32RCT6 工程架构（STM32F103RCT6 + FreeRTOS + CMake）

## 分层与依赖方向

```
Application 应用层  App/           业务逻辑：任务、调度、模块初始化编排
      |
Module      模块层  Module/        设备模块：按键、蜂鸣器，对外只暴露设备 API
      |
Driver      驱动层  Bsp/           通用外设驱动：GPIO 按键扫描等
      |
Low-Level   底层    Core/ Drivers/(HAL+CMSIS) Freertos/
```

依赖只能**从上往下**：应用层可调模块层，模块层可调驱动层，驱动层可调 HAL。
反向调用（模块层直接调应用层任务、驱动层调业务 API）应当禁止。

## 各目录职责

| 目录 | 层 | 内容 |
| --- | --- | --- |
| `Core/` | 底层 | CubeMX 生成：启动文件、时钟、GPIO/UART 初始化、中断、时间基准 |
| `Drivers/STM32F1xx_HAL_Driver`、`Drivers/CMSIS` | 底层 | 厂商 HAL 与 CMSIS，**不要手动改** |
| `Freertos/` | 底层 | FreeRTOS 内核、port、`FreeRTOSConfig.h` |
| `Bsp/` | 驱动层 | `key.c/.h`：通用 GPIO 按键驱动（`KeyHandle_TypeDef`、`Key_Init`、`Key_Scan`），与具体按键无关。**注意与下面厂商的 `Drivers/` 是两个不同目录** |
| `Module/key/` | 模块层 | `key1.c~key4.c`：4 个按键实例，各自绑定引脚与回调 |
| `Module/buzzer/` | 模块层 | `buzzer.c/.h`：蜂鸣器设备 API（`Buzzer_Init`/`Buzzer_Beep`/`Buzzer_WaitBeep`/`Buzzer_On`/`Buzzer_Off`） |
| `App/` | 应用层 | `app.c`（`App_Init` 统一初始化+建任务）、`key_task.c`、`buzzer_task.c` |

`Settings`、`.ioc`、CMake 预设、OpenOCD 配置、构建脚本等属于工程配置，保持原样。

## 调用链

```
main()  ->  App_Init()
              |-- Key1_Init .. Key4_Init      (模块层)
              |-- Buzzer_Init                 (模块层，创建鸣叫信号量)
              |-- xTaskCreate(Key_Task)       (应用层)
              +-- xTaskCreate(Buzzer_Task)    (应用层)
                            |
Key_Task --10ms--> Key1..4_Scan (模块层) --> Bsp/key.c 边沿检测
                            |
                    按键回调 --> Buzzer_Beep() (模块层，释放信号量)
                            |
Buzzer_Task <-- Buzzer_WaitBeep() --> Buzzer_On()/Off() 响 100ms
```

## 新增一个模块 / 按键

1. 驱动层：若涉及新外设，在 `Bsp/` 增加通用驱动（只做寄存器/HAL 级操作）。
2. 模块层：在 `Module/<设备>/` 增加模块，头文件里只暴露设备 API，不 include 任何任务头文件。
3. 应用层：在 `App/` 增加任务，并在 `App/app.c` 的 `App_Init()` 中初始化模块、创建任务。
4. `CMakeLists.txt` 的两个列表都要改（本工程**不使用 GLOB**）：
   - `add_executable(...)` 里加新的 `.c`
   - `target_include_directories(...)` 里加新的头文件目录
5. `core_include` 之外不要再引入相对路径（如 `#include "../xxx.h"`），统一用 `-I` 目录下的文件名。

## 构建与烧录

```powershell
cmake --build --preset debug        # 或 VS Code 任务 "CMake: Build Debug"
.\build-and-flash.ps1               # 构建 + OpenOCD 烧录（任务 "STM32: Flash Debug"）
```

## 注意事项

- `Core/`、`Drivers/(HAL+CMSIS)` 由 CubeMX 管理，重新生成会覆盖，业务代码一律不要放进去；
  入口只在 `main.c` 的 `USER CODE` 段调用 `App_Init()`。
- 生效的 FreeRTOS 配置是 `Freertos/Inc/FreeRTOSConfig.h`（`FreeRTOS.h` 以引号形式包含它，
  优先搜索自身目录），`Core/Inc/FreeRTOSConfig.h` 实际不生效，两份内容已不一致。
- `.cproject` / `.launch` / `Debug/` 是旧的 STM32CubeIDE、Keil 残留，不参与 CMake 构建，
  其中的 include 路径未跟随本次分层更新，仅在使用 CubeIDE 打开时才需要处理。
