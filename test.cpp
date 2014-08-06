#include <iostream>
#include <queue>
#include <time.h>


int global_num;
void input_tile(int[]);

class puzzle
{
private:
	int depth;
	int rep;
public:
	int no;
	int tile[9];
	int empty;
	int prevzero;
	void initialize();
	void output_tile();
	int heuristic();
	void generate();
	puzzle* root;
	puzzle(){
		rep=0;
		no = global_num;
		global_num++;
		//prevzero = n;
	}
	void zero(){
		for(int i=0;i<9;i++){
			if(tile[i]==0){
				empty=i;	//0の位置を保持
				break;
			}		
		}

	}
};

std::queue<puzzle> qu;
puzzle* last;

int main(){
	global_num=0;
	srand((unsigned int)time(NULL));
	puzzle initial;
	initial.initialize();
//	initial.output_tile();//初期状態
	initial.tile[0]=1;
	initial.tile[1]=2;
	initial.tile[2]=5;
	initial.tile[3]=3;
	initial.tile[4]=4;
	initial.tile[5]=0;
	initial.tile[6]=6;
	initial.tile[7]=7;
	initial.tile[8]=8;
	initial.zero();
	initial.output_tile();
	initial.generate();
	for(int i=0;i<20;i++){
		qu.front().generate();
		qu.pop();	
	}
	while(qu.empty()!=true){
		//qu.front().output_tile();
		qu.pop();
	}
	return 0;
}

void puzzle::initialize(){
		root=NULL;
		int g,tmp;
		depth=0;
		for(int i=0;i<9;i++){	//シャッフル前
			tile[i]=i;
		}
		for(int i=0;i<8;i++){
			g = rand() % (9 - i) + i; //i番目より後ろの要素
			tmp = tile[g];
			tile[g] = tile[i];
			tile[i] = tmp;
		}
		zero();
		prevzero=-1;
}

int puzzle::heuristic(){
	int count = 0;
	for(int i=0;i<9;i++){
		if(tile[i]!= i) count++;
	}
	return count;
}

void puzzle::generate(){
	int tmp,swap,num;
	puzzle node[4];

	if(empty==4) num=4;
	else if  (empty==0 || empty==2 || empty==6 || empty==8) num=2;
	else num=3;

	//std::cout << "ここから親" << no << std::endl;

	for(int i=0;i<4;i++){
		for(int j=0;j<9;j++){
			node[i].tile[j]=tile[j];
			node[i].depth=depth+1;
			node[i].root = this;
		}
	}
	swap=node[0].tile[empty];
	if(empty==4){
		node[0].tile[4]=node[0].tile[1];
		node[0].tile[1]=swap;
		if(prevzero==1) node[0].rep=1;
		node[1].tile[4]=node[1].tile[3];
		node[1].tile[3]=swap;
		if(prevzero==3) node[1].rep=1;
		node[2].tile[4]=node[2].tile[5];
		node[2].tile[5]=swap;
		if(prevzero==5) node[2].rep=1;
		node[3].tile[4]=node[3].tile[7];
		node[3].tile[7]=swap;
		if(prevzero==7) node[3].rep=1;
		}
	else if(empty == 0){
		node[0].tile[0]=node[0].tile[1];
		node[0].tile[1]=swap;
		if(prevzero==1) node[0].rep=1;
		node[1].tile[0]=node[0].tile[3];
		node[1].tile[3]=swap;
		if(prevzero==3) node[1].rep=1;
	}
	else if(empty == 2){
		node[0].tile[2]=node[0].tile[1];
		node[0].tile[1]=swap;
		if(prevzero==1) node[0].rep=1;
		node[1].tile[2]=node[1].tile[5];
		node[1].tile[5]=swap;
		if(prevzero==1) node[1].rep=1;
	}
	else if(empty == 6){
		node[0].tile[6]=node[0].tile[3];
		node[0].tile[3]=swap;
		if(prevzero==3) node[0].rep=1;
		node[1].tile[6]=node[0].tile[7];
		node[1].tile[7]=swap;
		if(prevzero==7) node[1].rep=1;
	}
	else if(empty == 8){
		node[0].tile[8]=node[0].tile[5];
		node[0].tile[5]=swap;
		if(prevzero==5) node[0].rep=1;
		node[1].tile[8]=node[1].tile[7];
		node[1].tile[7]=swap;
		if(prevzero==7) node[1].rep=1;
	}
	else if(empty == 1){
		node[0].tile[1]=node[0].tile[0];
		node[0].tile[0]=swap;
		if(prevzero==0) node[0].rep=1;
		node[1].tile[1]=node[1].tile[2];
		node[1].tile[2]=swap;
		if(prevzero==2) node[1].rep=1;
		node[2].tile[1]=node[2].tile[4];
		node[2].tile[4]=swap;
		if(prevzero==4) node[2].rep=1;
	}
	else if(empty == 3){
		node[0].tile[3]=node[0].tile[0];
		node[0].tile[0]=swap;
		if(prevzero==0) node[0].rep=1;
		node[1].tile[3]=node[1].tile[4];
		node[1].tile[4]=swap;
		if(prevzero==4) node[1].rep=1;
		node[2].tile[3]=node[2].tile[6];
		node[2].tile[6]=swap;
		if(prevzero==6) node[2].rep=1;
	}
	else if(empty == 5){
		node[0].tile[5]=node[0].tile[2];
		node[0].tile[2]=swap;
		if(prevzero==2) node[0].rep=1;
		node[1].tile[5]=node[1].tile[4];
		node[1].tile[4]=swap;
		if(prevzero==4) node[1].rep=1;
		node[2].tile[5]=node[2].tile[8];
		node[2].tile[8]=swap;
		if(prevzero==8) node[2].rep=1;
	}
	else if(empty == 7){
		node[0].tile[7]=node[0].tile[4];
		node[0].tile[4]=swap;
		if(prevzero==4) node[0].rep=1;
		node[1].tile[7]=node[1].tile[6];
		node[1].tile[6]=swap;
		if(prevzero==6) node[1].rep=1;
		node[2].tile[7]=node[2].tile[8];
		node[2].tile[8]=swap;
		if(prevzero==8) node[2].rep=1;
	}
	for(int i=0;i<num;i++) {
		if(node[i].rep==1) continue;
		node[i].zero();
		node[i].prevzero=empty;
		qu.push(node[i]);
		node[i].output_tile();
		if(node[i].heuristic()==0) {
			std::cout<< "Goal" << std::endl;
			last = &node[i];
			exit(1);
		}
		//node[i].output_tile();
	}

}

void puzzle::output_tile(){
	std::cout << "No." << no << std::endl;
	std::cout << "depth:" << depth << " error:" << heuristic() << std::endl;
	if(depth != 0) std::cout << "親: No."<< root->no << std::endl;
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			if (tile[i*3+j]==0) std::cout << " "; 
			else std::cout << tile[i*3+j] ;
		}
	std::cout << std::endl;
	}
	std::cout << std::endl;
}
