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

//**************CAST128******************
	out << endl << "*************CAST128*************" << endl;
    vector<al_protocol::element> ie_cast128 = {al_protocol::BL, al_protocol::SH,
	                                           al_protocol::LUT, al_protocol::MAS};
	al_base cast128(16,32,14,ie_cast128);
	cast128.init_graph(init_al_graph,"CAST128");
	std::vector<al_protocol::element> cast128_r;
	int cast128_delay;
	cast128.key_path(cast128_r,cast128_delay);
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
	out << endl << "*************GOST*************" << endl;
    vector<al_protocol::element> ie_gost = {al_protocol::BL, al_protocol::SH,
	                                           al_protocol::LUT, al_protocol::MAS};
	al_base gost(32,32,5,ie_gost);
	gost.init_graph(init_al_graph,"GOST");
	std::vector<al_protocol::element> gost_r;
	int gost_delay;
	gost.key_path(gost_r,gost_delay);
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
	out << endl << "*************RC5*************" << endl;
    vector<al_protocol::element> ie_rc5 = {al_protocol::BL, al_protocol::SH,
	                                       al_protocol::MAS};
	al_base rc5(24,32,4,ie_rc5);
	rc5.init_graph(init_al_graph,"RC5");
	std::vector<al_protocol::element> rc5_r;
	int rc5_delay;
	rc5.key_path(rc5_r,rc5_delay);
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
	out << endl << "*************SEED*************" << endl;
    vector<al_protocol::element> ie_seed = {al_protocol::BL, al_protocol::LUT,
	                                       al_protocol::MAS};
	al_base seed(16,32,24,ie_seed);
	seed.init_graph(init_al_graph,"SEED");
	std::vector<al_protocol::element> seed_r;
	int seed_delay;
	seed.key_path(seed_r,seed_delay);
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
	out << endl << "*************TWOFISH*************" << endl;
    vector<al_protocol::element> ie_twofish = {al_protocol::BL, al_protocol::LUT,
	                                           al_protocol::GFM, al_protocol::MAS,
											   al_protocol::SH};
	al_base twofish(16,32,20,ie_twofish);
	twofish.init_graph(init_al_graph,"TWOFISH");
	std::vector<al_protocol::element> twofish_r;
	int twofish_delay;
	twofish.key_path(twofish_r,twofish_delay);
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
	out << endl << "*************SM4*************" << endl;
    vector<al_protocol::element> ie_sm4 = {al_protocol::BL, al_protocol::LUT,
											   al_protocol::SH};
	al_base sm4(32,32,9,ie_sm4);
	sm4.init_graph(init_al_graph,"SM4");
	std::vector<al_protocol::element> sm4_r;
	int sm4_delay;
	sm4.key_path(sm4_r,sm4_delay);
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
	out << endl << "*************RC6*************" << endl;
    vector<al_protocol::element> ie_rc6 = {al_protocol::MAS, al_protocol::LUT,
											   al_protocol::SH, al_protocol::BL};
	al_base rc6(20,32,15,ie_rc6);
	rc6.init_graph(init_al_graph,"RC6");
	std::vector<al_protocol::element> rc6_r;
	int rc6_delay;
	rc6.key_path(rc6_r,rc6_delay);
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
	out << endl << "*************SERPENT*************" << endl;
    vector<al_protocol::element> ie_serpent = {al_protocol::SH, al_protocol::BL, al_protocol::MAS, al_protocol::LUT};
	al_base serpent(32,32,19,ie_serpent);
	serpent.init_graph(init_al_graph,"SERPENT");
	std::vector<al_protocol::element> serpent_r;
	int serpent_delay;
	serpent.key_path(serpent_r,serpent_delay);
	out<<"the critical path of serpent is:"<<endl;
	for(al_protocol::element i:serpent_r){
		print_element(i);
		out<<" -> "<<endl;		
	}
	out<<"the total delay of a round is :"<<serpent_delay/100.0<<"ns"<<endl;	
	al_protocol::element serpent_maxe;
	serpent.max_delay_element(serpent_maxe);
	out<<"the max_delay_element is :"<<serpent_maxe/100.0<<"ns"<<endl;	

	
	return 0;
	
}




