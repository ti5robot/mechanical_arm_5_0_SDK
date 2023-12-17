---
sort: 3
---
# 环境安装

运动控制程序建议使用Ubuntu 22.04的X86架构下的linux平台运行，


首先在终端中输入以下命令下载SDK：

cd   ~

git clone https://github.com/mrhouse-sweet/mechanical_arm_SDK-docs.git

注意：如果输入上面命令提示：Command 'git' not found, but can be installed with:sudo apt install git
则在终端中输入命令安装git：sudo apt install git

## 依赖安装

+ `libspdlog-dev`
+ `libopencv-dev`
+ `libudev-dev`

```bash
sudo apt update
sudo apt install -y libspdlog-dev libopencv-dev libudev-dev
```
+ `将usrlib中的libcontrolcan.so  libmylibscan.so libmylibti5.so文件拷贝到/usr/lib/下`

```bash
cd ~/mechanical_arm_SDK-docs/code/usrlib
sudo cp * /usr/lib
```


# SDK运行

## 实机控制

**①** 首先对机械臂进行通电 

**②** 编译src文件夹下的文件，生成可执行文件，例：

```shell
首次编译需要执行以下两条命令
cd ~/mechanical_arm_SDK-docs/code/src
export CPLUS_INCLUDE_PATH=~/mechanical_arm_SDK-docs/code/include:$CPLUS_INCLUDE_PATH
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/mechanical_arm_SDK-docs/code/include/can

然后进行编译：
sudo chmod +x gcc.sh
./gcc.sh
或者使用：
g++ main.cpp  -L./include -lmylibti5 -L./include/can -lmylibscan -lcontrolcan -lspdlog -lfmt -ludev -o move_sov
```

**③** 执行`sudo ./move_sov`

当执行该条命令后，终端会打印`找到的 CAN 设备序列号：USBCAN-31F10001C21`语句(这里的设备号会随着不同的can设备改变不是固定的)，我们可以看到已经成功连接can设备，并于机械臂建立了通讯。
接下来机械臂会按照程序执行相应的动作。

