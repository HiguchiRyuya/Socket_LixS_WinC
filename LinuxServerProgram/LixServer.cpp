#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <memory.h>

#define SERVER_PORT 11110
#define BUFSIZE 1024

int main()
{

    int socfd;                    // サーバー側のソケット
    int client_soc;             // クライアント側のソケット
    struct sockaddr_in addr;    // アドレスを入れる箱

    FILE* fp;

    socklen_t len = sizeof(struct sockaddr_in);
    struct sockaddr_in from_addr;

    char buf[BUFSIZE];

    // 受信バッファ初期化
    memset(buf,0,sizeof(buf));

    // ソケット生成
    if((socfd = socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        perror("socket");
    }

    // 待ち受け用IP・ポート番号設定
    //アドレスファミリ IPV4
    // ポート番号  11110
    addr.sin_family = AF_INET;
    addr.sin_port =  htons(SERVER_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    // バインド
    if(bind(socfd,(struct sockaddr *)&addr,sizeof(addr)) < 0)
    {
        perror("bind");
    }

    // 受信待ち
    // listen(接続待ちソケット,バックログ（接続を待機させる最大数）)
    if(listen(socfd,SOMAXCONN) < 0)
    {
        perror("listen");
    }


    // 受信
    int rsize;
    while(1)
    {
	  // クライアントからのコネクト要求待ち  
    	if((client_soc = accept(socfd,(struct sockaddr*)&from_addr,&len)) < 0)
    	{
        perror("accept");
        }
       // rsize = recv(client_soc,buf,sizeof(buf),0);

    while(rsize = read(client_soc ,buf , sizeof(buf)) > 0 )
    {
        fp = fopen("ScoreData.txt","a");

        if(fp == NULL)
        {
            perror("ファイルの読み込みに失敗\n");
            return -1;
        }
    

    fprintf(fp,"%s",buf);
    fclose(fp);

        //Send the message back to client
        write(client_soc , buf , strlen(buf));
        memset( &buf, 0, sizeof(buf));
    }

    if(rsize == 0)
    {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(rsize == -1)
    {
        perror("recv failed");
    }

    }

    // ソケットクローズ
    close(client_soc);
    close(socfd);

    return 0;
}


