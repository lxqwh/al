#ifndef algorithm_define_h
#define algorithm_define_h

#include "graph_t.h"
#include <string>


#define AESX2_ 81    
#define X2A1_  300     
#define BR_    70
#define AND_   20
#define OR_    21
#define NOT_   10
#define XOR_   60
#define LUT_   520
#define MAS_   270
#define SH_    271
#define MM_    900
#define GFM_   800
#define PER_   500




#define IDEA(g)                                                                                           \
	(g).Insertedge(1,2,MM_);    (g).Insertedge(1,3,MAS_);   (g).Insertedge(1,4,MAS_); (g).Insertedge(1,4,MM_);       \
	                                                                                                      \
	(g).Insertedge(2,18,0);     (g).Insertedge(2,6,0);      (g).Insertedge(3,22,0);   (g).Insertedge(3,8,0);        \
	(g).Insertedge(4,6,0);      (g).Insertedge(4,16,0);     (g).Insertedge(5,8,0);    (g).Insertedge(5,20,0);       \
	                                                                                                      \
	(g).Insertedge(6,7,XOR_);    (g).Insertedge(8,9,XOR_);                                                        \
	                                                                                                      \
	(g).Insertedge(7,10,MM_);   (g).Insertedge(9,11,0);                                                        \
	                                                                                                      \
	(g).Insertedge(10,14,0);    (g).Insertedge(10,11,0);                                                       \
	                                                                                                      \
	(g).Insertedge(11,12,MAS_);                                                                              \
	                                                                                                      \
	(g).Insertedge(12,13,MM_);                                                                              \
	                                                                                                      \
	(g).Insertedge(13,18,0) ;   (g).Insertedge(13,14,0);    (g).Insertedge(13,16,0);                              \
	                                                                                                      \
	(g).Insertedge(18,19,XOR_);	(g).Insertedge(14,15,MAS_); (g).Insertedge(16,17,XOR_);                             \
	                                                                                                      \
	(g).Insertedge(15,22,0);    (g).Insertedge(15,20,0);                                                       \
	                                                                                                      \
	(g).Insertedge(22,23,XOR_);  (g).Insertedge(20,21,XOR_); 


#define AES(g)                  \
    (g).Insertedge(1,2,LUT_);      \
	(g).Insertedge(2,3,BR_);      \
	(g).Insertedge(3,4,GFM_);      \
	(g).Insertedge(4,5,XOR_);
	

#define DES(g)                  \
    (g).Insertedge(1,2,PER_);       \
    (g).Insertedge(1,6,0);	    \
	(g).Insertedge(2,3,XOR_);       \
	(g).Insertedge(3,4,LUT_);      \
	(g).Insertedge(4,5,PER_);       \
	(g).Insertedge(5,6,0);	    \
	(g).Insertedge(6,7,XOR_);		
	
	
	
#define BLOWFISH(g)                  \
    (g).Insertedge(1,2,XOR_);       \
	                                                                                      \
	(g).Insertedge(2,3,LUT_);     (g).Insertedge(2,4,LUT_);  (g).Insertedge(2,5,LUT_);    \
	(g).Insertedge(2,6,LUT_);  	                                                          \
	                                                                                      \
    (g).Insertedge(3,7,0);        (g).Insertedge(4,7,0);                                       \
	                                                                                      \
	(g).Insertedge(7,8,MAS_);                                                             \
	                                                                                      \
	(g).Insertedge(8,9,0);        (g).Insertedge(5,9,0);                                    \
	                                                                                      \
	(g).Insertedge(9,10,XOR_);                                                             \
	                                                                                      \
	(g).Insertedge(10,11,0);	  (g).Insertedge(6,11,0);                                 \
	                                                                                      \
	(g).Insertedge(11,12,MAS_);		                                                      \
                                                                                          \
	(g).Insertedge(12,13,0);      (g).Insertedge(1,13,0);                                       \
                                                                                          \
    (g).Insertedge(13,14,XOR_);


