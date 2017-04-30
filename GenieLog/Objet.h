#include <cstring>
#include <iostream>
using namespace std;

#ifndef OBJET
#define OBJET

class Objet {
    
  private:  
    string m_Nom;
    int m_type;
    int m_pv;
    int m_mana;
    
  public:
    
   Objet();
   ~Objet();
    
    
};

#endif
