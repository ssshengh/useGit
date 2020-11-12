//创建git版本库
$ mkdir git
$ cd git
$ git init

//将文件添加进入git仓库
//随便写一个txt，
$ git add XXX.txt
//没有消息就说明OK了
$ git commit -m "wrote a readme file"
//git commit 指令 -m是本次提交的说明 添加文件需要两步，因为可以提交很多文件
//eg：
$ git add f1.txt f2.txt f2.txt
$ git commit -m "add 3 files "

 
 
//查看修改
$ git status  //可以告诉我们什么被修改过了，掌握仓库状态
$ git diff [filename] //可以查看详细修改了什么内容   加通道或者输出重定向
//完成查看后，就可以提交到仓库，同样的执行上两步

//查看修改过的版本
$ git log
$ git log --pretty=oneline//十六进制显示版本号


//回退到上个版本
$ git reset --hard HEAD^ //HEAD^上个版本 HEAD^^上上个版本。。。 HEAD~100 100 个版本前


//回退到上个版本后log里会失去原本的版本信息，恢复的化，就只能系希望与习惯性打开log了
//通过原本的shell中log的版本号可以又找到因为回退消失的版本，速度很快，因为有个指针指向当前的HEAD
//回退只是把指针移位，并未删除
$ git reset --hard 1094a //尽量多写几位


//概念很重要，看另一个文件


//追踪修改
//git之所以优秀就因为它管理的是修改而不是文件
//如果修改了一次之后就add，然后再进行修改，进行commit，可以看见第二次修改的并没有被添加上去，因为暂存区里并没有这个修改，
$ git diff HEAD --readme.txt 查看第一次工作区和版本库里的差别
/*****************************************************************************************
shenheng@shenheng-QiTianM410-N000:~/git$ git diff HEAD -- readme.txt
diff --git a/readme.txt b/readme.txt
index 8113c28..b125083 100644
--- a/readme.txt
+++ b/readme.txt
@@ -41,7 +41,7 @@ $ git reset --hard 1094a //尽量多写几位
 //追踪修改
 //git之所以优秀就因为它管理的是修改而不是文件
 //如果修改了一次之后就add，然后再进行修改，进行commit，可以看见第二次修改的并没有被添加上去，因为暂存区里并没有这个修改，
-$ git diff HEAD --readme.txt 查看
+$ git diff HEAD --readme.txt 查看第一次工作区和版本库里的差别
******************************************************************************************/

可以看见工作区里还保存着修改，二次add就好了



//自然，有时候希望撤销修改，比如写了个stupied boss
//如果这份修改还没有add，还在工作区里，那么可以
$ git checkout -- readme.txt //丢弃所有工作区中的修改，一定要加-- 不然就是切换分支

//会出现两种情况
//还没有放入暂存区（add），那么就会回到和版本库一模一样的状态
//已经添加到了暂存区，，将撤销修改回到添加到暂区前的模样


//另一种是，说了胡话，且add到了暂存区，庆幸的是，用status查看了一下，还可以这么稿：
$ git reset HEAD <file> //将暂存区的修改撤销重放回工作区
//git reset 可以回退版本，也可以把暂存区的修改回退到工作区，HEAD表示最新版本


//删除文件
//一般来说我们删除文件就直接 rm file
//但是在工作区中删除文件就不一样了，如果我们将其提交到了版本库
$ rm tet.txt   //我们删除了文件，但是版本库里还有
$ git status   //可以看见删除了哪个文件

//如果确实要删除,并且提交
$ git rm tet.txt                 //在这里都还有机会恢复，先reset，再checkout
$ git commit -m "remove tet.txt" 

//后悔了，就这么找回版本里的
$ git checkout -- tet.txt
//注意就是，一定要提交到版本库的才可以这么干




