#include <stdio.h>
#include <stdlib.h>

/*チェスの最初の並び*/
void Init(int boad[8][8]){
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(i==1){
                boad[i][j]=1;
            }else if(i==6){
                boad[i][j]=-1;
            }else if(i==0&&(j==0||j==7)){
                boad[i][j]=2;
            }else if(i==0&&(j==1||j==6)){
                boad[i][j]=3;
            }else if(i==0&&(j==2||j==5)){
                boad[i][j]=4;
            }else if(i==0&&j==3){
                boad[i][j]=5;
            }else if(i==0&&j==4){
                boad[i][j]=6;
            }else if(i==7&&(j==0||j==7)){
                boad[i][j]=-2;
            }else if(i==7&&(j==1||j==6)){
                boad[i][j]=-3;
            }else if(i==7&&(j==2||j==5)){
                boad[i][j]=-4;
            }else if(i==7&&j==3){
                boad[i][j]=-5;
            }else if(i==7&&j==4){
                boad[i][j]=-6;
            }else
                boad[i][j]=0;
        }
    }
}

/*勝ち負け判定*/
int judgement(int boad[8][8]){
    int win=0,win_2=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(boad[i][j]==6)
                win=1;
            else if(boad[i][j]==-6)
                win_2=1;
        }
    }
    if(win==1&&win_2==1)
        return 1;
    else if(win==1&&win_2==0){
        printf("ダッシュなしの勝ち\n");
        return 2;
    }
    else if(win==0&&win_2==1){
        printf("ダッシュありの勝ち\n");
        return 3;
    }
    else
        return 0;
}

/*周囲が味方に囲まれていて、動けない場合の判定*/
int search_surround(int boad[8][8],int player,int x,int y){
    int i=0,j=0;
    
    
    if(player==1&&boad[x][y]<=0)
        return 1;
    if(player==-1&&boad[x][y]>=0)
        return 1;
    if(boad[x][y]==player*3)
        return 0;
    
    if(boad[x][y]==player*1){
        if(player==1&&(boad[x+1][y+1]<0||boad[x+1][y-1]<0))
            return 0;
        if(player==-1&&(boad[x-1][y-1]>0||boad[x-1][y+1]>0))
            return 0;
        if(player==1&&boad[x+1][y]==0)
            return 0;
        if(player==-1&&boad[x-1][y]==0)
            return 0;
        if(player==1&&boad[x+1][y]!=0)
            return 1;
        if(player==-1&&boad[x-1][y]!=0)
            return 1;
    }
    
    for(i=-1;i<2;i++){
        for(j=-1;j<2;j++){
            if(i==0&&j==0)
                continue;
            if(x+i<0||x+i>7||y+j<0||y+j>7){
                continue;
            }
            if(boad[x][y]==player*5||boad[x][y]==player*6){
                if(boad[x+i][y+j]<=0&&player==1)
                    return 0;
                if(boad[x+i][y+j]>=0&&player==-1)
                    return 0;
            }
            if(boad[x][y]==player*4&&(i==j||i==-j||j==-i)){
                if(boad[x+i][y+j]<=0&&player==1)
                    return 0;
                if(boad[x+i][y+j]>=0&&player==-1)
                    return 0;
            }
            if(boad[x][y]==player*2&&(i!=0&&j==0)||i==0&&j!=0){
                if(boad[x+i][y+j]<=0&&player==1)
                    return 0;
                if(boad[x+i][y+j]>=0&&player==-1)
                    return 0;
            }
        }
    }

    return 1;
}

/*動くところに味方のコマまたは敵のコマがないかどうかを判定する*/
int move_judge(int boad[8][8],int player,int x,int y,int s,int t){
    int j=0;
    int k=0;
    int m=0,n=0;
    m=s-x;
    n=t-y;
    
    if(m<0&&n==0){
        for(int i=-1;i>m;i--){
            if(boad[x+i][y]!=0)
                return 0;
        }
    }
    
    if(m>0&&n==0){
        for(int i=1;i<m;i++){
            if(boad[x+i][y]!=0)
                return 0;
        }
    }
    
    if(m==0&&n<0){
        for(int i=-1;i>n;i--){
            if(boad[x][y+i]!=0)
                return 0;
        }
    }
    
    if(m==0&&n>0){
        for(int i=1;i<n;i++){
            if(boad[x][y+i]!=0)
                return 0;
        }
    }
    
    if(m==n&&m<0&&n<0){
        j=-1;
        k=-1;
        while(j>=m&&k>n){
            if(boad[x+j][y+k]!=0)
                return 0;
            j--;
            k--;
        }
    }
    
    if(m==n&&m>0&&n>0){
        j=1;
        k=1;
        while(j<m&&k<n){
            if(boad[x+j][y+k]!=0)
                return 0;
            j++;
            k++;
        }
    }
    
    
    if(n==-m){
        j=-1;
        k=1;
        while(j>m&&k<n){
            if(boad[x+j][y+k]!=0)
                return 0;
            j--;
            k++;
        }
    }
    
    if(m==-n){
        j=1;
        k=-1;
        while(j<m&&k>n){
            if(boad[x+j][y+k]!=0)
                return 0;
            j++;
            k--;
        }
    }
    
    return 1;
}