#define CAMELLIA(g)                 \
    (g).Insertedge(1,2,XOR_);       \
    (g).Insertedge(2,3,LUT_);       \
	(g).Insertedge(3,4,XOR_);       \
	(g).Insertedge(4,5,XOR_);       \
	(g).Insertedge(5,6,XOR_);       \
	(g).Insertedge(6,7,BR_);       \
	(g).Insertedge(7,8,XOR_);	
	
#define CAST128(g)                  \
    (g).Insertedge(1,2,MAS_);       \
	(g).Insertedge(2,3,SH_);       \
	(g).Insertedge(3,4,LUT_);     (g).Insertedge(3,5,LUT_);  (g).Insertedge(3,6,LUT_);    \
	(g).Insertedge(3,7,LUT_);  	\
    (g).Insertedge(4,8,0);        (g).Insertedge(5,8,0);                                       \
	(g).Insertedge(8,9,XOR_);       \
    (g).Insertedge(9,10,0);       (g).Insertedge(6,10,0);                                       \
	(g).Insertedge(10,11,MAS_);       \
    (g).Insertedge(7,12,0);       (g).Insertedge(11,12,0);                                       \
	(g).Insertedge(12,13,MAS_);       \
	(g).Insertedge(13,14,XOR_);       

#define GOST(g)                  \
    (g).Insertedge(1,2,MAS_);       \
	(g).Insertedge(2,3,LUT_);       \
	(g).Insertedge(3,4,SH_);  \
	(g).Insertedge(4,5,XOR_);       
	
	
	
#define KASUMI(g)                  \
    (g).Insertedge(1,2,MAS_);       \
	(g).Insertedge(2,3,LUT_);       \
	(g).Insertedge(3,4,SH_);  \
	(g).Insertedge(4,5,XOR_);   

#define RC5(g)                  \
    (g).Insertedge(1,2,XOR_);       \
	(g).Insertedge(2,3,SH_);       \
	(g).Insertedge(3,4,MAS_);  

#define SEED(g)                  \
    (g).Insertedge(1,2,XOR_);       \
	(g).Insertedge(1,3,XOR_);       \
	(g).Insertedge(2,4,0);   (g).Insertedge(3,4,0); \
	(g).Insertedge(4,5,XOR_);       \
	(g).Insertedge(5,6,LUT_); \
	(g).Insertedge(6,7,XOR_); \
	(g).Insertedge(7,8,XOR_); \
	(g).Insertedge(8,9,XOR_); \
	(g).Insertedge(9,10,0);  (g).Insertedge(2,10,0); \
	(g).Insertedge(10,11,MAS_); \
	(g).Insertedge(11,12,LUT_); \
	(g).Insertedge(12,13,XOR_); \
	(g).Insertedge(13,14,XOR_); \
	(g).Insertedge(14,15,XOR_); \
	(g).Insertedge(9,16,0);  (g).Insertedge(15,16,0); \
	(g).Insertedge(16,17,MAS_); \
	(g).Insertedge(17,18,LUT_); \
	(g).Insertedge(18,19,XOR_); \
	(g).Insertedge(19,20,XOR_); \
	(g).Insertedge(20,21,XOR_); \
	(g).Insertedge(21,22,0); (g).Insertedge(15,22,0); \
	(g).Insertedge(22,23,MAS_); \
	(g).Insertedge(23,24,XOR_); 
	
#define TWOFISH(g)                  \
    (g).Insertedge(1,2,XOR_);     (g).Insertedge(1,3,XOR_);   (g).Insertedge(1,4,XOR_); (g).Insertedge(1,5,XOR_);       \
	(g).Insertedge(2,6,LUT_);    (g).Insertedge(3,8,SH_); \
	(g).Insertedge(6,7,GFM_); 	 (g).Insertedge(8,9,LUT_); \
	(g).Insertedge(9,10,GFM_); \
	(g).Insertedge(7,11,0); 	 (g).Insertedge(10,11,0); \
	(g).Insertedge(11,12,MAS_); \
	(g).Insertedge(12,13,0); 	 (g).Insertedge(10,13,0); \
	(g).Insertedge(12,15,MAS_);  (g).Insertedge(13,14,MAS_); \
	(g).Insertedge(15,16,0);     (g).Insertedge(4,16,0); \
	(g).Insertedge(14,18,MAS_); \
	(g).Insertedge(16,17,XOR_); \
	(g).Insertedge(18,19,0); 	 (g).Insertedge(5,19,0); \
	(g).Insertedge(19,20,XOR_); 

