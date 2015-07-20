#include "graph_t.h"
#include "algorithm_define.h"
#include "al_base.h"
#include <iostream>

using std::cout;
using std::endl;

void print_element(int i){
	switch(i){
	case 30:     cout<<"logic"; break;
	case 163:    cout<<"LUT"; break;
	case 356:    cout<<"Modular add or sub "; break;
	case 164:    cout<<"Shift"; break;
	case 462:    cout<<"Modular Multiplication"; break;
	case 422:    cout<<"GF Multiplication"; break;
	case 60:     cout<<"substitution"; break;
	default:     cout<<"error elememt,the delay is:"<<i<<endl; break;
	}
}

int main(){

//*************AES******************	
	al_base aes = al_base(10,32,5,4);
	aes.init_graph(init_al_graph,"AES");
	std::vector<al_protocol::element> aes_r;
	int aes_delay;
	aes.key_path(aes_r,aes_delay);
	cout<<"the critical path of aes is:"<<endl;
	for(al_protocol::element i:aes_r){
		print_element(i);
		cout<<" -> "<<endl;		
	}
	cout<<"the total delay of a round is :"<<aes_delay/100.0<<"ns"<<endl;	
//*************DES*******************

	al_base des = al_base(16,32,7,5);
	des.init_graph(init_al_graph,"DES");
	std::vector<al_protocol::element> des_r;
	int des_delay;
	des.key_path(des_r,des_delay);
	cout<<"the critical path of des is:"<<endl;
	for(al_protocol::element i:des_r){
		print_element(i);
		cout<<" -> "<<endl;		
	}
	cout<<"the total delay of a round is :"<<des_delay/100.0<<"ns"<<endl;	

//**************IDEA******************
	al_base idea = al_base(8,16,23,3);
	idea.init_graph(init_al_graph,"IDEA");
	std::vector<al_protocol::element> idea_r;
	int idea_delay;
	idea.key_path(idea_r,idea_delay);
	cout<<"the critical path of idea is:"<<endl;
	for(al_protocol::element i:idea_r){
		print_element(i);
		cout<<" -> "<<endl;		
	}
	cout<<"the total delay of a round is :"<<idea_delay/100.0<<"ns"<<endl;	
	
	
	
	return 0;
	
}




