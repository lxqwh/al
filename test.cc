#include "graph_t.h"
#include "algorithm_define.h"
#include "al_base.h"
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <deque>
#include <vector>
#include <algorithm>


#define NO_SINGLE  0 //0：包含单个 1：不包含单个
#define LEN 4    //最长的组合（2-5）
#define TYPE 1   //0:所有组合 1：去除特殊单元级联 2：只有抑或



using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::string;
using std::set;
using std::pair;
using std::map;
using std::multimap;

std::ofstream out("output");
std::ofstream out_round("data_in_round");
std::ofstream out_al("data_in_al");
std::map<string, set<int>> mix = std::map<string, set<int>>();
vector<deque<al_protocol::element>> key_path = vector<deque<al_protocol::element>>();
vector<string> al_str = {"AES","DES","IDEA","BLOWFISH","CAMELLIA","CAST128","GOST","RC5","SEED","TWOFISH",
                         "SM4","RC6","SERPENT","TEA","XTEA","SKIPJECT"};

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
	case 270:    out<<"MAS"; break;
	case 271:    out<<"SH"; break;
	case 900:    out<<"MM"; break;
	case 800:    out<<"GFM"; break;
	case 500:    out<<"SUB"; break;
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

//***********************************
//算子组合
//***********************************

bool isspecial(al_protocol::element in){
	switch(in){
	case al_protocol::X2A1:   return true;
	case al_protocol::AESX2:  return true;
	case al_protocol::LUT:    return true;
	case al_protocol::MM:     return true;
	case al_protocol::GFM:    return true;
	default:                  return false;
	}
}

void mix_temp(std::map<string, set<int>> &mix,deque<al_protocol::element> &de, int delay, int al, int type=0){
	int i = de.size();
	string s = string();
	int c_delay = 0;
	bool go = false;
	bool sp = false;
	while(i-- >0){
		for(size_t j=0;j<de.size();j++){
			c_delay += int(de[j]);
			
			
			if(type==0) go = (j>=LEN)?false:c_delay <= delay;
			else if(type==1){
				if(isspecial(de[j])){
					if(sp) go=false;
				    else{
						sp=true;
						go = (j>=LEN)?false:c_delay <= delay;
					}
				}		
				else
					go = (j>=LEN)?false:c_delay <= delay;
			}
			else if(type==2){
				if(de[j]!=al_protocol::XOR)
					go=false;
				else
					go=c_delay <= delay;
			}
			else {
				out<<"error:错误的type..."<<endl;
				go = false;
			}
			
			if(go){
				s = s + element_to_string(de[j]) + " ";
				mix[s + "| the delay is: " + std::to_string(c_delay/1000.0) + " ns"].insert(al);
			}
			else
				break;
		}
		sp=false;
		s.clear();
		c_delay = 0;
		de.push_back(*(de.begin()));//头入尾
		de.pop_front();//头出队，成环
	}
}


void do_mix(std::map<string, set<int>> &mix, vector<deque<al_protocol::element>> &key_path, int delay){
	for(unsigned i = 0; i<key_path.size(); i++){
		mix_temp(mix,key_path[i], delay, i, TYPE);
	}
}

void print_mix(std::map<string, set<int>> &mix){
	for (std::map<string, set<int>>::iterator i = mix.begin(); i != mix.end(); i++){
#if NO_SINGLE
	    if(i->second.size()==1) continue;
#endif
		out << "组合类型: " << i->first << endl;
		out << "算法个数: " << i->second.size() << " 分别是：" << endl;
		for (int j : i->second)
			out << al_str[j] << " ";
		out << endl;	

	}
}

void print_center(std::map<string, set<int>> &mix, string center){
	std::multimap<int, std::map<string, set<int>>::iterator> sorted;
	for (std::map<string, set<int>>::iterator i = mix.begin(); i != mix.end(); i++){
		if((i->first).find(center)!=string::npos){
#if NO_SINGLE
    	    if(i->second.size()==1) continue;
#endif
            sorted.insert(std::make_pair(i->second.size(),i));
    	}
		else continue;
	}
	std::multimap<int,std::map<string, set<int>>::iterator>::iterator beg=sorted.begin();
	while(beg!=sorted.end()){
		out << "组合类型: " << beg->second->first << endl;
		out << "算法个数: " << beg->second->second.size() << " 分别是：" << endl;
		for (int j : beg->second->second)
			out << al_str[j] << " ";
		out << endl;	
        ++beg;		
	}
}

void print_center_pre(std::map<string, set<int>> &mix, string center) {
	std::multimap<int, std::map<string, set<int>>::iterator> sorted;
	int s_size = center.size();
	for (std::map<string, set<int>>::iterator i = mix.begin(); i != mix.end(); i++) {
		//if (i->first.substr(0,s_size)==center) 
		if(i->first.find(center)==0){
#if NO_SINGLE
			if (i->second.size() == 1) continue;
#endif
			sorted.insert(std::make_pair(i->second.size(), i));
		}
		else continue;
	}
	std::multimap<int, std::map<string, set<int>>::iterator>::iterator beg = sorted.begin();
	while (beg != sorted.end()) {
		out << "组合类型: " << beg->second->first << endl;
		out << "算法个数: " << beg->second->second.size() << " 分别是：" << endl;
		for (int j : beg->second->second)
			out << al_str[j] << " ";
		out << endl;
		++beg;
	}
}