#define SM4(g)                  \
    (g).Insertedge(1,2,XOR_);     \
	(g).Insertedge(2,3,XOR_);  \
	(g).Insertedge(3,4,LUT_); \
	(g).Insertedge(4,5,SH_); \
	(g).Insertedge(5,6,XOR_); \
	(g).Insertedge(6,7,XOR_); \
	(g).Insertedge(7,8,XOR_); \
	(g).Insertedge(8,9,XOR_); 	

#define RC6(g)                  \
    (g).Insertedge(1,2,X2A1_);      	(g).Insertedge(1,3,X2A1_);       \
	(g).Insertedge(2,4,MM_);       (g).Insertedge(3,5,MM_); \
	(g).Insertedge(4,6,SH_);     	(g).Insertedge(5,7,SH_); \
	(g).Insertedge(6,8,XOR_);    	(g).Insertedge(7,9,XOR_); \
	(g).Insertedge(8,12,0);         (g).Insertedge(7,12,0); (g).Insertedge(9,10,0); (g).Insertedge(6,10,0); \
	(g).Insertedge(12,13,SH_); \
	(g).Insertedge(10,11,SH_); \
	(g).Insertedge(13,14,MAS_); \
	(g).Insertedge(11,15,MAS_); 

#define SERPENT(g)                  \
    (g).Insertedge(1,2,XOR_);         (g).Insertedge(2,3,LUT_);\
    (g).Insertedge(1+2,2+2,SH_);     (g).Insertedge(1+2,3+2,SH_);       \
	(g).Insertedge(2+2,4+2,0);       (g).Insertedge(3+2,4+2,0);     (g).Insertedge(1+2,4+2,0);\
	(g).Insertedge(4+2,5+2,MAS_);       \
	(g).Insertedge(2+2,6+2,SH_); \
	(g).Insertedge(6+2,7+2,0);       (g).Insertedge(3+2,7+2,0);     (g).Insertedge(1+2,7+2,0); \
	(g).Insertedge(5+2,10+2,SH_); \
	(g).Insertedge(7+2,8+2,MAS_); \
	(g).Insertedge(8+2,9+2,SH_); \
	(g).Insertedge(9+2,11+2,0);      (g).Insertedge(10+2,11+2,0);   (g).Insertedge(2+2,11+2,0); \
	(g).Insertedge(11+2,12+2,MAS_); \
	(g).Insertedge(12+2,14+2,SH_); \
	(g).Insertedge(10+2,13+2,SH_); \
	(g).Insertedge(13+2,15+2,0);     (g).Insertedge(9+2,15+2,0);    (g).Insertedge(3+2,15+2,0); \
	(g).Insertedge(15+2,16+2,MAS_); \
    (g).Insertedge(16+2,17+2,SH_); 

#define TEA(g)                  \
    (g).Insertedge(1,2,SH_);        (g).Insertedge(1,3,SH_);\
	(g).Insertedge(1,4,XOR_);        (g).Insertedge(2,5,XOR_); \
	(g).Insertedge(2,6,XOR_);     	(g).Insertedge(4,7,0); \
	(g).Insertedge(6,7,0);       	(g).Insertedge(7,8,MAS_); \
	(g).Insertedge(8,9,0);          (g).Insertedge(5,9,0);  \
	(g).Insertedge(9,10,MAS_); \
	(g).Insertedge(10,11,XOR_); 
	
#define XTEA(g)                  \
    (g).Insertedge(1,2,SH_);        (g).Insertedge(1,3,SH_);\
	(g).Insertedge(2,4,0);          (g).Insertedge(3,4,0); \
	(g).Insertedge(4,5,MAS_);     	(g).Insertedge(5,6,0); \
	(g).Insertedge(1,6,0);       	(g).Insertedge(6,7,XOR_); \
	(g).Insertedge(7,8,0);          (g).Insertedge(1,8,0);  \
	(g).Insertedge(8,9,MAS_); \
	(g).Insertedge(9,10,XOR_); 	

