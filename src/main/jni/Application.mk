#使用的NDK库版本号,一般和SDK对应,各个版本在platforms目录下
APP_PLATFORM = android-24
 
#不写APP_ABI就生成全部支持的平台
APP_ABI := all
 
#如何链接C++标准库,stlport_static表示静态链接、stlport_shared表示动态链接
APP_STL := c++_shared
 
#编译为release版本
APP_OPTIM := debug

#允许某些依赖不存在
APP_ALLOW_MISSING_DEPS=true

#编译支持异常
APP_CPPFLAGS += -fexceptions

APP_CPPFLAGS += -frtti