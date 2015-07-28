#ifndef algorithm_define_h
#define algorithm_define_h

#include "graph_t.h"
#include <string>


#define BL_ 30
#define LUT_ 163
#define MAS_ 356
#define SH_ 164
#define MM_ 462
#define GFM_ 422
#define SUB_ 60




#define IDEA(g)                                                                                           \
	(g).Insertedge(1,2,MM_);   (g).Insertedge(1,3,MAS_);   (g).Insertedge(1,4,MAS_); (g).Insertedge(1,4,MM_);       \
	                                                                                                      \
	(g).Insertedge(2,18,0);    (g).Insertedge(2,6,0);     (g).Insertedge(3,22,0);   (g).Insertedge(3,8,0);        \
	(g).Insertedge(4,6,0);     (g).Insertedge(4,16,0);    (g).Insertedge(5,8,0);    (g).Insertedge(5,20,0);       \
	                                                                                                      \
	(g).Insertedge(6,7,BL_);    (g).Insertedge(8,9,BL_);                                                        \
	                                                                                                      \
	(g).Insertedge(7,10,MM_);  (g).Insertedge(9,11,0);                                                        \
	                                                                                                      \
	(g).Insertedge(10,14,0);   (g).Insertedge(10,11,0);                                                       \
	                                                                                                      \
	(g).Insertedge(11,12,MAS_);                                                                              \
	                                                                                                      \
	(g).Insertedge(12,13,MM_);                                                                              \
	                                                                                                      \
	(g).Insertedge(13,18,0) ;  (g).Insertedge(13,14,0);   (g).Insertedge(13,16,0);                              \
	                                                                                                      \
	(g).Insertedge(18,19,BL_);	 (g).Insertedge(14,15,MAS_); (g).Insertedge(16,17,BL_);                             \
	                                                                                                      \
	(g).Insertedge(15,22,0);   (g).Insertedge(15,20,0);                                                       \
	                                                                                                      \
	(g).Insertedge(22,23,BL_);  (g).Insertedge(20,21,BL_); 


#define AES(g)                  \
    (g).Insertedge(1,2,LUT_);      \
	(g).Insertedge(2,3,SH_);      \
	(g).Insertedge(3,4,GFM_);      \
	(g).Insertedge(4,5,BL_);
	

#define DES(g)                  \
    (g).Insertedge(1,2,SUB_);       \
    (g).Insertedge(1,6,0);	    \
	(g).Insertedge(2,3,BL_);       \
	(g).Insertedge(3,4,LUT_);      \
	(g).Insertedge(4,5,SUB_);       \
	(g).Insertedge(5,6,0);	    \
	(g).Insertedge(6,7,BL_);		
	
	
	
#define BLOWFISH(g)                  \
    (g).Insertedge(1,2,BL_);       \
	                                                                                      \
	(g).Insertedge(2,3,LUT_);     (g).Insertedge(2,4,LUT_);  (g).Insertedge(2,5,LUT_);    \
	(g).Insertedge(2,6,LUT_);  	                                                          \
	                                                                                      \
    (g).Insertedge(3,7,0);   (g).Insertedge(4,7,0);                                       \
	                                                                                      \
	(g).Insertedge(7,8,MAS_);                                                             \
	                                                                                      \
	(g).Insertedge(8,9,0);      (g).Insertedge(5,9,0);                                    \
	                                                                                      \
	(g).Insertedge(9,10,BL_);                                                             \
	                                                                                      \
	(g).Insertedge(10,11,0);	  (g).Insertedge(6,11,0);                                 \
	                                                                                      \
	(g).Insertedge(11,12,MAS_);		                                                      \
                                                                                          \
	(g).Insertedge(12,13,0);(g).Insertedge(1,13,0);                                       \
                                                                                          \
    (g).Insertedge(13,14,BL_);


#define CAMELLIA(g)                  \
    (g).Insertedge(1,2,LUT_);       \
	(g).Insertedge(2,3,BL_);       \
	(g).Insertedge(3,4,BL_);       \
	(g).Insertedge(4,5,BL_);       \
	(g).Insertedge(5,6,BL_);       \
	(g).Insertedge(6,7,SUB_);       \
	(g).Insertedge(7,8,BL_);	
	

	
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
}





#endif

