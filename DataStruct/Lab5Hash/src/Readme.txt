1.哈希函数采用了形如h(k) = (A·k mod m) rsh (w–r)的双重哈希函数，
具体算法见StudentHash.cpp中的StuHashFun函数；

2.StudentHash.h和StudentHash.cpp实现了满足实验要求的哈希表，
其中class StuInf负责包装学生信息，class StuHash实现主要功能，
除Search、Insert、Delete操作外，还提供了函数ReadinCSV，其通过调用Insert将csv文件全部读入StuHash中；

3.test.cpp 测试了相关功能，并通过实验计数得到哈希表中所有名字的平均搜索时间(次数)为1.41611，
a.exe是以上文件编译得到的可执行文件；

4.所有文件采用GBK编码；