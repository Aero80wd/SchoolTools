<p align="center">
  <img width="18%" alt="icon" src="https://github.com/user-attachments/assets/3a87e9c8-4283-454f-ba54-fc5c26ea3966">

</p>
  <h1 align="center">
  校园悬浮窗
</h1>
<p align="center">
  基于Qt6 Widgets的校园桌面悬浮窗组件
</p>

<p align="center">
  <a href="https://pypi.org/project/PyQt-Fluent-Widgets" target="_blank">
    <img src="https://img.shields.io/badge/Version-v5.0-2334D05" alt="Version">
  </a>

  <a style="text-decoration:none" href="/LICENSE">
    <img src="https://img.shields.io/badge/License-GPLv2-blue?color=#4ec820" alt="GPLv2"/>
  </a>

  <a style="text-decoration:none" href="https://github.com/Aero80wd/SchoolTools/releases">
    <img src="https://img.shields.io/badge/Platform-Windows_Only-blue?color=#4ec820" alt="Platform Win32 | Linux | macOS"/>
  </a>
</p>

<img src="https://github.com/user-attachments/assets/4459366e-60b9-4606-845d-a731f9c6c91c" alt="example">




## 功能
- 在屏幕上方显示今日的课程
- 在一言窗口上显示每日诗词
- 在悬浮窗或主窗口显示Todo
- 在屏幕侧边显示工具栏，可显示插件或快捷方式。
> **注意**<br/>
> 本项目以<a style="text-decoration:none" href="/LICENSE">GPLv2</a>协议开源，如需修改，请开源并遵守协议


## 安装
1. 下载<a href="https://gitee.com/Aero80wd/SchoolTools/releases">Release</a>内的安装包，根据安装包提示进行安装。
2. 打开程序后根据提示进行设置。
3. 开始使用。
> **注意**
> 如运行出现缺失DLL，请下载安装[VS2019运行库](https://aka.ms/vs/17/release/vc_redist.x64.exe)。
## 更新日志
### [v5.1] - 2024-10-13
- 将一言回归到工具箱
- 修复当课间为0时当前课程显示错误的bug
- 修复编辑器关闭后的课程表空白bug
- 修复换课时没有resize的bug
### [v5.0] - 2024-10-5
- UI大更新：
1. 将灵动岛连体，更改主题色，添加毛玻璃效果
2. 将一言和岛上Todo删除，一言将会在5.1回归。
3. 在悬浮窗上显示所有课程
- 支持课表同步，可同步服务端上的课表。
- ~~移除了him~~
#### [v4.1] - 2024-9-15
- 该版本为第一个较稳定版本，功能bug基本修复完毕
- 更改项目目录结构，将源文件、头文件、UI文件、资源文件进行分类
- 使用资源文件字体避免需安装字体后才可使用倒计时

## 关于插件
### 安装
打开设置中的工具栏设置，将插件文件或快捷方式放入插件列表中。
### 制作
请查看[SchoolTools-Plugin-example-win32](https://github.com/Aero80wd/SchoolTools-Plugin-example-win32)仓库的示例和README。
## 关于同步
具体见[SchoolTools-Sync-Server](https://github.com/Aero80wd/SchoolTools-Sync-Server)仓库。
## 许可证
本项目使用<a style="text-decoration:none" href="/LICENSE">GPLv2</a>协议开源，修改请遵循协议。
