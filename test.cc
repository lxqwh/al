#include "graph_t.h"
#include "algorithm_define.h"
#include "al_base.h"
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <deque>
#include <vector>

#define NOT_INCLUDE_SINGLE  1


using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::string;
using std::set;

std::ofstream out("output");
std::ofstream out_round("data_in_round");
std::ofstream out_al("data_in_al");
std::map<string, set<int>> mix = std::map<string, set<int>>();
vector<deque<al_protocol::element>> key_path = vector<deque<al_protocol::element>>();


void print_element(int i){
	switch(i){
	case 300:    out<<"X2A1"; break;	
	case 81:     out<<"AESX2"; break;		
	case 70:     out<<"BR"; break;
	case 20:     out<<"AND"; break;	
	case 21:     out<<"OR"; break;	
	case 10:     out<<"NOT"; break;	
	case 60:     out<<"XOR"; break;	
	case 520:    out<<"LUT"; break;
	case 270:    out<<"Modular add or sub "; break;
	case 271:    out<<"Shift"; break;
	case 900:    out<<"Modular Multiplication"; break;
	case 800:    out<<"GF Multiplication"; break;
	case 500:    out<<"substitution"; break;
	default:     out<<"error element,the delay is:"<<i<<endl; break;
	}
}
string element_to_string (al_protocol::element i){
	switch(i){
	case al_protocol::X2A1:   return "X2A1";
	case al_protocol::AESX2:  return "AESX2";
	case al_protocol::BR:     return "BR";
	case al_protocol::AND:    return "AND";
	case al_protocol::NOT:    return "NOT";
	case al_protocol::XOR:    return "XOR";
	case al_protocol::OR:     return "OR";
	case al_protocol::LUT:    return "LUT"; 
	case al_protocol::MAS:    return "MAS"; 
	case al_protocol::SH:     return "SH"; 
	case al_protocol::MM:     return "MM"; 
	case al_protocol::GFM:    return "GFM";
	case al_protocol::SUB:    return "SUB"; 
	default:     out<<"error element,the delay is:"<<i<<endl; return string();
	}
}


void mix_temp(std::map<string, set<int>> &mix,deque<al_protocol::element> &de, int delay, int al){
	int i = de.size();
	string s = string();
	int c_delay = 0;
	while(i-- >0){
		for(size_t j=0;j<de.size();j++){
			c_delay += int(de[j]);
			if(c_delay <= delay){
				s = s + element_to_string(de[j]) + " ";
				mix[s + "| the delay is: " + std::to_string(c_delay/1000.0) + " ns"].insert(al);
			}
			else
				break;
		}
		s.clear();
		c_delay = 0;
		de.push_back(*(de.begin()));
		de.pop_front();
	}
}

void do_mix(std::map<string, set<int>> &mix, vector<deque<al_protocol::element>> &key_path, int delay){
	for(unsigned i = 0; i<key_path.size(); i++){
		mix_temp(mix,key_path[i], delay, i+1);
	}
}

void print_mix(std::map<string, set<int>> &mix){
	for (std::map<string, set<int>>::iterator i = mix.begin(); i != mix.end(); i++){
#if NOT_INCLUDE_SINGLE
	    if(i->second.size()==1) continue;
#endif
		out << "组合类型: " << i->first << endl;
		out << "算法个数: " << i->second.size() << " 分别是：" << endl;
		for (int j : i->second)
			out << j << " ";
		out << endl;	

	}
}
al_base* build_al(string type){
	al_base *re;
	vector<al_protocol::element> ie; 
	if(type=="AES"){
		ie = {al_protocol::LUT,al_protocol::BR,
	          al_protocol::GFM,al_protocol::XOR};
		re = new al_base(type,10, 32, 5, ie);
	}	
	else if(type=="DES"){
		ie = {al_protocol::SUB, al_protocol::XOR,
	          al_protocol::LUT};
		re = new al_base(type,16,32,7,ie);
	}
	else if(type=="IDEA"){
		ie = {al_protocol::MM, al_protocol::MAS,
		      al_protocol::XOR};
		re = new al_base(type,8,16,23,ie);
	}		
	else if(type=="BLOWFISH"){
		ie = {al_protocol::LUT, al_protocol::XOR,
		      al_protocol::MAS};
		re = new al_base(type,16,32,14,ie);
	}	
	else if(type=="CAMELLIA"){
		ie = {al_protocol::LUT, al_protocol::XOR,
		      al_protocol::SUB};
		re = new al_base(type,18,32,8,ie);
	}	
	else if(type=="CAST128"){
		ie = {al_protocol::XOR, al_protocol::SH,
		      al_protocol::LUT, al_protocol::MAS};
		re = new al_base(type,16,32,14,ie);
	}	
	else if(type=="GOST"){
		ie = {al_protocol::XOR, al_protocol::SH,
		      al_protocol::LUT, al_protocol::MAS};
		re = new al_base(type,32,32,5,ie);
	}		
//	else if(type=="KASUMI"){
//		ie = 
//		re = new al_base(type,32,32,5,ie);
//	}		
	else if(type=="RC5"){
		ie = {al_protocol::XOR, al_protocol::SH,
		      al_protocol::MAS};
		re = new al_base(type,24,32,4,ie);
	}		
	else if(type=="SEED"){
		ie = {al_protocol::XOR, al_protocol::LUT,
		      al_protocol::MAS};
		re = new al_base(type,16,32,24,ie);
	}		
	else if(type=="TWOFISH"){
		ie = {al_protocol::XOR, al_protocol::LUT,
		      al_protocol::GFM, al_protocol::MAS,
		      al_protocol::SH};
		re = new al_base(type,16,32,20,ie);
	}		
	else if(type=="SM4"){
		ie = {al_protocol::XOR, al_protocol::LUT,
		      al_protocol::SH};
		re = new al_base(type,32,32,9,ie);
	}		
	else if(type=="RC6"){
		ie = {al_protocol::MAS, al_protocol::LUT,al_protocol::X2A1,
		      al_protocol::SH, al_protocol::XOR};
		re = new al_base(type,20,32,15,ie);
	}		
	else if(type=="SERPENT"){
		ie = {al_protocol::SH, al_protocol::XOR, 
		      al_protocol::MAS, al_protocol::LUT};
		re = new al_base(type,32,32,19,ie);
	}		
	else if(type=="TEA"){
		ie = {al_protocol::XOR, al_protocol::SH,
		      al_protocol::MAS};
		re = new al_base(type,32,32,11,ie);
	}	
	else if(type=="XTEA"){
		ie = {al_protocol::XOR, al_protocol::SH,
		      al_protocol::MAS};
		re = new al_base(type,32,32,10,ie);
	}	
	else if(type=="SKIPJECT"){
		ie = {al_protocol::XOR, al_protocol::LUT};
		re = new al_base(type,32,32,15,ie);
	}		
	
	re->init_graph(init_al_graph,type);		
    return re;
}

