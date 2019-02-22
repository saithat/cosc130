//Sai Thatigotla
//9/21/18
//COSC130
//TAs: Grace and Tasmia
#include <cstdio>
#include <iostream>
#include <fstream>

using namespace std;

struct Room {
	int roomNum;
	string description;
	int n = -1;			//default to invalid directions
	int s = -1;
	int e = -1;
	int w = -1;
};

class Game {
	public:
		Room *rooms;
		Game(int num);
		void SetRoom(int roomInd, int num);
		void Summary(int roomInd, string descrip);
		void Exits(int roomInd, string descrip2);
		Room GetRoom(int roomInd);

};
int main(int argc, char *argv[])
{
	ifstream in;
	string str;
	string tmp;
	int counter = 0;
	int roomIndex = 0;
	in.open(argv[1]);

	if(argc != 2){
		printf("insufficent arguments\n");
		return 1;
	}
	
	if(!in){
		printf("File does not exist.\n");
	}

	getline(in, str);

	while(in){
		if(str[0]=='~'){
			counter++;
		}
		getline(in, str);
	}

	str = "";

	Game game(counter/3);

	counter = 0; //cleared variable to now keep track of what part of room file it is in
	
	in.close();
	in.open(argv[1]);

	getline(in, tmp);

	while(in){
		while(!(tmp[0]=='~')){
			if(counter == 2){  //if it is at one of the exit parts of the file, read and pass exits one by one for scanf
				game.Exits(roomIndex, tmp);
				getline(in, tmp);
			}else{
			str.append(tmp);
			str.append("\n");
			getline(in, tmp);
			}
		}
		if(counter == 0){  //room number part
			game.SetRoom(roomIndex, roomIndex);
			counter++;
		}
		else if(counter == 1){  //description part
			game.Summary(roomIndex, str);
			counter++;
		}else if(counter == 2){
			counter = 0;
			roomIndex++;
		}
		getline(in, tmp);
		str = "";
	}

	char ui[1];
	char lol[100];			//please don't enter more than 100 characters into input
	int roomC = 0;
	while(ui[0] != 'q'){
		printf("> ");
		scanf(" %s", lol);
		sscanf(lol, "%c", ui);
		switch(ui[0]){
			case 'n':
				{
					if(game.GetRoom(roomC).n != -1){
						roomC = game.GetRoom(roomC).n;
					}else{
						printf("That's Invalid\n");
					}
					break;
				}
			case 'e':
				{
					if(game.GetRoom(roomC).e != -1){
						roomC = game.GetRoom(roomC).e;
					}else{
						printf("That's Invalid\n");
					}
					break;
				}
			case 's':
				{
					if(game.GetRoom(roomC).s != -1){
						roomC = game.GetRoom(roomC).s;
					}else{
						printf("That's Invalid\n");
					}
					break;
				}
			case 'w':
				{
					if(game.GetRoom(roomC).w != -1){
						roomC = game.GetRoom(roomC).w;
					}else{
						printf("That's Invalid\n");
					}
					break;
				}
			case 'l':
				{
					printf("Room #%d\n", game.GetRoom(roomC).roomNum);
					printf("%s\n", game.GetRoom(roomC).description.c_str());
					printf("Exits: ");
						if(game.GetRoom(roomC).n != -1)
						{
							printf("n\n");
						}
						if(game.GetRoom(roomC).s != -1)
						{
							printf("s\n");
						}
						if(game.GetRoom(roomC).e != -1)
						{
							printf("e\n");
						}
						if(game.GetRoom(roomC).w != -1)
						{
							printf("w\n");
						}
					break;
				}
			case 'q':
				{
					return 0;
				}
			default:
				{
					printf("That's not valid\n");
					break;
				}
			}
	}

	
	in.close();

	return 0;
	
}

Game::Game(int num){
	rooms = new Room[num];
}

void Game::SetRoom(int roomInd, int num){
	rooms[roomInd].roomNum = num;
}
void Game::Summary(int roomInd, string descrip){
	rooms[roomInd].description = descrip;
}
void Game::Exits(int roomInd, string descrip2){
	int num = 0;
	char letter [1];
	sscanf(descrip2.c_str(), "%c %d",letter, &num);
	switch (letter[0])
	{
		case 'n':
			rooms[roomInd].n = num;
			break;
		case 's':
			rooms[roomInd].s = num;
			break;
		case 'e':
			rooms[roomInd].e = num;
			break;
		case 'w':
			rooms[roomInd].w = num;
			break;
		default:
			printf("Not a valid direction\n");
			break;
	}
}
Room Game::GetRoom(int RoomInd){
	return rooms[RoomInd];
}
