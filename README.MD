[TOC]

# 0、[在github上查看](https://github.com/7723li/StdTest/blob/master/README.MD)

<img src = "http://www.ruanyifeng.com/blogimg/asset/2015/bg2015120901.png">

参考来源：[常用 Git 命令清单](http://www.ruanyifeng.com/blog/2015/12/git-cheat-sheet.html)

- Workspace：工作区

- Index / Stage：暂存区

- Repository：仓库区（或本地仓库）

- Remote：远程仓库

  

# 1、项目Git访问地址

问人



# 2、登录

问人



# 3、添加SSH秘钥

这个必须添加，不然无法正常使用git，参考[Windows下的ssh秘钥添加方法](https://blog.csdn.net/Suo_ivy/article/details/79940839)，链接中包含对git配置的操作



# 4、创建本地仓库

git init											   			 // 在合适的位置创建一个非中文的文件夹作为根目录

git clone [比如这样的项目地址]("https://github.com/7723li/-git-Windows.git") 目录名		// 复制整个完整的项目以及所有的代码历史到本地，并更改目录名



# 5、更新本地仓库

**在日常更新某些文件的时候，使用第1~3条就可以了**

**关于第4条，我的理解用于多人协作时，在本地增加一个别人正在编辑中的分支**

git fetch origin 分支名称										// 从远程获取某分支的最新版本到本地

git log -p aaa origin/分支名称								// 比较本地分支与远程分支的区别

git merge origin/分支名称									   // 合并到本地分支

git checkout -b 分支名称 origin/分支名称 -f		   // 在本地创建分支，并强制映射到远程分支，会改变本地文件

git fetch origin															// 从远程获取当前主机的所有更新

git remote prune origin // 同步被删除的远程分支



# 6、同步到远程服务器



## 添加特殊忽略文件

在根目录新建名称为.gitignore的文件，用于避免上传不必要的文件（比如.exe、.obj之类），具体方法看[git特殊忽略文件](https://www.liaoxuefeng.com/wiki/896043488029600/900004590234208)	或 [这里](https://github.com/7723li/-git-Windows/blob/dev/.gitignore)



## 查看暂存区状态

git status



## 添加到暂存区中

git add .										// 提交新增和修改的文件

git add -A								 	// 提交新增、修改和被删除的文件

git add 文件1 文件2...			 	// 添加指定文件

git add 文件夹						 	// 添加整个目录



## 撤销暂存区操作

git rm --cache 文件1 文件2		// 删除添加到暂存区的错误文件，之后手动修改或删除相关文件就可以了

git checkout 文件						// 恢复暂存区的指定文件到本地

git checkout .							   // 恢复暂存区的所有文件到本地



## 提交到本地仓库

git commit -m '一些描述'



## 撤销commit操作

git reset commit_id						// 回退到上一个提交的节点 代码不会改变 commit_id可以在项目界面找

**_commit错误的话，可以用reset指令，但是感觉不是很透彻，比较透彻的方法是先提交到远程，然后修改本地文件，再提交一次_**



## 添加远程仓库

git remote add 远程服务器名称 [比如这样的项目地址]("https://github.com/7723li/-git-Windows.git") 		// 远程服务器名称一般默认为origin



## 推送到远程仓库

git push 远程服务器名称 分支名称			// 初次合并的时候需要在push后面带上参数 -u																  

# 7、分支管理

## 查看分支

git branch 		// 查看本地所有分支

git branch -r 	// 查看所有远程分支

git branch -a 	// 查看所有本地与远程分支



## 创建分支

git branch 分支名称				 // 创建本地分支，分支名称最好使用



## 切换分支

git checkout 分支名称			  // 切换本地分支，并更新工作区

git checkout -b 分支名称		 // 创建本地分支并切换到该分支



## 推送本地分支到远程

git push origin 分支名称



## 合并分支

git merge 分支名称			 // 合并*__该分支__*到*__当前分支__*，所以**_必须先切换分支_**

git push origin 分支名称    // 合并后同步到远程分支，即相当于推送到远程仓库

​											  // 推送到远程仓库之后就可以删除本地和远程的_**多余**_分支了



## 删除分支

git branch -d 分支名称								// 删除本地分支

git push origin --delete 分支名称			   // 删除远程分支