# 内存检查工具Valgrind的使用   

## 1 Valgrind的简介   
-  Valgrind是一款用于内存调试、内存泄漏检测以及性能分析的软件开发工具。 最初作者是Julian Seward，他于2006年由于在开发Valgrind上的工作获得了第二届Google-O'Reilly开源代码奖。     
- 遵守GNU通用公共许可证条款，是一款自由软件。   
- 此工具由内核（core）以及基于内核的其他调试工具组成。内核类似于一个框架，模拟了一个CPU环境，并提供服务给其他工具：而其他工具则类似于插件， 利用内核提供的服务完成各种特定的内存调试任务。    

## 2 Valgrind的下载与安装   
```shell
sudo apt-get install valgrind
```
## 3 valgrind的用法    
### 3.1 valgrind在GCC下的使用   

```shell
valgrind --tool=memcheck --leak-check=yes --show-reachable=yes ./test   
```


### 3.2 valgrind在linux-qt下的使用    
- 自动加载到qtcreator的开发环境模块      

### 3.3 valgrind在win-qt下的使用    
- 必须是msvc编译器才能用，mingw编译器不能用    


## 4  参考资料   

1. https://blog.csdn.net/tao546377318/article/details/51766164    
2. https://blog.csdn.net/fan_hai_ping/article/details/8173240?utm_medium=distribute.pc_relevant.none-task-blog-OPENSEARCH-2.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-OPENSEARCH-2.channel_param   
3. https://blog.csdn.net/q5707802/article/details/45181343?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param    
4. https://blog.csdn.net/fengbingchun/article/details/50196189?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.channel_param     
5. https://blog.csdn.net/weixin_38293850/article/details/84189733?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.channel_param     
6. https://blog.csdn.net/inter_xuxing/article/details/19764633  
7. https://blog.csdn.net/xianquji1676/article/details/106168321