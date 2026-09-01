#include<iostream>
#include<iomanip>
using namespace std;

int level =2;

namespace Physics {
// clamp a velocity
 double clamp(double val, double min, double max){
	 if(max < min) return 0;
	 cout<<"Physics Clamp called"<<endl;
	 if(val < min) return min;
	 if(val > max) return max;
	 return val;
 }
 double lerp(double a, double b, double t){
	 cout<<"Physics Lerp called"<<endl;
	 return a + t * (b-a);
 }
}


namespace GameMath {
 int clamp(int val, int min, int max){
	 if(max < min) return 0;
	 cout<<"GameMath Clamp called"<<endl;
	 if(val < min) return min;
	 if(val > max) return max;
	 return val;
 }
 double lerp(double a, double b, double t){
	 cout<<"Gamemath Lerp called"<<endl;
	 return a + t * (b-a);
 }
}

namespace Engine{
	namespace Audio{
	void playSound(string name){
		cout<<"Playing: "<<name<<endl;
	}
	}
}


class Entity{
    string name;
    int health;
    int level;
    string type; // player, enemy, item

    public :

    Entity& setName(const string& name) {
        this->name = name;
        return *this;
    }

    Entity& setHealth(int health){
        this->health = health;
        return *this;
    }

    Entity& setLevel(int level){
        this->level = level;
        return *this;
    }

    Entity& setType(const string& type){
        this->type = type;
        return *this;
    }

    string getName() const{
        return name;
    }

    int getHealth() const{
        return health;
    }

    int getLevel() const{
        return level;
    }

    string getType() const{
        return type;
    }

    void displayInfo() const{
        cout << "Display Info :" << endl;
        cout << name << endl;
        cout << health << endl;
        cout << level << endl;
        cout << type << endl;

    }

};

void Count(int& cnt1,int& cnt2,int& cnt3,int& cnt4,int& cnt5, int& gridval){
	if(gridval == 0){
		cnt1++;
	}
	else if(gridval == 1){
		cnt2++;
	}
	else if(gridval == 2){
		cnt3++;
	}
	else if(gridval == 3){
		cnt4++;
	}
	else{
		cnt5++;
	}
}



int main(){
    
    Entity player, enemy, item;
    player.setName("Aragorn").setHealth(100).setLevel(10).setType("Player");
    enemy.setName("Orc").setHealth(60).setLevel(5).setType("Enemy");
    item.setName("HealthPotion").setHealth(0).setLevel(1).setType("Item");
    
    player.displayInfo();
	enemy.displayInfo();
	item.displayInfo();


    cout<<"Physics Clamp: ";
	cout<<Physics::clamp(30,80, 80);
	cout<<endl;
	cout<<"Physics Lerp: ";
	cout<<Physics::lerp(9, 6,84);
	cout<<endl<<endl;

	cout<<"GameMath Clamp: ";
	cout<<GameMath::clamp(7, 55, 150);
	cout<<endl;
	cout<<"GameMath Lerp: ";
	cout<<GameMath::lerp(5, 64, 62);
	cout<<endl;

	{
		using namespace Physics;
		cout<<clamp(40, 54, 3444);
	}
	cout<<endl;
	{
		using namespace GameMath;
		cout<<clamp(4040, 44, 540);
	}
	cout<<endl;


    int R, C;
    cout << "Enter R and C :" << endl;
    cin >> R >> C;
    
    // Dynamically Allocated the memory
    int** grid = new int*[R];

	for(int i = 0; i < R; i++){
		grid[i] = new int[C];
		for(int j = 0; j < C; j++){
			grid[i][j] = (rand() % 5);
		}
	}

	cout<<"===== GAME MAP "<<R<<" * "<<C<<" "<<"====="<<endl;
	int cnt1 = 0, cnt2 = 0, cnt3 = 0, cnt4 = 0, cnt5 = 0;
	for(int i = 0; i < R; i++){
		for(int j = 0; j < C; j++){
			Count(cnt1, cnt2, cnt3, cnt4, cnt5, grid[i][j]);
			cout<<grid[i][j]<<" ";
		}
		cout<<endl;
	}

	cout<<"Legend: 0=Grass 1=Water 2=Mountain 3=Forest 4=Dungeon"<<endl;
	cout<<endl;
	cout<<"Tile Count:"<<endl;
	cout<<"Grass : "<<cnt1<<endl;
	cout<<"Water : "<<cnt2<<endl;
	cout<<"Mountain : "<<cnt3<<endl;
	cout<<"Forest : "<<cnt4<<endl;
	cout<<"Dungeon : "<<cnt5<<endl;


    int level = 1; 
	cout<<"Printing global value: "<<::level<<endl;
	cout<<"Printing local value: "<<level<<endl;
	cout<<"Calling Nested Namespace: ";
	Engine::Audio::playSound("sword_clash");
    return 0;

}
