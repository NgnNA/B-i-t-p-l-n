#include<iostream>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<iomanip>
#include <time.h>

using namespace std;

char table[10][10];
char table_mine_positions[10][10];
char symbol;
int mines_flagged_counter=0;
int flag_counter=0;
time_t time_since_start = time(0);
time_t game_time;

void show_content(int, int);
void create_mine_positions();
void increase_values();
void create_table();
void open_cell();
void game();
void print_table(char);
bool game_lose=false;

void increase_values(int i,int j){//Tăng giá trị của mỗi ô xung quanh một ô chứa mìn.
    if(i>=0&&i<10&&j>=0&&j<10&&table_mine_positions[i][j]!='X')
        table_mine_positions[i][j]++;
}
void create_mine_positions(){//Tạo vị trí của mìn trên bảng, tăng giá trị các ô xung quanh chứa mìn.
    int counter=0;
    srand(time(NULL));
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            table_mine_positions[i][j]='0';
    int i=0;
    int j=0;
    while(counter<10){
        int i=rand()%10;
        int j=rand()%10;
        if(table_mine_positions[i][j]=='0'){
            table_mine_positions[i][j]='X';
            increase_values(i-1,j);
            increase_values(i+1,j);
            increase_values(i,j-1);
            increase_values(i,j+1);
            increase_values(i-1,j-1);
            increase_values(i-1,j+1);
            increase_values(i+1,j-1);
            increase_values(i+1,j+1);
            counter++;
        }
    }
}
void create_table(){//Khởi tạo bảng trò chơi với ký tự *
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            table[i][j]='*';
}
void print_table(char arr[10][10]){// In bảng trò chơi lên màn hình.
    cout<<"    ";
    for(int i=0;i<10;i++)
        cout<<setw(3)<<i;
    cout<<endl<<"  ";
    for(int i=0;i<36;i++)
        cout<<"_";
    cout<<endl;
    for(int i=0;i<10;i++){
        cout<<setw(3)<<i<<"|";
        for(int j=0;j<10;j++)
            cout<<setw(3)<<arr[i][j];
        cout<<"  |"<<i<<endl;
    }
    cout << "  ";
    for(int i=0;i<36;i++)
        cout<<"-";
    cout<<endl;
    cout<<"    ";
    for(int i=0;i<10;i++)
        cout<<setw(3)<<i;
}
void open_cell(){//Mở ô được chọn bởi người chơi và kiểm tra xem có mìn không.
    int i,j;
    do{
        cout << "Input cell position: ";
        cin>>i>>j;
    }while(i<0||i>9||j<0||j>9);
    if(table_mine_positions[i][j]=='X'){
        table[i][j]='X';
        game_lose=true;
        for(int i=0;i<10;i++)
            for(int j=0;j<10;j++)
                if(table_mine_positions[i][j]=='X')
                    table[i][j]='X';
    }
    else
        show_content(i,j);
}
void place_or_remove_flag(){//Đặt hoặc loại bỏ cờ trên ô được chọn
    int i,j;
    do
        cin>>i>>j;
    while(i<0||i>9||j<0||j>9);
    if (table[i][j]=='*'){
        table[i][j]='F';
        flag_counter++;
        if(table_mine_positions[i][j]=='X')
            mines_flagged_counter++;
    }
    else if (table[i][j]=='F'){
        table[i][j]='*';
        flag_counter--;
        if(table_mine_positions[i][j]=='X')
            mines_flagged_counter--;
    }
}
void input_symbol(){//Nhập ký tự "o" hoặc "f"
    cout << "Choose 'o' or 'f': ";
    cin>>symbol;
    switch (symbol){
        case 'o': open_cell(); break;
        case 'f': place_or_remove_flag(); break;
        default:
            cout << "Wrong choice!\n";
            input_symbol();
    }
}
void show_content(int i,int j){//Hiển thị nội dung ô dược chọn
    if (table[i][j]=='*'&&table_mine_positions[i][j]!='X'&&i>=0&&i<10&&j>=0&&j<10){
        table[i][j]=table_mine_positions[i][j];
        if(table_mine_positions[i][j]=='0'){
            show_content(i,j-1);
            show_content(i,j+1);
            show_content(i-1,j-1);
            show_content(i+1,j-1);
            show_content(i+1,j+1);
            show_content(i-1,j+1);
            show_content(i-1,j);
            show_content(i+1,j);
        }
    }
}
bool game_win_check(){//Kiểm tra xem đã thắng chưa
    if(flag_counter==10&&mines_flagged_counter==10)
        return 1;
    else
        return 0;
}
void game(){
    create_table();
    create_mine_positions();
    while(!game_lose&&!game_win_check()){
        game_time=time(0);
        print_table(table);
        cout<<endl<<"Flags:"<<flag_counter<<endl;
        cout<<"Time:"<<game_time-time_since_start<<endl;
        input_symbol();
    }
    if(game_lose){
        print_table(table);
        cout<<endl<<"GAME OVER."<<endl;
    }
    if(game_win_check()){
        cout<<"Time to complete:"<<game_time-time_since_start<<endl;
        cout<<endl<<"YOU WIN!"<<endl;
    }
}
int main(){
    cout<<"Rules:";
    cout<<endl<<"Enter 'o' , then enter value of i and j to open cell[i][j].";
    cout<<endl<<"Enter 'f' ,then enter value of i and j to place ";
    cout<<"or remove flag on cell [i][j].";
    cout<<endl<<endl;
    game();
    return 0;
}
