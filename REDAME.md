# 学生通讯录(WinUI3)

## 安装方式

### 方法一（推荐）

右键使用PowerShell运行Install.ps1，这将会自动安装签名和所需依赖包。

![image-20221205215527116](C:\Users\82135\AppData\Roaming\Typora\typora-user-images\image-20221205215527116.png)

### 方法二（备用）

此处以其他msix安装包为例子.

1. 安装软件前请先安装依赖包[^1]

2. 安装软件前请先安装自签名证书[^2]（没有申请开发者账号，用VS生成了一个自签名证书）

3. 最后安装软件[^3]后，可以在 *开始菜单——最近添加* 里面找到[^4]

   

[^1]: 依赖包在Dependencies文件夹内，请根据系统架构进行选择。例如，我的电脑是x86架构的64位操作系统，安装Dependencies文件夹内的x64文件夹的3个依赖包。

![Pasted image 20221102095750](D:\华师\数据结构\Pasted image 20221102095750.png)

[^2]: 自签名证书在图形界面软件包目录下，文件名为Tree_1.0.0.0_x64.cer(图中高亮选中)，打开后请选择安装证书，具体安装步骤参考下图。最后提示导入成功即为安装成功。

<img src="D:\华师\数据结构\Pasted image 20221102100338.png" alt="Pasted image 20221102100338" style="zoom:50%;" />

<img src="D:\华师\数据结构\Pasted image 20221102100018.png" alt="Pasted image 20221102100018" style="zoom:67%;" />

<img src="D:\华师\数据结构\Pasted image 20221102100103.png" alt="Pasted image 20221102100103" style="zoom:50%;" />

<img src="D:\华师\数据结构\Pasted image 20221102100130.png" alt="Pasted image 20221102100130" style="zoom:50%;" />

<img src="D:\华师\数据结构\Pasted image 20221102100146.png" alt="Pasted image 20221102100146" style="zoom:50%;" />

<img src="D:\华师\数据结构\Pasted image 20221102100200.png" alt="Pasted image 20221102100200" style="zoom:67%;" />

<img src="D:\华师\数据结构\Pasted image 20221102100214.png" alt="Pasted image 20221102100214" style="zoom:67%;" />

[^3]: 软件安装包（图中高亮处），软件默认安装至Windows应用商店的软件安装目录，需要卸载的时候只需要在开始菜单找到右键卸载即可。

<img src="D:\华师\数据结构\Pasted image 20221102100755.png" alt="Pasted image 20221102100755" style="zoom:50%;" />



## 编译需求

(翻译自微软[开源文档](https://github.com/microsoft/WindowsAppSDK-Samples/blob/main/README.md))

该Windows App SDK应用需要满足以下的系统要求：

- Windows 10, version 1809 (build 17763) 或更新，64位架构.
- [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/) 或 Visual Studio 2019 (16.9或更新), 并安装了以下组件
  - 通用 Windows 平台开发(Universal Windows Platform development)
  - .NET桌面开发 (.NET Desktop Development) (即使你只需要构建 C++ Win32 应用)
  - 使用 C++ 的桌面开发(Desktop development with C++) (即使你只需要构建 .NET 应用)
  - Windows SDK 版本2004 (build 19041) 或更新. 正常来说Visual Studio已默认安装了.

更多使用Windows App SDK开发信息请参考[系统需求]((https://docs.microsoft.com/windows/apps/windows-app-sdk/system-requirements) )文档和[Windows应用开发工具](https://docs.microsoft.com/windows/apps/windows-app-sdk/set-up-your-development-environment)文档.