/*ポーンの動きの定義*/
int def_P(int boad[8][8],int player,int x,int y,int s,int t){
    int m=0;
    int n=0;
    m=s-x;
    n=t-y;
    
    if(m<0)
        m=x-s;
    if(n<0)
        n=y-t;
    
        
    if(x>1&&x<6){
        if((m==1&&n==0)&&boad[s][t]==0)
            return 0;
    }
    if((x==1&&player==1)||(x==6&&player==-1)){
        if(m<=2&&n==0&&move_judge(boad,player,x,y,s,t)){
            return 0;
        }
    }
    
    if(player==1&&m==1&&n==1&&boad[s][t]<0)
        return 0;
    
    if(player==-1&&m==1&&n==1&&boad[s][t]>0)
        return 0;
    
    return 1;
}

/*ルークの動きの定義*/
int def_R(int boad[8][8],int player,int x,int y,int s,int t){
    int m=s-x,n=t-y;
    if((m!=0&&n==0||m==0&&n!=0)&&move_judge(boad,player,x,y,s,t))
        return 0;
    
    return 1;
}

/*ビショップの動きの定義*/
int def_B(int boad[8][8],int player,int x,int y,int s,int t){
    int m=0,n=0;
    m=s-x;
    n=t-y;
    
    if((m==n||m==-n||n==-m)&&move_judge(boad,player,x,y,s,t)&&n!=0&&m!=0)
        return 0;
    
    return 1;
}

/*クイーンの動きの定義*/
int def_Q(int boad[8][8],int player,int x,int y,int s,int t){
    
    int m=0,n=0;
    m=s-x;
    n=t-y;
    
    if((m!=0&&n==0||m==0&&n!=0)&&move_judge(boad,player,x,y,s,t))
        return 0;
    if((m==n||m==-n||n==-m)&&move_judge(boad,player,x,y,s,t)&&n!=0&&m!=0)
        return 0;
    
    return 1;
}

/*キングの動きの定義*/
int def_K(int boad[8][8],int player,int x,int y,int s,int t){
    int m=s-x,m_1=t-y;
    if(m_1<0)
        m_1=y-t;
    if(m<0)
        m=x-s;
    if((m==1&&m_1==0)||(m_1==1&&m==1)){
        if(player==-1&&boad[s][t]>=0)
            return 0;
        if(player==1&&boad[s][t]<=0)
            return 0;
    }
    
    return 1;
}

/*ナイトの動きの定義*/
int def_N(int boad[8][8],int player,int x,int y,int s,int t){
    int m=s-x,m_1=t-y;
    if(m_1<0)
        m_1=-(t-y);
    if(m<0)
        m=-(s-x);
    if(((m==2&&m_1==1)||(m==1&&m_1==2))&&player==1&&boad[s][t]<=0)
        return 0;
    if(((m==2&&m_1==1)||(m==1&&m_1==2))&&player==-1&&boad[s][t]>=0)
        return 0;
    
    return 1;
}

/*さまざまなコマの動きの定義を集めたもの*/
int action(int boad[8][8],int player,int x,int y,int s,int t){
    
    if((player==1&&boad[s][t]>0)||(player==-1&&boad[s][t]<0))
        return 1;
    if(boad[x][y]==1*player)
        return def_P(boad,player,x,y,s,t);
    if(boad[x][y]==2*player)
        return def_R(boad,player,x,y,s,t);
    if(boad[x][y]==3*player)
        return def_N(boad,player,x,y,s,t);
    if(boad[x][y]==4*player)
        return def_B(boad,player,x,y,s,t);
    if(boad[x][y]==5*player)
        return def_Q(boad,player,x,y,s,t);
    if(boad[x][y]==6*player)
        return def_K(boad,player,x,y,s,t);
    
    return 0;
}

