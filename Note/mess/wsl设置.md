# ArchWSL设置

## 安装步骤

> https://wsldl-pg.github.io/ArchW-docs/How-to-Setup/

### appx安装方式:

1. 下载appx源文件和证书

2. 双击下载好的证书文件，安装到本地计算机->受信任的根证书颁发机构

3. 打开powershell，cd命令转到appx源文件所在路径，执行 `Add-AppPackage 源文件名`

4. 安装完成

5. 在wsl中执行`arch`

6. 输入`passwd`设置管理员密码

7. arch中执行：

   ```shell
   echo "%wheel ALL=(ALL) ALL" > /etc/sudoers.d/wheel
   useradd -m -G wheel -s /bin/bash carry
   passwd carry
   #ctrl+d退出arch
   ```

8. powershell中执行：

   ```shell
   Arch.exe config --default-user carry
   ```

9. 初始化keyring

   ```shell
   sudo pacman-key --init
   sudo pacman-key --populate
   sudo pacman -Syy archlinux-keyring
   ```

## 其他设置

### 设置桥接

- get-netadapter
- Set-VMSwitch WSL -NetAdapterName 以太网

### 恢复为NAT

- wsl --shutdown

- Set-VMSwitch WSL -SwitchType Internal
- 在网卡属性设置中，取消勾选`Hiper-V可扩展的虚拟交换机`选项

### 许可证无法使用时

- 在`/etc/pacman.conf`中把manjaro配置里的 `SigLevel = Optional TrustedOnly`改为`SigLevel = Optional TrustAll`，完整内容如下

```shell
[archlinuxcn]
SigLevel = Optional TrustAll
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/$arch
```

### wsl使用代理
- 脚本实现代理服务器
```shell
#在.bashrc脚本里写入
export host_ip=$(cat /etc/resolv.conf |grep "nameserver" |cut -f 2 -d " ")
alias proxy="export all_proxy=http://$host_ip:7890 http_proxy=http://$host_ip:7890 https_proxy=http://$host_ip:7890"
alias unproxy='unset all_proxy http_proxy https_proxy'
```

- 手动分配代理服务器
```shell
#在WSL的终端上输入vim ~/.bashrc，在末行写入
export http_proxy=127.0.0.1:7890
export https_proxy=127.0.0.1:7890
#注意这里的7890是上图Clash的HTTP代理端口号，请替换成自己本机的端口。
```
### 配置ssh
- 安装openssh
`sudo pacman -S openssh`

```shell
#配置/etc/ssh/sshd_config
Port 22
Address Family any
ListenAddress 0.0.0.0
PasswordAuthentication yes
```
`ssh-keygen -t ed25519 -C "xxxxx@xxxxx.com"`生成sshkey

### 设置开机的默认shell
在.bashrc中加入
`bash -c <your shell>`