#define SKIPJECT(g)                  \
    (g).Insertedge(1,2,XOR_);        (g).Insertedge(2,3,LUT_);\
	(g).Insertedge(3,4,XOR_);        (g).Insertedge(4,5,XOR_);     	(g).Insertedge(5,6,LUT_); \
    (g).Insertedge(6,7,XOR_); \
	(g).Insertedge(7,8,XOR_);  \
	(g).Insertedge(8,9,LUT_); \
	(g).Insertedge(9,10,XOR_); \
	(g).Insertedge(10,11,XOR_); \
	(g).Insertedge(11,12,LUT_);\
	(g).Insertedge(12,13,XOR_); \
	(g).Insertedge(13,14,XOR_); \
	(g).Insertedge(14,15,XOR_); 


	
	
inline void	init_al_graph(ALGraph<int> &g, std::string al_type){
	if(al_type == "IDEA" ){
		for(int i = 0; i <= 22; i++)
		g.InsertVertex(i+1);
		IDEA(g); 
	}
	else if(al_type == "AES"){
		for(int i = 0; i <= 4; i++){
		g.InsertVertex(i+1);
	    }
		AES(g); 
	}
	else if(al_type == "DES"){  
		for(int i = 0; i <= 6; i++){
		g.InsertVertex(i+1);
	    }
		DES(g);  
	}
	else if(al_type == "BLOWFISH"){  
		for(int i = 0; i <= 13; i++){
		g.InsertVertex(i+1);
	    }
		BLOWFISH(g);  
	}	
	else if(al_type == "CAMELLIA"){  
		for(int i = 0; i <= 7; i++){
		g.InsertVertex(i+1);
	    }
		CAMELLIA(g);  
	}
	else if(al_type == "CAST128"){  
		for(int i = 0; i <= 13; i++){
		g.InsertVertex(i+1);
	    }
		CAST128(g);  
	}	
	else if(al_type == "GOST"){  
		for(int i = 0; i <= 4; i++){
		g.InsertVertex(i+1);
	    }
		GOST(g);  
	}	
	else if(al_type == "KASUMI"){  
		for(int i = 0; i <= 4; i++){
		g.InsertVertex(i+1);
	    }
		KASUMI(g);  
	}		
	else if(al_type == "RC5"){  
		for(int i = 0; i <= 3; i++){
		g.InsertVertex(i+1);
	    }
		RC5(g);  
	}		
	else if(al_type == "SEED"){  
		for(int i = 0; i <= 23; i++){
		g.InsertVertex(i+1);
	    }
		SEED(g);  
	}	
	else if(al_type == "TWOFISH"){  
		for(int i = 1; i <= 20; i++){
		g.InsertVertex(i);
	    }
		TWOFISH(g);  
	}	
	else if(al_type == "SM4"){  
		for(int i = 1; i <= 9; i++){
		g.InsertVertex(i);
	    }
		SM4(g);  
	}	
	else if(al_type == "RC6"){  
		for(int i = 1; i <= 15; i++){
		g.InsertVertex(i);
	    }
		RC6(g);  
	}	
	else if(al_type == "SERPENT"){  
		for(int i = 1; i <= 19; i++){
		g.InsertVertex(i);
	    }
		SERPENT(g);  
	}	
	else if(al_type == "TEA"){  
		for(int i = 1; i <= 11; i++){
		g.InsertVertex(i);
	    }
		TEA(g);  
	}	
	else if(al_type == "XTEA"){  
		for(int i = 1; i <= 10; i++){
		g.InsertVertex(i);
	    }
		XTEA(g);  
	}	
	else if(al_type == "SKIPJECT"){  
		for(int i = 1; i <= 15; i++){
		g.InsertVertex(i);
	    }
		SKIPJECT(g);  
	}
	
}





#endif

