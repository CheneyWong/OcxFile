# OcxFile

## 需求
通过 javascript 操作客户端所有文件的 ocx 控件。
实现的方法有：
- create 创建文件
- read 读取指定的文件内容
  如果是文件，返回文件内容(base64 编码)。【TODO】如果是文件夹，列出包含的文件和文件夹。
- write 将内容(base64 编码)转义为原始二进制写入文件。

##　其他
- 由于编码中包含 ‘+’ 、‘/’ 和 ‘=’ 等特殊字符，如果需要提交到 web 后台，需要先调用 encodeURIComponent 转义
- debug 目录下有注册文件和网页调用 demo
- 更多内容请访问[这里](http://gpio.me/ocx-file.html) 


>注
网页调用时 ocx 控件如果隐藏则自定义消息失败，可通过将元素的长宽设为 0 作为替代。
