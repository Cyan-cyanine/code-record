# Git学习笔记
> 出处 https://mp.weixin.qq.com/s/Bf7uVhGiu47uOELjmC5uXQ
## 配置git
- `git config --system --list`以列表方式查看系统给git的配置内容
- `git config --global --list`用户可以更改的配置条目
    - `git config --global user.name "carry"`
    - `git config --global user.email "1710845733@qq.com"`

## git基本操作
`git add filename`把文件添加到暂存区
`git commit -m "description"`将暂存区的文件提交到本地库
`git commit -am "描述信息"`将文件直接提交到本地库
`git status`查看文件状态
`git log`查看提交日志
`git branch 分支名称`添加分支
`git checkout 分支`分支切换
`git branch -d 分支名称`删除分支(若分支还未合并到主分支需要用`-D`代替`-d`进行删除)
`git checkout -b 分支名称`创建分支并切换到新建的分支上
`git brach -M demo`创建一个demo分支并将该分支设为master分支
`git merge demo`将demo分支合并到当前所处的分支上
`git remote -v`查看本地仓库和哪些远程仓库有联系
`git remote add 远程地址别名 HTTPS地址`添加远程仓库地址并取别名
`ssh-keygen -t rsa -C 邮箱地址`配置ssh秘钥
`git remote set-url --add origin git@git.coding.net:KeithNull/keithnull.github.io.git`一个别名推送两个地址