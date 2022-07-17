# Manjaro KDE系统配置
[toc]
## 安装应用

- 换安装源（默认源在国外，下载速度慢）

  - `sudo pacman-mirrors -i -c China -m rank`，对国内镜像源测速并排序
  - ustc：中国科学技术大学
  - nju：南京大学
  - huaweicloud：华为云
  - pku：北京大学
  - sjtu：上海交通大学
  - tsinghua：清华大学
  - aliyun：阿里云

- 添加AUR(Arch User Repository)的源

  - `sudo nano /etc/pacman.conf`，编辑pacman的配置文件

  - 输入密码后在配置文件的末尾添加如下内容：

    ```shell
    [archlinuxcn]
    SigLevel = Optional TrustedOnly
    Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
    ```

  - `sudo pacman -Sy`，更新源(y)

  - `sudo pacman -S archlinuxcn-keyring`，安装archlinuxcn-keyring，被arch授权，授权后才能从arch上下载资源。

 - `sudo pacman -Su`，升级系统(u)
- 安装AUR包管理工具yay

  - `sudo pacman -S yay`，安装完后`yay`可以替代`sudo pacman`，而且`yay`可以模糊搜索。

- 安装ntpdate同步系统时间

  - `yay -S ntpdate`，manjaro kde不需要安装，系统自带
  - `sudo ntpdate time.windows.com`，检查弹出的时间是否正确，正确后进行下一步
  - `sudo hwclock --localtime --systohc`，更改时间机制
  - 完成修改

- 安装`neovim`编辑器

  - `sudo pacman -S neovim`

- 安装输入法

  - 谷歌拼音和搜狗拼音都是基于`fcitx`的，因此需要先安装fcitx家族的文件（以安装谷歌拼音为例）

    依次执行如下命令：

    ```shell
    yay -S fcitx-googlepinyin 或 fcitx-sogoupinyin
    yay -S fcitx-im	//安装过程会出现多个，直接Enter，全部安装
    yay -S fcitx-configtool
    ```

  - `sudo nvim ~/.xprofile`，将`fcitx`放入环境变量才能激活输入法，此操作是新建一个配置文件

  - 在打开的`.xprofile`中写入以下内容：

    ```shell
    export GTK_IM_MODULE=fcitx
    export QT_IM_MODULE=fcitx
    export XMODIFIERS="@im=fcitx"
    export XIM=fcitx
    export XIM_PROGRAM=fcitx
    ```

    保存文件，重启系统。

  - 若是安装sogou拼音，可能会出现不能输入中文的情况，那是因为缺少qt，在命令行输入

    ```shell
    yay -S fcitx-qt4
    ```

    安装即可，然后重启manjaro（使用reboot命令），则可以使用搜狗输入法了。

- 安装chrome浏览器
  - `sudo pacman -S google-chrome`

- 安装WPS(只能使用word，而且界面还不清晰，建议不要装)

  - ```shell
    sudo pacman -S wps-office
    sudo pacman -S wps-office-mui-zh-cn #安装中文
    sudo pacman -S ttf-wps-fonts # 安装依赖字体
    ```

- 安装VScode
  - `sudo pacman -S visual-studio-code-bin`

- 安装typora
  - `sudo pacman -S typora`

- 安装wechat

  - 主要有三种，`electronic-wechat`是网页版的，`deepin-wine-wechat`是真正电脑版的（模拟windows环境安装的），还有一个`wewechat`以`electronic-wechat`为例

    ```shell
    sudo pacman -S electronic-wechat
    ```

- 安装网易云音乐
  - `sudo pacman -S netease-cloud-music`


## 终端美化

- 安装zsh
  - `sudo pacman -S zsh`
- 安装oh-my-zsh
  - 可以从github上克隆到本地，`git clone http://链接`

## 配置NVIM编辑器

### 修改默认编辑器

  - ```
    echo export EDITOR=/usr/bin/nvim >> ~/.zshrc 
    ```

### vim-plug的安装

  - `git clone https://github.com/junegunn/vim-plug.git`，获取vim-plug

  - ```shell
    //vim
    mkdir -p  ~/.vim/autoload/
    cp plug.vim  ~/.vim/autoload/plug.vim
    
    //nvim
    mkdir -p ~/.config/nvim/autoload
    cp ~/vim-plug/plug.vim ~/.config/nvim/autoload/plug.vim
    ```
    
  - 创建配置文件`touch ~/.vimrc`for vim，`nvim ~/.config/nvim/init.vim`for nvim，添加如下命令

    ```
    call plug#begin()
    Plug 'XXXXXX'
    Plug 'XXXXXX'
    call plug#end()
    ```

    使用命令`:PlugInstall`即可安装插件`XXXXXX`，具体插件需上vimawsome上查找所需

