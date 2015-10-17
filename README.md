
                     ___eSDK_uc_plugin_lync 编译指南简介___

1 编译指南 

1.1依赖文件

1.1.1  UCservice 插件 (lync 所依赖的UC库) 

1.1.2  lync插件 (lync插件源代码) 

1.1.3  self_dev (eSDK自研插件)

1.1.4  open_src (合作方开源资源) 

1.1.5  third_party_groupware (微软平台所需资源) 

1.1.6platform (华为UC&C产品线提供资源)

1.2层次关系

建立一个新文件夹，以github_lync_plugin为例，其中1.1.3—1.1.6为同一级目录，属于github_lync_plugin文件夹下的一级目录；
1.1.1—1.1.2属于同一级，新建一个子文件夹，以Source为例，将1.1.1—1.1.2 放置该目录下，该Source文件夹与上述1.1.3—1.1.6 文件夹并列。一级目录如下图所示：

二级文件夹Source目录如下图所示：

1.3编译顺序

1.3.1 打开UCService 文件夹，运行“0_拷贝依赖文件.bat”脚本，然后依次运行“1_Debug_全量编译全部.bat”和“2_Release_全量编译全部.bat”； 

1.3.2 打开lync文件夹，运行“0_拷贝依赖文件.bat”脚本，然后依次运行“1_Debug_全量编译全部.bat”和“2_Release_全量编译全部.bat”；

1.3.3 上述两步操作若无错误，打开lync文件夹下的build文件夹，经过1.3.1和1.3.2步骤会生成一个安装压缩文件，用于安装该插件。

1.4运行程序 

用VS2010打开lync文件夹下的LyncWpfApp文件夹下的LyncWpfApp.sln，选用debug或release环境下运行源代码程序。
 
