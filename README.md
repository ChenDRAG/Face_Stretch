# 数值分析大作业——图像变形处理
本项目目标是编写程序对人脸图像进行扭曲变形，以及图像的扭曲与畸变变换。项目使用C++/Qt5.12.4/OpenCV4在VS2019上配置编译（MSVC_2017_x64）。
（本项目目的在于能力训练，如果你不想了解底层算法或者追求代码封装简洁高效，本项目可能不是你的最优选择）
## 可执行文件及UI界面
UI界面的执行需要在Windows64位系统中使用，可以打开\face_strech_ui\x64\Release\Face_Strech_UI.exe进行使用。 
- 在主界面可以选择人脸变形或图像变形
- 人脸变形模式下，点击前两张图片可以更改选择图像（图像必须在同一文件夹下配置同名人脸关键点检测txt文件，在Resources文件夹下有范例），点击右侧图片启动变形并获得结果。
- 在图像变形界面下，用户点击左侧原图可以更改输入图片，拖动右侧控制条可以实时观察变形效果。
- 在两种界面下用户都可以改变插值策略观察不同插值方法的效果差异。
- 所有的变形都可以在5s内完成，请耐心等待10s左右，如果超出这个时间可能是出现了异常
<img src="https://github.com/ChenDRAG/Face_Stretch/blob/master/1.PNG" width=600 alt="UI">
<img src="https://github.com/ChenDRAG/Face_Stretch/blob/master/2.PNG" width=600 alt="UI">
<img src="https://github.com/ChenDRAG/Face_Stretch/blob/master/3.PNG" width=600 alt="UI">

## 文件说明
- /face_strech_ui/Face_Strech_UI/ 包含了本项目所有源码
- /face_strech_ui/x64/Release/ 包含了本项目可执行文件
- /face_strech_ui/x64/Release/main.cpp 为本项目的界面主逻辑文件
- /face_strech_ui/x64/Release/Warping.cpp 实现两项基础的图像变形
- /face_strech_ui/x64/Release/TPS.cpp 实现TPS算法
- /face_strech_ui/x64/Release/Interp.cpp 实现了三种图像插值算法
- /face_strech_ui/x64/Release/Matmath.cpp 实现了opencv数据结构的数学运算（这个文件存在的意义仅仅是由于课程要求，大部分函数都是opencv的同名函数，你可以自己实现替换）
- /face_strech_ui/x64/Release/ 中其余主要cpp文件都是界面相关的定义文件。

## 作者
作者：清华大学自动化系自76班 陈华玉  
邮箱：chenhuay17@mails.tsinghua.edu.cn  
github：chendrag

