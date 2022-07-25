#include <langinfo.h>
#include <locale.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#include "users.h"
#include "coms.h"
#include "ipmsg.h"
#include "send_receive.h"
#include "utils.h"


extern void destroyer(void);

void* interacter(void* option)
{
  char com[20], *fileName;
  int count;

  while(1)
  {
    //输入指令
    printf("\n(ipmsg):");
    fgets(com, sizeof(com), stdin);

    //去掉com数组中前后的空格
    transfStr(com, 1); 

    //查看当前在线用户
    if (!strcmp(com, "list") ||
        !strcmp(com, "ls"))
    {
      pthread_mutex_lock(&usrMutex);
      count = listUsers(NULL, &userList, 2, 1);
      pthread_mutex_unlock(&usrMutex);
    }

    //退出
    else if (!strcmp(com, "quit") ||
             !strcmp(com, "q"))
    {
      logout();
      destroyer();
      exit(0);
    }
	//刷新
    else if (!strcmp(com, "refresh") ||
             !strcmp(com, "rf"))
    {
      login();
      pthread_mutex_lock(&usrMutex);
      count = listUsers(NULL, &userList, 2, 1);
      pthread_mutex_unlock(&usrMutex);
    }
    //发送字符串
    else if (!strcmp(com, "talk") ||
             !strcmp(com, "tk"))
    {
      saySth();
    }
    //发送文件
    else if (!strcmp(com, "sendfile") ||
             !strcmp(com, "sf"))
    {
      selectFiles();//发送文件
    }
    //接收文件
    else if (!strcmp(com, "getfile") ||
             !strcmp(com, "gf"))
    {
      recvFiles();//接收文件
    }
    //暂停发送
    else if (!strcmp(com, "ceaseSend") ||
             !strcmp(com, "cs"))
    {
      ceaseSend();
    }
    //获取帮助
    else if (!strcmp(com, "help") ||
             !strcmp(com, "h"))
      printf(IMHELP);
  }

}



void* receiver(void *option)
{
  command *peercom;
  struct sockaddr_in peer;
  int mSock = *(int*)option, len;
  char buf[COMLEN];
  
  while(1)
  {
    //UDP接收数据，存入到buf中，peer会保存发送方的网络结构体
    if (recvfrom(mSock, buf, sizeof(buf), 0, (struct sockaddr*)&peer, &len)<0)
      continue;

	//申请一个command的结构体内存
    peercom = (command*)malloc(sizeof(command));
    bzero(peercom, sizeof(command));

	printf("recvbuf:[%s]\n",buf);

    //分割buf字符串，分别把 version，packetNo，senderName，senderHost，commandNo分割出来
    msgParser(buf, sizeof(buf), peercom);

    //用发送方的网络结构体覆盖掉 peercom中的网络结构体
    memcpy(&peercom->peer, &peer, sizeof(peercom->peer));

    //P操作 -1
    sem_wait(&waitNonFull);
    pthread_mutex_lock(&msgMutex);

    //把command结构体保存到队列mlist中
    mList.comTail->next = peercom;
    mList.comTail = peercom;

    //V操作 +1
    sem_post(&waitNonEmpty); 
    pthread_mutex_unlock(&msgMutex);
  }
}


