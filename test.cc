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

std::ofstream out("output.txt");
std::map<string, set<int>> mix = std::map<string, set<int>>();
vector<deque<al_protocol::element>> key_path = vector<deque<al_protocol::element>>();


void print_element(int i){
	switch(i){
	case 30:     out<<"logic"; break;
	case 163:    out<<"LUT"; break;
	case 356:    out<<"Modular add or sub "; break;
	case 164:    out<<"Shift"; break;
	case 462:    out<<"Modular Multiplication"; break;
	case 422:    out<<"GF Multiplication"; break;
	case 60:     out<<"substitution"; break;
	default:     out<<"error element,the delay is:"<<i<<endl; break;
	}
}
string element_to_string (al_protocol::element i){
	switch(i){
	case al_protocol::BL:     return "BL";
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
				mix[s + "| the delay is: " + std::to_string(c_delay/100.0) + " ns"].insert(al);
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




int main(){


//*************AES******************	
	out << "*************1.AES***************" << endl;
	vector<al_protocol::element> ie_aes = {al_protocol::LUT,al_protocol::SH,
	                                       al_protocol::GFM,al_protocol::BL};
	//al_base aes = al_base(10, 32, 5, ie_aes);//初始化还是赋值，这里是调用拷贝初始化？？？？
	al_base aes(10, 32, 5, ie_aes);
	aes.init_graph(init_al_graph,"AES");
	std::vector<al_protocol::element> aes_r;
	int aes_delay;
	aes.key_path(aes_r,aes_delay);
	key_path.push_back(deque<al_protocol::element>(aes_r.begin(),aes_r.end()));	
	
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
	out << endl<<"*************2.DES****************" << endl;
    vector<al_protocol::element> ie_des = {al_protocol::SUB, al_protocol::BL,
	                                       al_protocol::LUT};
	al_base des(16,32,7,ie_des);
	des.init_graph(init_al_graph,"DES");
	std::vector<al_protocol::element> des_r;
	int des_delay;
	des.key_path(des_r,des_delay);
	key_path.push_back(deque<al_protocol::element>(des_r.begin(),des_r.end()));	
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
	out << endl << "*************3.IDEA*************" << endl;
    vector<al_protocol::element> ie_idea = {al_protocol::MM, al_protocol::MAS,
	                                        al_protocol::BL};
	al_base idea(8,16,23,ie_idea);
	idea.init_graph(init_al_graph,"IDEA");
	std::vector<al_protocol::element> idea_r;
	int idea_delay;
	idea.key_path(idea_r,idea_delay);
	key_path.push_back(deque<al_protocol::element>(idea_r.begin(),idea_r.end()));	
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
	out << endl << "*************4.BLOWFISH*************" << endl;
    vector<al_protocol::element> ie_blowfish = {al_protocol::LUT, al_protocol::BL,
	                                        al_protocol::MAS};
	al_base blowfish(16,32,14,ie_blowfish);
	blowfish.init_graph(init_al_graph,"BLOWFISH");
	std::vector<al_protocol::element> blowfish_r;
	int blowfish_delay;
	blowfish.key_path(blowfish_r,blowfish_delay);
	key_path.push_back(deque<al_protocol::element>(blowfish_r.begin(),blowfish_r.end()));	
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
	out << endl << "*************5.CAMELLIA*************" << endl;
    vector<al_protocol::element> ie_camellia = {al_protocol::LUT, al_protocol::BL,
	                                            al_protocol::SUB};
	al_base camellia(18,8,8,ie_camellia);
	camellia.init_graph(init_al_graph,"CAMELLIA");
	std::vector<al_protocol::element> camellia_r;
	int camellia_delay;
	camellia.key_path(camellia_r,camellia_delay);
	key_path.push_back(deque<al_protocol::element>(camellia_r.begin(),camellia_r.end()));	
	out<<"the critical path of camellia is:"<<endl;
	for(al_protocol::element i:camellia_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<camellia_delay/100.0<<"ns"<<endl;	
	al_protocol::element camellia_maxe;
	camellia.max_delay_element(camellia_maxe);
	out<<"the max_delay_element is :"<<camellia_maxe/100.0<<"ns"<<endl;		

//**************CAST128******************
	out << endl << "*************6.CAST128*************" << endl;
    vector<al_protocol::element> ie_cast128 = {al_protocol::BL, al_protocol::SH,
	                                           al_protocol::LUT, al_protocol::MAS};
	al_base cast128(16,32,14,ie_cast128);
	cast128.init_graph(init_al_graph,"CAST128");
	std::vector<al_protocol::element> cast128_r;
	int cast128_delay;
	cast128.key_path(cast128_r,cast128_delay);
	key_path.push_back(deque<al_protocol::element>(cast128_r.begin(),cast128_r.end()));	
	out<<"the critical path of cast128 is:"<<endl;
	for(al_protocol::element i:cast128_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<cast128_delay/100.0<<"ns"<<endl;	
	al_protocol::element cast128_maxe;
	cast128.max_delay_element(cast128_maxe);
	out<<"the max_delay_element is :"<<cast128_maxe/100.0<<"ns"<<endl;		

	
//**************GOST******************
	out << endl << "*************7.GOST*************" << endl;
    vector<al_protocol::element> ie_gost = {al_protocol::BL, al_protocol::SH,
	                                           al_protocol::LUT, al_protocol::MAS};
	al_base gost(32,32,5,ie_gost);
	gost.init_graph(init_al_graph,"GOST");
	std::vector<al_protocol::element> gost_r;
	int gost_delay;
	gost.key_path(gost_r,gost_delay);
	key_path.push_back(deque<al_protocol::element>(gost_r.begin(),gost_r.end()));	
	out<<"the critical path of gost is:"<<endl;
	for(al_protocol::element i:gost_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<gost_delay/100.0<<"ns"<<endl;	
	al_protocol::element gost_maxe;
	gost.max_delay_element(gost_maxe);
	out<<"the max_delay_element is :"<<gost_maxe/100.0<<"ns"<<endl;	
	
/*	
//**************KASUMI******************
	out << endl << "*************KASUMI*************" << endl;
    vector<al_protocol::element> ie_kasumi = {al_protocol::BL, al_protocol::SH,
	                                           al_protocol::LUT, al_protocol::MAS};
	al_base kasumi(32,32,5,ie_kasumi);
	kasumi.init_graph(init_al_graph,"KASUMI");
	std::vector<al_protocol::element> kasumi_r;
	int kasumi_delay;
	kasumi.key_path(kasumi_r,kasumi_delay);
	out<<"the critical path of kasumi is:"<<endl;
	for(al_protocol::element i:kasumi_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<kasumi_delay/100.0<<"ns"<<endl;	
	al_protocol::element kasumi_maxe;
	kasumi.max_delay_element(kasumi_maxe);
	out<<"the max_delay_element is :"<<kasumi_maxe/100.0<<"ns"<<endl;		
*/


//**************RC5******************
	out << endl << "*************8.RC5*************" << endl;
    vector<al_protocol::element> ie_rc5 = {al_protocol::BL, al_protocol::SH,
	                                       al_protocol::MAS};
	al_base rc5(24,32,4,ie_rc5);
	rc5.init_graph(init_al_graph,"RC5");
	std::vector<al_protocol::element> rc5_r;
	int rc5_delay;
	rc5.key_path(rc5_r,rc5_delay);
	key_path.push_back(deque<al_protocol::element>(rc5_r.begin(),rc5_r.end()));
	out<<"the critical path of rc5 is:"<<endl;
	for(al_protocol::element i:rc5_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<rc5_delay/100.0<<"ns"<<endl;	
	al_protocol::element rc5_maxe;
	rc5.max_delay_element(rc5_maxe);
	out<<"the max_delay_element is :"<<rc5_maxe/100.0<<"ns"<<endl;	

//**************SEED******************
	out << endl << "*************9.SEED*************" << endl;
    vector<al_protocol::element> ie_seed = {al_protocol::BL, al_protocol::LUT,
	                                       al_protocol::MAS};
	al_base seed(16,32,24,ie_seed);
	seed.init_graph(init_al_graph,"SEED");
	std::vector<al_protocol::element> seed_r;
	int seed_delay;
	seed.key_path(seed_r,seed_delay);
	key_path.push_back(deque<al_protocol::element>(seed_r.begin(),seed_r.end()));
	out<<"the critical path of seed is:"<<endl;
	for(al_protocol::element i:seed_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<seed_delay/100.0<<"ns"<<endl;	
	al_protocol::element seed_maxe;
	seed.max_delay_element(seed_maxe);
	out<<"the max_delay_element is :"<<seed_maxe/100.0<<"ns"<<endl;		
	
//**************TWOFISH******************
	out << endl << "*************10.TWOFISH*************" << endl;
    vector<al_protocol::element> ie_twofish = {al_protocol::BL, al_protocol::LUT,
	                                           al_protocol::GFM, al_protocol::MAS,
											   al_protocol::SH};
	al_base twofish(16,32,20,ie_twofish);
	twofish.init_graph(init_al_graph,"TWOFISH");
	std::vector<al_protocol::element> twofish_r;
	int twofish_delay;
	twofish.key_path(twofish_r,twofish_delay);
	key_path.push_back(deque<al_protocol::element>(twofish_r.begin(),twofish_r.end()));
	out<<"the critical path of twofish is:"<<endl;
	for(al_protocol::element i:twofish_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<twofish_delay/100.0<<"ns"<<endl;	
	al_protocol::element twofish_maxe;
	twofish.max_delay_element(twofish_maxe);
	out<<"the max_delay_element is :"<<twofish_maxe/100.0<<"ns"<<endl;		
	
//**************SM4******************
	out << endl << "*************11.SM4*************" << endl;
    vector<al_protocol::element> ie_sm4 = {al_protocol::BL, al_protocol::LUT,
											   al_protocol::SH};
	al_base sm4(32,32,9,ie_sm4);
	sm4.init_graph(init_al_graph,"SM4");
	std::vector<al_protocol::element> sm4_r;
	int sm4_delay;
	sm4.key_path(sm4_r,sm4_delay);
	key_path.push_back(deque<al_protocol::element>(sm4_r.begin(),sm4_r.end()));
	out<<"the critical path of sm4 is:"<<endl;
	for(al_protocol::element i:sm4_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<sm4_delay/100.0<<"ns"<<endl;	
	al_protocol::element sm4_maxe;
	sm4.max_delay_element(sm4_maxe);
	out<<"the max_delay_element is :"<<sm4_maxe/100.0<<"ns"<<endl;		
	
//**************RC6******************
	out << endl << "*************12.RC6*************" << endl;
    vector<al_protocol::element> ie_rc6 = {al_protocol::MAS, al_protocol::LUT,
											   al_protocol::SH, al_protocol::BL};
	al_base rc6(20,32,15,ie_rc6);
	rc6.init_graph(init_al_graph,"RC6");
	std::vector<al_protocol::element> rc6_r;
	int rc6_delay;
	rc6.key_path(rc6_r,rc6_delay);
	key_path.push_back(deque<al_protocol::element>(rc6_r.begin(),rc6_r.end()));
	out<<"the critical path of rc6 is:"<<endl;
	for(al_protocol::element i:rc6_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<rc6_delay/100.0<<"ns"<<endl;	
	al_protocol::element rc6_maxe;
	rc6.max_delay_element(rc6_maxe);
	out<<"the max_delay_element is :"<<rc6_maxe/100.0<<"ns"<<endl;		
	
//**************SERPENT******************
	out << endl << "*************13.SERPENT*************" << endl;
    vector<al_protocol::element> ie_serpent = {al_protocol::SH, al_protocol::BL, al_protocol::MAS, al_protocol::LUT};
	al_base serpent(32,32,19,ie_serpent);
	serpent.init_graph(init_al_graph,"SERPENT");
	std::vector<al_protocol::element> serpent_r;
	int serpent_delay;
	serpent.key_path(serpent_r,serpent_delay);
	key_path.push_back(deque<al_protocol::element>(serpent_r.begin(),serpent_r.end()));
	out<<"the critical path of serpent is:"<<endl;
	for(al_protocol::element i:serpent_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<serpent_delay/100.0<<"ns"<<endl;	
	al_protocol::element serpent_maxe;
	serpent.max_delay_element(serpent_maxe);
	out<<"the max_delay_element is :"<<serpent_maxe/100.0<<"ns"<<endl;	
	
//**************TEA******************
	out << endl << "*************14.TEA*************" << endl;
    vector<al_protocol::element> ie_tea = {al_protocol::BL, al_protocol::SH,
	                                       al_protocol::MAS};
	al_base tea(32,32,11,ie_tea);
	tea.init_graph(init_al_graph,"TEA");
	std::vector<al_protocol::element> tea_r;
	int tea_delay;
	tea.key_path(tea_r,tea_delay);
	out<<"the critical path of tea is:"<<endl;
	for(al_protocol::element i:tea_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<tea_delay/100.0<<"ns"<<endl;	
	al_protocol::element tea_maxe;
	tea.max_delay_element(tea_maxe);
	out<<"the max_delay_element is :"<<tea_maxe/100.0<<"ns"<<endl;
	
//**************XTEA******************
	out << endl << "*************15.XTEA*************" << endl;
    vector<al_protocol::element> ie_xtea = {al_protocol::BL, al_protocol::SH,
	                                       al_protocol::MAS};
	al_base xtea(32,32,10,ie_xtea);
	xtea.init_graph(init_al_graph,"XTEA");
	std::vector<al_protocol::element> xtea_r;
	int xtea_delay;
	xtea.key_path(xtea_r,xtea_delay);
	out<<"the critical path of xtea is:"<<endl;
	for(al_protocol::element i:xtea_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<xtea_delay/100.0<<"ns"<<endl;	
	al_protocol::element xtea_maxe;
	xtea.max_delay_element(xtea_maxe);
	out<<"the max_delay_element is :"<<xtea_maxe/100.0<<"ns"<<endl;	
	
//**************SKIPJECT******************
	out << endl << "*************16.SKIPJECT*************" << endl;
    vector<al_protocol::element> ie_skipject = {al_protocol::BL, al_protocol::LUT};
	al_base skipject(32,8,15,ie_skipject);
	skipject.init_graph(init_al_graph,"SKIPJECT");
	std::vector<al_protocol::element> skipject_r;
	int skipject_delay;
	skipject.key_path(skipject_r,skipject_delay);
	out<<"the critical path of skipject is:"<<endl;
	for(al_protocol::element i:skipject_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<skipject_delay/100.0<<"ns"<<endl;	
	al_protocol::element skipject_maxe;
	skipject.max_delay_element(skipject_maxe);
	out<<"the max_delay_element is :"<<skipject_maxe/100.0<<"ns"<<endl;	
	
	
	
//***************print mix************
    do_mix(mix,key_path,1000);
	print_mix(mix);
	
	
	
	
	return 0;
	
	
}