### vim/nvim的强大配置文件(my vimrc  &  init.vim)
  - [nvim&vim配置文件](../../Code/etc/init.vim)---ctrl+鼠标左键点击查看

### vim自带的一些小功能
- `set spell`：设置拼写检查
  - normal模式下按`z=`可以对光标下的单词进行纠正选择
  - insert模式下依次按`ctrl+x s`，tab选择下一个,shift+tab选择上一个
- set list            "显示行尾符
- set nocompatible    "版本兼容设置
- set relativenumber  "设置相对行号
- set nu              "设置行号
- set showcmd         "i显示命令,如3dd
- set wildmenu        "显示命令行提示
- set noignorecase    "查找时忽略区分大小写
- "set smartcase      "查找时智能忽略大小写
- set nohlsearch      "查找不会高亮显示
- set wrap            "超出终端显示范围时,跳转到下一行
- set encoding=utf-8  "设置字符集为utf-8
- set laststatus=2    "在窗口底部显示一个永久状态栏,文件名+行列号
- set autochdir       "自动维护编辑的历史记录

### vim/nvim插件推荐
#### coc.nvim，超好用的自动补全插件

  - `yay nodejs`，选择安装nodejs,版本须>=12.12

  - `yay -S npm yarn`安装npm包裹管理器和yarn

    - 查看coc安装了哪些插件`:CocList extensions`
    - 安装coc插件`:CocInstall 插件名称`

  - 在`~/.vimrc`或`~/.config/nvim/init.vim`中添加vim-plug代码

    ```
    Plug 'neoclide/coc.nvim', {'branch': 'release'}
    ```

  - 运行命令`:checkhealth`，看到coc: health栏下有3个OK代表coc已正确安装。