void* processor(void *option)
{
  command *peercom, com;
  int comMode, comOpt, temp;
  int len;
  user *cur;
  filenode *head, *curFile;
  gsNode *preSend, *curSend, *curGet, *preGet;

  initCommand(&com, IPMSG_NOOPERATION);
  while(1)
  {
    sem_wait(&waitNonEmpty);//对信号量进行-1操作
    pthread_mutex_lock(&msgMutex);//加锁

    //从队列mlist里面取一个节点
    peercom = mList.comHead.next;
    mList.comHead.next = mList.comHead.next->next;

    if (mList.comHead.next == NULL)
      mList.comTail = &mList.comHead;


    sem_post(&waitNonFull); 
    pthread_mutex_unlock(&msgMutex);
    
    memcpy(&com.peer, &peercom->peer, sizeof(com.peer));

    comMode = GET_MODE(peercom->commandNo);//取低8位
    comOpt = GET_OPT(peercom->commandNo); //取高24位

    if (comOpt & IPMSG_SENDCHECKOPT)
    {
      com.packetNo = (unsigned int)time(NULL);

      snprintf(com.additional, MSGLEN, "%d", peercom->packetNo);
      com.commandNo = IPMSG_RECVMSG;
	  
      sendMsg(&com); 
    }
	
    switch (comMode)
    {
    
      case IPMSG_SENDMSG://消息传送
      if (strlen(peercom->additional)>0)
      {
        printf("\nGet message from: %s(%s)\n", peercom->senderName, peercom->senderHost);
        puts(peercom->additional);
      }

      if (comOpt & IPMSG_FILEATTACHOPT)//文件附件选项
      {
        printf("\nGet Files from: %s(%s).\nInput \"getfile(gf)\" to download.\n",
               peercom->senderName, peercom->senderHost);

		curGet = (gsNode*)malloc(sizeof(gsNode));
        initGsNode(curGet);
        memcpy(&curGet->peer, &peercom->peer, sizeof(curGet->peer));
        curGet->packetNo = peercom->packetNo;
        curGet->fileList.next = peercom->fileList;
        peercom->fileList = NULL;

        curGet= &getFHead;
        pthread_mutex_lock(&getFMutex);
        while ((curGet->next!=NULL) &&
               (curGet->next->packetNo!=curGet->packetNo))
          curGet= curGet->next;
        
        if (preGet->next==NULL)
          preGet->next = curGet;
        
        pthread_mutex_unlock(&getFMutex);
      }
      
      break;

	  
	case IPMSG_ANSENTRY://通报新上线
	cur = (user*)malloc(sizeof(user));
	memcpy(&cur->peer, &peercom->peer, sizeof(cur->peer));
	strncpy(cur->name, peercom->senderName, NAMELEN);
	strncpy(cur->host, peercom->senderHost, NAMELEN);
	strncpy(cur->nickname, peercom->additional, NAMELEN);
	cur->inUse = 0;
	cur->exit = 0;
	cur->next = NULL;
	pthread_mutex_lock(&usrMutex); 
	if (insertUser(&userList, cur)<0)
	free(cur);
	pthread_mutex_unlock(&usrMutex); 
	break;


	case IPMSG_BR_ENTRY://接收到广播
	com.packetNo = (unsigned int)time(NULL);//赋值包号
	com.commandNo = IPMSG_ANSENTRY;//赋值命令码
	strncpy(com.additional, pwd->pw_name, MSGLEN);//赋值内容
	sendMsg(&com);

	cur = (user*)malloc(sizeof(user));
	memcpy(&cur->peer, &peercom->peer, sizeof(cur->peer));
	strncpy(cur->name, peercom->senderName, NAMELEN);
	strncpy(cur->host, peercom->senderHost, NAMELEN);
	strncpy(cur->nickname, peercom->additional, NAMELEN);
	cur->inUse = 0;
	cur->exit = 0;
	cur->next = NULL;
	pthread_mutex_lock(&usrMutex);
	if (insertUser(&userList, cur)<0)
	free(cur);
	pthread_mutex_unlock(&usrMutex);
	break;


	case IPMSG_RECVMSG://　接收消息确认
	break;

	case IPMSG_RELEASEFILES://丢弃（取消）附件文件的接收
	preSend = &sendFHead;
	pthread_mutex_lock(&sendFMutex);
	curSend = sendFHead.next;
	while ((curSend!=NULL)&&(curSend->packetNo!=atoi(peercom->additional)))
	{
	preSend = preSend->next;
	curSend = curSend->next;
	}

	if (curSend!=NULL)
	{
	curSend->cancelled = 1;
	if (curSend->tcpSock>0)
	  shutdown(curSend->tcpSock, SHUT_RDWR);
	}
	pthread_mutex_unlock(&sendFMutex);
	break;


	case IPMSG_BR_EXIT://下线
      pthread_mutex_lock(&usrMutex);
      delUser(&userList, peercom);
      pthread_mutex_unlock(&usrMutex);
      break;

	  
    case IPMSG_NOOPERATION://没有任何操作
      break;

	  
    default:
      printf("\nno handle, %#x\n", peercom->commandNo);
      break;
    }
	
    deCommand(peercom);
    free(peercom);
    peercom = NULL;
  }
  
}