void disp_c(int boad[8][8],int x,int y){
    system("cls");
    printf("  0 1 2 3 4 5 6 7\n");
    for(int i=0;i<8;i++){
        if(i==x+1)
            printf("\x1b[0m");
        printf("%d ",i);
        for(int j=0;j<8;j++){
            if(i==x&&j==y)
                printf("\x1b[31m");
            if(j==y+1)
                printf("\x1b[0m");
            if(boad[i][j]==0)
                printf(". ");
            else if(boad[i][j]==1)
                printf("P ");
            else if(boad[i][j]==2)
                printf("R ");
            else if(boad[i][j]==3)
                printf("N ");
            else if(boad[i][j]==4)
                printf("B ");
            else if(boad[i][j]==5)
                printf("Q ");
            else if(boad[i][j]==6)
                printf("K ");
            else if(boad[i][j]==-1)
                printf("P'");
            else if(boad[i][j]==-2)
                printf("R'");
            else if(boad[i][j]==-3)
                printf("N'");
            else if(boad[i][j]==-4)
                printf("B'");
            else if(boad[i][j]==-5)
                printf("Q'");
            else if(boad[i][j]==-6)
                printf("K'");
        }
        printf("\n");
        printf("\x1b[0m");
    }
}

/*動けるかどうかを判定し、コマを実際に動かす*/
void move_area(int boad[8][8],int player,int x,int y){
    int s,t;
    if(player==1){
        do{
            printf("どのマスへ進ませますか。\n");
            printf("y座標は?\n");
            scanf("%d",&s);
            printf("x座標は?\n");
            scanf("%d",&t);
        }while(action(boad,player,x,y,s,t));
        boad[s][t]=boad[x][y];
        boad[x][y]=0;
        if(s==7&&boad[s][t]==1)
            boad[s][t]=5;
    }
    if(player==-1){
        do{
            printf("どのマスへ進ませますか。\n");
            printf("y座標は?\n");
            scanf("%d",&s);
            printf("x座標は?\n");
            scanf("%d",&t);
        }while(action(boad,player,x,y,s,t));
        boad[s][t]=boad[x][y];
        boad[x][y]=0;
        if(s==0&&boad[s][t]==-1)
            boad[s][t]=-5;
    }
}

/*動かしたいこまの指定*/
void move_target(int boad[8][8],int player){
    int x;
    int y;
    
    if(player==1){
        do{
            printf("ダッシュなしの番です。\n");
            printf("動かしたいコマの座標を入力してください。\n");
            printf("y座標は?\n");
            scanf("%d",&x);
            printf("x座標は?\n");
            scanf("%d",&y);
        }while(search_surround(boad,player,x,y));
        disp_c(boad,x,y);
        move_area(boad,player,x,y);
    }
    if(player==-1){
        do{
            printf("ダッシュの番です。\n");
            printf("動かしたいコマの座標を入力してください。\n");
            printf("y座標は?\n");
            scanf("%d",&x);
            printf("x座標は?\n");
            scanf("%d",&y);
        }while(search_surround(boad,player,x,y));
        disp_c(boad,x,y);
        move_area(boad,player,x,y);
    }
}
/*表示の設定*/
void disp(int boad[8][8]){
    system("cls");
    printf("  0 1 2 3 4 5 6 7\n");
    for(int i=0;i<8;i++){
        printf("%d ",i);
        for(int j=0;j<8;j++){
            if(boad[i][j]==0)
                printf(". ");
            else if(boad[i][j]==1)
                printf("P ");
            else if(boad[i][j]==2)
                printf("R ");
            else if(boad[i][j]==3)
                printf("N ");
            else if(boad[i][j]==4)
                printf("B ");
            else if(boad[i][j]==5)
                printf("Q ");
            else if(boad[i][j]==6)
                printf("K ");
            else if(boad[i][j]==-1)
                printf("P'");
            else if(boad[i][j]==-2)
                printf("R'");
            else if(boad[i][j]==-3)
                printf("N'");
            else if(boad[i][j]==-4)
                printf("B'");
            else if(boad[i][j]==-5)
                printf("Q'");
            else if(boad[i][j]==-6)
                printf("K'");
        }
        printf("\n");
    }
}
    
   
int main(void){
    int boad[8][8];
    int i=0;
    int player=-1;

    system("chcp 65001");
    Init(boad);
    disp(boad);
    
    while(judgement(boad)==1){
        player=-player;
        move_target(boad,player);
        disp(boad);
    }
    
    return 0;
}
