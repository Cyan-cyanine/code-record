# Git学习笔记
> 出处 https://mp.weixin.qq.com/s/Bf7uVhGiu47uOELjmC5uXQ
## 配置git
- `git config --system --list`以列表方式查看系统给git的配置内容
- `git config --global --list`用户可以更改的配置条目
    - `git config --global user.name "carry"`
    - `git config --global user.email "1710845733@qq.com"`
    - `git config --global core.editor vim`修改git的默认编辑器

## git基本操作

### 添加、提交、查看状态
`git add file`追踪file文件
`git rm --cached file`停止追踪file文件
`git commit -m "description"`将暂存区的文件提交到本地库
`git status`查看文件状态
`git log`查看提交日志
`git log --pretty=online`查看提交日志(简洁)
`git log --online`查看提交日志(更简洁)
`git reflog`
`git reset --参数 索引号`记录跳转
参数hard表示工作区、暂存区同步改动
参数mixed表示只有工作区不跟随跳转同步改动
参数soft表示工作区、暂存区都不同步改动

### 分支
`git branch 分支名称`添加分支
`git checkout 分支`分支切换
`git merge demo`将demo分支合并到当前所处的分支上
`git branch -d 分支名称`删除分支(若分支还未合并到主分支需要用`-D`代替`-d`进行删除)
`git checkout -b 分支名称`创建分支并切换到新建的分支上
`git brach -M demo`创建一个demo分支并将该分支设为master分支

### 远端仓库
`git remote -v`查看本地仓库和哪些远程仓库有联系
`git remote add 远程地址别名 远程仓库地址`添加远程仓库地址并取别名
#### push
`git push -u 远端地址或别名 分支`如果您指定了-u选项，那么下一次推送时就可以省略分支名称了
`git config credencial.helper 模式`模式可选cache(内存-临时)、store(磁盘-永久)
`ssh-keygen -t rsa -C 邮箱地址`配置ssh秘钥
`git remote set-url --add origin git@git.coding.net:KeithNull/keithnull.github.io.git`一个别名推送两个地址
#### clone
`git clone <repository> <directory>`