void destroyer()
{
  gsNode *preSend, *curSend, *preGet, *curGet;
  filenode *curFile;
  user *curUsr, *preUsr;
  
  preSend = &sendFHead;
  pthread_mutex_lock(&sendFMutex);
  curSend = sendFHead.next;
  while (curSend!=NULL)
  {
    if ((curSend->cancelled == 1) && (curSend->transferring==0))
    {
      preSend->next = curSend->next;
      deGsNode(curSend);
      free(curSend);
    }
    else preSend = preSend->next;
    
    curSend = preSend->next;
  }
  pthread_mutex_unlock(&sendFMutex);
  
  
  preGet = &getFHead;
  pthread_mutex_lock(&getFMutex);
  curGet = getFHead.next;
  while (curGet!=NULL)
  {
    if ((curGet->cancelled==1) &&(curGet->transferring==0))
    {
      preGet->next = curGet->next;
      deGsNode(curGet);
      free(curGet);
    }
    else preGet = preGet->next;
    
    curGet = preGet->next;
  }
  pthread_mutex_unlock(&getFMutex);

  preUsr = &userList;
  pthread_mutex_lock(&usrMutex);
  curUsr = userList.next;
  while (curUsr!=NULL)
  {
    if ((curUsr->exit==1) && (curUsr->inUse==0))
    {
      preUsr->next = curUsr->next;
      free(curUsr);
    }
    else preUsr = preUsr->next;
    
    curUsr = preUsr->next;
    
  }
  pthread_mutex_unlock(&usrMutex);
}



void* cleaner(void *option)
{
  gsNode *preSend, *curSend, *preGet, *curGet;
  filenode *curFile;
  user *curUsr, *preUsr;
  
  while(1)
  {
    sleep(30);
    destroyer();
  }
  
}


int initSvr(void)
{
  struct sockaddr_in server;
  char targetHost[NAMELEN];
  const int on=1;

  msgSock = socket(AF_INET, SOCK_DGRAM, 0);  //UDP for Msg
  
  tcpSock = socket(AF_INET, SOCK_STREAM, 0); //TCP for File
  
  server.sin_family = AF_INET;
  server.sin_port = htons(IPMSG_DEFAULT_PORT);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  //设置UDP广播属性
  if (setsockopt(msgSock, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on))<0)
  {
    printf("initSvr: Socket options set error.\n");
    exit(1);
  }

  //绑定UDP套接字
  if (bind(msgSock, (struct sockaddr*)&server, sizeof(server))<0)
  {
    printf("initSvr: Udp socket bind error.\n");
    exit(1);
  }

  //设置TCP的地址可重用属性
  int on1 = 1;
  setsockopt(tcpSock, SOL_SOCKET, SO_REUSEADDR, &on1, sizeof on1);

  //绑定tcp
  if (bind(tcpSock, (struct sockaddr*)&server, sizeof(server))<0)
  {
    printf("initSvr: Tcp socket bind error.\n");
    exit(1);
  }

  //监听
  if (listen(tcpSock, 10)<0)
  {
    printf("initSvr: Tcp listen error.\n");
    exit(1);
  }

  
  printf(IMHELP);
  return 0;
}



int main (int argc, char *argv [])
{

  pthread_t procer, recver, iter, fler, cler;
  int *fSock;
  int tmp;
  pthread_attr_t attr;
  
  uname(&sysName);//获取系统名称
  pwd = getpwuid(getuid()); //获取用户信息
  getcwd(workDir, sizeof(workDir));//获取当前用户工作路径


  //如果当前源代码时UTF-8编码,那么变量utf8=1，否则=0 
  utf8 = 0;
  if (setlocale(LC_CTYPE, ""))
    if (!strcmp(nl_langinfo(CODESET), "UTF-8"))
      utf8 = 1;


  //对结构体初始化
  initGsNode(&sendFHead);//初始化结构体
  initCommand(&mList.comHead, IPMSG_NOOPERATION);
  mList.comTail = &mList.comHead;
  userList.next = NULL;

  //信号量初始化
  sem_init(&waitNonEmpty, 0, 0);
  sem_init(&waitNonFull, 0, MSGLIMIT);

  //初始化UDP和TCP
  initSvr();

  //创建线程
  pthread_create(&procer, NULL, &processor, &msgSock); 
  pthread_create(&recver, NULL, &receiver, &msgSock);
  pthread_create(&iter, NULL, &interacter, NULL);
  pthread_create(&cler, NULL, &cleaner, NULL);


  login();

  //设置分离属性
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

  //接收tcp客户端的连接请求
  while(1)
  {
    if ((tmp=accept(tcpSock, NULL, NULL))<0)
      printf("Tcp accept error.\n");
    else
    {
      fSock = (int *)malloc(sizeof(int));
      *fSock = tmp;
      pthread_create(&fler, &attr, &sendData, fSock);//发送数据线程---发送文件
    }
    
  }

  pthread_join(procer, NULL);
  pthread_join(recver, NULL);
  pthread_join(iter, NULL);
  pthread_join(cler, NULL);
  return 0;
}

