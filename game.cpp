#include<bits/stdc++.h>
#include<conio.h>
#include<time.h>
using namespace std;

class cPlayer{  
public:
    int x,y;
    cPlayer(int width){
        x = width/2;    // constructs the player right in the middle column
        y=0;
    }
};

class cLane{
private:
    deque<bool> cars;
    bool right;

public:
    cLane(int width){
        for(int i=0;i<width;i++)
            cars.push_front(true);  // inititally every lane is filled with cars <hue hue hue>
        right = rand()%2;
    }

    void Move(){

        if(right){
            if(rand()%10 <= 1)
            cars.push_front(true);
            else
            cars.push_front(false);
            cars.pop_back();
        }
        
        else{
            if(rand()%10 <= 1)
            cars.push_back(true);
            else
            cars.push_back(false);
            cars.pop_front();
        } 
    }

    bool checkPosition(int pos) {return cars[pos];}
    
    void changeDirection(){right = !right;}

};

class cGame{

private:
    bool quit;
    int numberOfLanes;
    int width;
    int score;
    
    cPlayer * player;
    vector<cLane*> lanes;

public:
    cGame(int w=30, int h=15){
        numberOfLanes = h;
        width = w ;
        quit = false;
        score = 0;

        for(int i=0;i<numberOfLanes;i++)
            lanes.push_back(new cLane(width));
        
        player = new cPlayer(width);
    }

    void Draw(){
        system("cls");
        for(int i=0;i<numberOfLanes;i++){
            for(int j=0;j<width;j++){

                if(i==0 && (j == 0 || j == width-1)) cout<<"S";
                if(i==numberOfLanes-1 && (j == 0 || j == width-1)) cout<<"E";
                if(lanes[i]->checkPosition(j) && i!=0 && i!= numberOfLanes-1)
                    cout<<"#";
                else if(player->x == j && player->y == i)
                    cout<<"||";
                else 
                    cout<<" ";
            }
            cout<<endl;
        }
        cout<<"Score: "<< score <<endl;
    }

    void Input(){
        if(_kbhit()){

            char current = _getch();
                if(current == 'a')
                    player->x--;
                if(current == 's')
                    player->y++;
                if(current == 'd')
                    player->x++;
                if(current == 'w')
                    player->y--;
                if(current == 'q')
                quit = true;
        }
    }

    void Logic(){

        for(int i=1; i<numberOfLanes-1;i++){
            if(rand()%10 == 1)
                lanes[i]->Move();
            if(lanes[i]->checkPosition(player->x) && player->y == i)
                quit = true;
        }

        if(player->y == numberOfLanes-1){
            score++;
            player->y=0;
            cout<<"\x07";
            lanes[rand()%numberOfLanes]->changeDirection();
        }
    }

    void Run(){
        
        while(!quit){
            Input();
            Draw();
            Logic();
        }
    }
    ~cGame(){
        delete player;
        for(int i=0;i<lanes.size();i++){
            cLane *current = lanes.back();
            lanes.pop_back();
            delete current;
        }
    }
};

int main(){

    srand(time(NULL));

    cGame game(50,8);
    game.Run();
    
    cout<<"GAME OVER!!"<<endl;

    getchar();
    return 0;
}