void print_center_post(std::map<string, set<int>> &mix, string center) {
	std::multimap<int, std::map<string, set<int>>::iterator> sorted;
	int s_size = center.size();
	for (std::map<string, set<int>>::iterator i = mix.begin(); i != mix.end(); i++) {
		//if ((i->first.size() - int(s_size) - 28) < 0) continue;
		//if (i->first.substr(i->first.size() - s_size - 28, s_size) == center) 
		if(i->first[i->first.rfind(center)+s_size+1]=='|'){
#if NO_SINGLE
			if (i->second.size() == 1) continue;
#endif
			sorted.insert(std::make_pair(i->second.size(), i));
		}
		else continue;
	}
	std::multimap<int, std::map<string, set<int>>::iterator>::iterator beg = sorted.begin();
	while (beg != sorted.end()) {
		out << "组合类型: " << beg->second->first << endl;
		out << "算法个数: " << beg->second->second.size() << " 分别是：" << endl;
		for (int j : beg->second->second)
			out << al_str[j] << " ";
		out << endl;
		++beg;
	}
}
void print_center(void(*ptr)(std::map<string, set<int>> &mix, string center)){
	out << endl << endl << "***********SH*********" << endl;
	ptr(mix, "SH");
	out << endl << endl << "***********MAS*********" << endl;
	ptr(mix, "MAS");
	out << endl << endl << "***********MM*********" << endl;
	ptr(mix, "MM");
	out << endl << endl << "***********LUT*********" << endl;
	ptr(mix, "LUT");
	out << endl << endl << "***********GFM*********" << endl;
	ptr(mix, "GFM");
	out << endl << endl << "***********SUB*********" << endl;
	ptr(mix, "SUB");
	out << endl << endl << "***********BR*********" << endl;
	ptr(mix, "BR");
}
void print_center() {
	out << endl << endl << "***********SH*********" << endl;
	print_center(mix, "SH");
	out << endl << endl << "***********MAS*********" << endl;
	print_center(mix, "MAS");
	out << endl << endl << "***********MM*********" << endl;
	print_center(mix, "MM");
	out << endl << endl << "***********LUT*********" << endl;
	print_center(mix, "LUT");
	out << endl << endl << "***********GFM*********" << endl;
	print_center(mix, "GFM");
	out << endl << endl << "***********SUB*********" << endl;
	print_center(mix, "SUB");
	out << endl << endl << "***********BR*********" << endl;
	print_center(mix, "BR");
}
void print_center_pre() {
	out << endl << endl << "***********SH*********" << endl;
	print_center_pre(mix, "SH");
	out << endl << endl << "***********MAS*********" << endl;
	print_center_pre(mix, "MAS");
	out << endl << endl << "***********MM*********" << endl;
	print_center_pre(mix, "MM");
	out << endl << endl << "***********LUT*********" << endl;
	print_center_pre(mix, "LUT");
	out << endl << endl << "***********GFM*********" << endl;
	print_center_pre(mix, "GFM");
	out << endl << endl << "***********SUB*********" << endl;
	print_center_pre(mix, "SUB");
	out << endl << endl << "***********BR*********" << endl;
	print_center_pre(mix, "BR");
}

void print_center_post() {
	out << endl << endl << "***********SH*********" << endl;
	print_center_post(mix, "SH");
	out << endl << endl << "***********MAS*********" << endl;
	print_center_post(mix, "MAS");
	out << endl << endl << "***********MM*********" << endl;
	print_center_post(mix, "MM");
	out << endl << endl << "***********LUT*********" << endl;
	print_center_post(mix, "LUT");
	out << endl << endl << "***********GFM*********" << endl;
	print_center_post(mix, "GFM");
	out << endl << endl << "***********SUB*********" << endl;
	print_center_post(mix, "SUB");
	out << endl << endl << "***********BR*********" << endl;
	print_center_post(mix, "BR");
}

//**********************************
//中心算子的合理前后缀
//特殊算子：1.找到第一个，往前后扩展（有效范围内：左（起点或者上一次的匹配点（不允许两个同时出现）），往后扩展（末尾，下一个匹配点）；到末尾结束）
//sh\mas\等：跳过特殊算子：记录哪些是特殊算子
//**********************************


//**********************************
//逻辑组合的选择
//
//**********************************







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
//input for k-means
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
    do_mix(mix,key_path,1000);
	print_mix(mix);
	print_center(print_center_pre);
	print_center(print_center_post);


	return 0;
	
	
}




