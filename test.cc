#include "graph_t.h"
#include "algorithm_define.h"
#include "al_base.h"
#include <iostream>
#include <fstream>

using std::cout;
using std::endl;


std::ofstream out("output.txt");


void print_element(int i){
	switch(i){
	case 30:     out<<"logic"; break;
	case 163:    out<<"LUT"; break;
	case 356:    out<<"Modular add or sub "; break;
	case 164:    out<<"Shift"; break;
	case 462:    out<<"Modular Multiplication"; break;
	case 422:    out<<"GF Multiplication"; break;
	case 60:     out<<"substitution"; break;
	default:     out<<"error elememt,the delay is:"<<i<<endl; break;
	}
}

int main(){


//*************AES******************	
	out << "*************AES***************" << endl;
	vector<al_protocol::element> ie_aes = {al_protocol::LUT,al_protocol::SH,
	                                       al_protocol::GFM,al_protocol::BL};
	//al_base aes = al_base(10, 32, 5, ie_aes);//初始化还是赋值，这里是调用拷贝初始化？？？？
	al_base aes(10, 32, 5, ie_aes);
	aes.init_graph(init_al_graph,"AES");
	std::vector<al_protocol::element> aes_r;
	int aes_delay;
	aes.key_path(aes_r,aes_delay);
	out<<"the critical path of aes is:"<<endl;
	for(al_protocol::element i:aes_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<aes_delay/100.0<<"ns"<<endl;	
	al_protocol::element aes_maxe;
	aes.max_delay_element(aes_maxe);
	out<<"the max_delay_element is :"<<aes_maxe/100.0<<"ns"<<endl;	


//*************DES*******************
	out << endl<<"*************DES****************" << endl;
    vector<al_protocol::element> ie_des = {al_protocol::SUB, al_protocol::BL,
	                                       al_protocol::LUT};
	al_base des(16,32,7,ie_des);
	des.init_graph(init_al_graph,"DES");
	std::vector<al_protocol::element> des_r;
	int des_delay;
	des.key_path(des_r,des_delay);
	out<<"the critical path of des is:"<<endl;
	for(al_protocol::element i:des_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<des_delay/100.0<<"ns"<<endl;	
	al_protocol::element des_maxe;
	des.max_delay_element(des_maxe);
	out<<"the max_delay_element is :"<<des_maxe/100.0<<"ns"<<endl;	

//**************IDEA******************
	out << endl << "*************IDEA*************" << endl;
    vector<al_protocol::element> ie_idea = {al_protocol::MM, al_protocol::MAS,
	                                        al_protocol::BL};
	al_base idea(8,16,23,ie_idea);
	idea.init_graph(init_al_graph,"IDEA");
	std::vector<al_protocol::element> idea_r;
	int idea_delay;
	idea.key_path(idea_r,idea_delay);
	out<<"the critical path of idea is:"<<endl;
	for(al_protocol::element i:idea_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<idea_delay/100.0<<"ns"<<endl;	
	al_protocol::element idea_maxe;
	idea.max_delay_element(idea_maxe);
	out<<"the max_delay_element is :"<<idea_maxe/100.0<<"ns"<<endl;	
	
//**************BLOWFISH******************
	out << endl << "*************BLOWFISH*************" << endl;
    vector<al_protocol::element> ie_blowfish = {al_protocol::LUT, al_protocol::BL,
	                                        al_protocol::MAS};
	al_base blowfish(16,32,14,ie_blowfish);
	blowfish.init_graph(init_al_graph,"BLOWFISH");
	std::vector<al_protocol::element> blowfish_r;
	int blowfish_delay;
	blowfish.key_path(blowfish_r,blowfish_delay);
	out<<"the critical path of blowfish is:"<<endl;
	for(al_protocol::element i:blowfish_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<blowfish_delay/100.0<<"ns"<<endl;	
	al_protocol::element blowfish_maxe;
	blowfish.max_delay_element(blowfish_maxe);
	out<<"the max_delay_element is :"<<blowfish_maxe/100.0<<"ns"<<endl;		
	
	
//**************CAMELLIA******************
	out << endl << "*************CAMELLIA*************" << endl;
    vector<al_protocol::element> ie_camellia = {al_protocol::LUT, al_protocol::BL,
	                                            al_protocol::SUB};
	al_base camellia(18,8,8,ie_camellia);
	camellia.init_graph(init_al_graph,"CAMELLIA");
	std::vector<al_protocol::element> camellia_r;
	int camellia_delay;
	camellia.key_path(camellia_r,camellia_delay);
	out<<"the critical path of camellia is:"<<endl;
	for(al_protocol::element i:camellia_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<camellia_delay/100.0<<"ns"<<endl;	
	al_protocol::element camellia_maxe;
	camellia.max_delay_element(camellia_maxe);
	out<<"the max_delay_element is :"<<camellia_maxe/100.0<<"ns"<<endl;		
	
	return 0;
	
}




