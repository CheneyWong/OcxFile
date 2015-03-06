# OcxFile

## 需求
通过 javascript 操作客户端所有文件的 ocx 控件。
实现的方法有：
- create 创建文件
- read 读取指定的文件内容
  如果是文件，返回文件内容的 16 进制字符串。如果是文件夹，包含的文件和文件夹。
- write 将内容（16 进制字符串）转义为原始二进制写入文件。
 
## 开发
1. 由于 read 和 write 阻塞时间可能比较长，所以必须使用多线程方式。
2. 然后发现新的线程中无法将数据返回给网页。原先的设计是触发自定义事件来回调 js 的代码。自定义事件本身没有问题，测试通过。但是不能在新线程中触发，所以又改为新线程给主线程发送一个自定义消息，主线程收到自定义消息之后自己触发自定义事件。此方法在 TSTCOM32 下测试通过，但是在 IE 网页中发现无法响应自定义消息。

## 结束
IE 的自定义消息问题无法解决，中止开发。
