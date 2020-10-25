# 如何写shell脚本获取本机时间   

## 1 命令行实现    

```shell 
date "+%Y%m%d%H%M%S"   # 20201025194313  
```

## 2 shell脚本编写   
### 2.1 脚本的框架   
```shell 
#!/bin/sh
current_time=$(date "+%Y%m%d%H%M%S")
git add .
git commit -m ${current_time}
git push  
```   

## 参考资料  
1. https://www.cnblogs.com/wuhuohanke/p/10083798.html   
2. https://jingyan.baidu.com/article/7c6fb428fa08b280642c90ea.html    

