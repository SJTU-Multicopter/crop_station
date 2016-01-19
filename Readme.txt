作者：Clarence Chan     日期：2015.1.18
e-mail:chg10086@yeah.net

注意：配置及代码适用环境：ubuntu14.04
ubuntu14.10等版本应该也可以，但是作者并没有试过，某些路径可能略有不同

源码下载:https://github.com/g-ch/Clarence-Chan
可以先在系统中安装git，终端执行 sudo apt-get install git
然后在某个目录中（默认home下）执行
git clone https://github.com/g-ch/Clarence-Chan.git
或者 git clone git@github.com:g-ch/Clarence-Chan.git


源码编译需要安装的环境有：
qt4.8.7
ros -jade系统

/*************第一步-安装qt相关环境******************/

qt所有相关内容下载网址：
http://download.qt.io
需要下载qt4.8.7的源码（qt-everywhere-opensource-src-4.8.7.tar.gz）以及qtcreator3.1.2.run文件

一、按装qt4.8.7
1、需安装几个环境
终端运行
sudo apt-get update
sudo apt-get install g++ libX11-dev libXext-dev libXtst-dev libqglviewer-dev

2、解压tar.gz包
tar zxvf xxx.tar.gz
此处xxx为下载的qt-everywhere-opensource-src-4.8.7

4、进入qt4.8.7安装源码的目录
./configure -multimedia -opengl
 (in case qtopengl is not installded)
choose opensource 

接着就make，然后sudo make install就可以了
（make这里时间比较长，可以先去吃饭睡觉打豆豆了）


5、设置环境：

当这几个步骤全部完成后
执行vi ~/.bashrc 添加如下内容：
QTDIR=/usr/local/Trolltech/Qt-4.8.7/
PATH=$QTDIR/bin:$PATH
MANPATH=$QTDIR/doc/man:$MANPATH
LD_LIBRARY_PATH=$QTDIR/lib:$LD_LIBRARY_PATH
export QTDIR PATH MANPATH LD_LIBRARY_PATH
之后重启。如果不会用vi可以执行vi语句后输入:$回车，然后输入o进入输入模式，将上面的字段拷贝后按esc，然后输入大写的ZZ或者输入：wq即可。



/******************第二步-安装ros相关环境**************************/
ros系统官网：ros.org
ubuntu安装jade版本的ros网址http://wiki.ros.org/jade/Installation/Ubuntu

一、安装ros jade（内容来自官网教程的翻译）

1、终端输入
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list' 设置环境

2、设定密钥
sudo apt-key adv --keyserver hkp://pool.sks-keyservers.net --recv-key 0xB01FA116

3、确保所有环境为最新版本
终端输入sudo apt-get update

4、安装ros jade
sudo apt-get install ros-jade-desktop-full
（默认安装到opt/下）

5、初始化rosdep
sudo rosdep init
rosdep update

6、设置ros环境，这样就不用每次都要setup一下了～
直接用vi把source /opt/ros/jade/setup.bash添加到~/.bashrc中也可以
如果仅要配置一次环境的话，source /opt/ros/jade/setup.bash

7、安装rosinstall
sudo apt-get install python-rosinstall


/*****************第三步-建立自己的ros工作空间*******************/
以下内容参见：http://wiki.ros.org/ROS/Tutorials

在home下创建一个名字叫做catkin_ws的文件夹作为工作空间并初始化，执行
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace

现在可以试着编译一下，执行
cd ~/catkin_ws/
catkin_make
其中catkin_make是一个很好用的编译工具，不过我们后面不会通过这种方式编译，直接在qt中编译就可以了。这里只要不报错就可以了，报错呢就google一下吧，肯定不是教程的问题。。
catkin_make之后生成的文件默认保存在catkin_ws/build/下

然后再setup一下工作空间：
source ~/devel/setup.bash 
这样工作空间的搭建就完成了，如果需要检验以下的话可以在终端输入：
echo $ROS_PACKAGE_PATH
你应该会看到显示
/home/youruser/catkin_ws/src:/opt/ros/jade/share:/opt/ros/jade/stacks