#### MarkdownPreview
```vim
Plug 'iamcco/markdown-preview.nvim', { 'do': { -> mkdp#util#install() }, 'for': ['markdown', 'vim-plug']}

:source %
:PluginInstall
:call mkdp#util#install()   "需要等待一定的时间
"用nvim打开任意markdown文件,在nomal模式下按r即可用chromium打开markdwon预览

"功能介绍
autocmd Filetype markdown inoremap ,f <Esc>/<++><CR>:nohlsearch<CR>c4l"跳转到下一个pressHolder
autocmd Filetype markdown inoremap ,n ---<Enter><Enter>     "分隔符
autocmd Filetype markdown inoremap ,b **** <++><Esc>F*hi    "字体加粗
autocmd Filetype markdown inoremap ,s ~~~~ <++><Esc>F~hi    "删除线
autocmd Filetype markdown inoremap ,i ** <++><Esc>F*i       "斜体
autocmd Filetype markdown inoremap ,d `` <++><Esc>F`i       "代码块"
autocmd Filetype markdown inoremap ,c ```<Enter><++><Enter>```<Enter><Enter><++><Esc>4kA        "代码段
autocmd Filetype markdown inoremap ,h ====<Space><++><Esc>F=hi  "
autocmd Filetype markdown inoremap ,p ![](<++>) <++><Esc>F[a    "图片
autocmd Filetype markdown inoremap ,a [](<++>) <++><Esc>F[a     "超链接
autocmd Filetype markdown inoremap ,1 #<Space><Enter><++><Esc>kA    "一级
autocmd Filetype markdown inoremap ,2 ##<Space><Enter><++><Esc>kA   "二级
autocmd Filetype markdown inoremap ,3 ###<Space><Enter><++><Esc>kA  "三级
autocmd Filetype markdown inoremap ,4 ####<Space><Enter><++><Esc>kA "四级
autocmd Filetype markdown inoremap ,l --------<Enter>
```
### tagbar
```
" -------- general ----------
" <CR>: 回车跳到定义位置
" p: 跳到定义位置，但光标仍然在tagbar原位置
" P: 打开一个预览窗口显示标签内容，如果在标签处回车跳到vim编辑页面内定义处，则预览窗口关闭
" <C-N>: 跳到下一个标签页的顶端
" <C-P>:  跳到上一个（或当前）标签页的顶端
" <Space>: 底行显示标签原型
"
" ---------- Folds ----------
" + 展开标签内容
" -  折叠标签内容

" *  展开所有标签
" =  折叠所有标签
" o 在折叠与展开间切换，按o键，折叠标签，再按一次o，则展开标签，如此来回切换
"
" ---------- Misc -----------
" s: 切换排序，一次s，则让标签按字典排序，再一次s，则按照文件内出现顺序排序
" x: 是否展开tagbar标签栏，x展开，再一次x，则缩小标签栏
" <F1>: 切换快捷键帮助页面，F1一次出现快捷键帮助页面，在一次F1，快捷键帮助页面隐藏。
————————————————
版权声明：本文为CSDN博主「羁旅人间」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/yangqing99801/article/details/50729849k
```

### 文字图形化软件(figlet)
  - 安装:`sudo pacman -S figlet`
  - vim下的使用方法:`:r !figlet my vimrc`
    - `:r`：vim下可以使用该指令获取终端下的输出
    - `!` ：vim中使用终端命令的符号
    - 这串命令相当于在vim中运行了终端命令figlet my vimrc，将终端的输出结果写入到当前vim打开的文件里
    - ![](pic/Myvimrc.png)
- vim for VScode按键绑定文件路径：`C:\Users\Administrator\AppData\Roaming\Code\User\keybindings.json`

## 开启远程连接ssh服务
## ArchWSL配置ssh公钥认证
- 首先需要安装openssh`yay -S openssh`	//安装openssh

- 开启服务命令
  - `sudo systemctl start sshd.service`

- 设置ssh开机自启动
  - `sudo systemctl enable sshd.service`

- 如果出现问题，可以重启服务
  - `sudo systemctl restart sshd.service`

## 解决共享文件夹消失问题

- 首先，确认vmtools已经安装,并且共享文件夹已经开启

- sudo nvim etc/fstab文件，在末尾处加入如下命令

  ```
  .host:/ /mnt/hgfs fuse.vmhgfs-fuse allow_other,uid=1000,gid=1000,umask=022 0 0
  ```

- 重启或执行`source /etc/fstab`

## 解决VM客户机自适应窗口的问题

卸载open-vm-tools 

```
sudo pacman -R open-vm-tools
```

 下载vmwaretools补丁

```
git clone https://github.com/rasa/vmware-tools-patches.git
```

进入vmware-tools-patches目录

```
cd vmware-tools-patches
```

运行补丁（可能需要多次尝试才可以）

```
sudo ./patched-open-vm-tools.sh
```

`reboot`重启manjaro，显示分辨率正常。

## 安装ttf字体

- 将ttf文件拷贝到`/usr/share/fonts/TTF`

## GitHub520 Host Start
185.199.108.154               github.githubassets.com
140.82.113.22                 central.github.com
185.199.108.133               desktop.githubusercontent.com
185.199.108.153               assets-cdn.github.com
185.199.108.133               camo.githubusercontent.com
185.199.108.133               github.map.fastly.net
199.232.69.194                github.global.ssl.fastly.net
140.82.113.3                  gist.github.com
185.199.108.153               github.io
140.82.114.4                  github.com
140.82.112.6                  api.github.com
185.199.108.133               raw.githubusercontent.com
185.199.108.133               user-images.githubusercontent.com
185.199.108.133               favicons.githubusercontent.com
185.199.108.133               avatars5.githubusercontent.com
185.199.108.133               avatars4.githubusercontent.com
185.199.108.133               avatars3.githubusercontent.com
185.199.108.133               avatars2.githubusercontent.com
185.199.108.133               avatars1.githubusercontent.com
185.199.108.133               avatars0.githubusercontent.com
185.199.108.133               avatars.githubusercontent.com
140.82.113.9                  codeload.github.com
52.217.88.28                  github-cloud.s3.amazonaws.com
52.216.238.99                 github-com.s3.amazonaws.com
52.216.26.252                 github-production-release-asset-2e65be.s3.amazonaws.com
52.217.101.68                 github-production-user-asset-6210df.s3.amazonaws.com
52.217.48.84                  github-production-repository-file-5c1aeb.s3.amazonaws.com
185.199.108.153               githubstatus.com
64.71.168.201                 github.community
185.199.108.133               media.githubusercontent.com

Update time: 2021-03-16T12:24:16+08:00

Star me GitHub url: https://github.com/521xueweihan/GitHub520

GitHub520 Host End