void print_al_inf(std::ofstream &out, std::ofstream &out_round, std::ofstream &out_al, 
                  vector<deque<al_protocol::element>> &key_path, al_base *al){
	std::vector<al_protocol::element> al_r;
	int delay;
	al->key_path(al_r,delay);
	key_path.push_back(deque<al_protocol::element>(al_r.begin(),al_r.end()));	
	
	out<<"the critical path of "<<al->getname()<<" is:"<<endl;
	for(al_protocol::element i:al_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<delay/1000.0<<"ns"<<endl;	
	al_protocol::element maxe;
	al->max_delay_element(maxe);
	out<<"the max_delay_element is :"<<maxe/1000.0<<"ns"<<endl;	
//for k-means
    out_round<<al->getname()<<" "<<delay/1000.0<<endl;
    out_al<<al->getname()<<" "<<(delay/1000.0)*(al->getround())<<endl;
}





int main(){
	
	al_base *al;

//*************AES******************	
	out <<"*************1.AES****************" << endl;
    al = build_al("AES");
    print_al_inf(out, out_round, out_al, key_path, al);

//*************DES*******************
	out << endl<<"*************2.DES****************" << endl;
	al = build_al("DES");
    print_al_inf(out, out_round, out_al, key_path, al);

//**************IDEA******************
	out << endl << "*************3.IDEA*************" << endl;
	al = build_al("IDEA");
    print_al_inf(out, out_round, out_al, key_path, al);
	
//**************BLOWFISH******************
	out << endl << "*************4.BLOWFISH*************" << endl;
	al = build_al("BLOWFISH");
    print_al_inf(out, out_round, out_al, key_path, al);	
	
	
//**************CAMELLIA******************
	out << endl << "*************5.CAMELLIA*************" << endl;
	al = build_al("CAMELLIA");
    print_al_inf(out, out_round, out_al, key_path, al);	

//**************CAST128******************
	out << endl << "*************6.CAST128*************" << endl;
	al = build_al("CAST128");
    print_al_inf(out, out_round, out_al, key_path, al);	

	
//**************GOST******************
	out << endl << "*************7.GOST*************" << endl;
	al = build_al("GOST");
    print_al_inf(out, out_round, out_al, key_path, al);
	

//**************KASUMI******************
//	out << endl << "*************KASUMI*************" << endl;
//	al = build_al("KASUMI");
//  print_al_inf(out, out_round, out_al, key_path, al);


//**************RC5******************
	out << endl << "*************8.RC5*************" << endl;
	al = build_al("RC5");
    print_al_inf(out, out_round, out_al, key_path, al);

//**************SEED******************
	out << endl << "*************9.SEED*************" << endl;
	al = build_al("SEED");
    print_al_inf(out, out_round, out_al, key_path, al);
	
//**************TWOFISH******************
	out << endl << "*************10.TWOFISH*************" << endl;
 	al = build_al("TWOFISH");
    print_al_inf(out, out_round, out_al, key_path, al);		
	
//**************SM4******************
	out << endl << "*************11.SM4*************" << endl;
	al = build_al("SM4");
    print_al_inf(out, out_round, out_al, key_path, al);	
	
//**************RC6******************
	out << endl << "*************12.RC6*************" << endl;
	al = build_al("RC6");
    print_al_inf(out, out_round, out_al, key_path, al);	
	
//**************SERPENT******************
	out << endl << "*************13.SERPENT*************" << endl;
	al = build_al("SERPENT");
    print_al_inf(out, out_round, out_al, key_path, al);	
	
//**************TEA******************
	out << endl << "*************14.TEA*************" << endl;
	al = build_al("TEA");
    print_al_inf(out, out_round, out_al, key_path, al);
	
//**************XTEA******************
	out << endl << "*************15.XTEA*************" << endl;
	al = build_al("XTEA");
    print_al_inf(out, out_round, out_al, key_path, al);
	
//**************SKIPJECT******************
	out << endl << "*************16.SKIPJECT*************" << endl;
	al = build_al("SKIPJECT");
    print_al_inf(out, out_round, out_al, key_path, al);
	
	
	
//***************print mix************
    do_mix(mix,key_path,5000);
	print_mix(mix);
	
	
	
	
	return 0;
	
	
}




