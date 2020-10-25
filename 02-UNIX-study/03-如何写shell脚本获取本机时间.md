# 如何写shell脚本获取本机时间   

## 1 命令行实现    

```shell 
date "+%Y%m%d%H%M%S"   # 20201025194313  
```

## 2 shell脚本编写   
### 2.1 脚本的框架   
```shell 
#!/bin/sh
D = date "+%Y%m%d%H%M%S" 
git add .
git commit -m D
git push  
```

