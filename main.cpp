#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

class file {  
    protected:
                ifstream inFile;      
               
    public:    
        file();
        ~file();
        virtual void loop()=0;
};

file::file() {
    inFile.open("dane_obrazki.txt");
    if (!inFile.good())
        {
                cerr << "Blad - pliku nie da sie otworzyc!\n";
                exit(1);
        }
}


file::~file() {
    inFile.close();
}
class ex64
    :public file
{
    
    bool rewers(string scren[20][20]);
    int ykor;
    int xkor;
    int parza();
    int reversecount =0;
    int maxblack =0;
    string image[20][20];
    string pionparz;
    string pozparz;
    int maxblad;
    public:
    virtual void loop();
};
    
void ex64::loop(){
	int good =0;
	int fixable =0;
	int bad = 0;
    string line;
    string buf;
    for(int i=0;i<200;++i){
        for(int j=0;j<20;++j){
            inFile >>line;
            for(int l = 0 ;l<20;++l){
                image[j][l]=line[l];
                
            }
            pionparz+=line[20];
        }
        inFile >>pozparz;
        int ddd = parza();
        //cout<<pozparz <<endl<<pionparz<<endl<<i<<endl;
        pionparz = "";
        /*if(rewers(image)){
            reversecount++;
        }*/
        if(ddd==0){
        	good++;
		}else if(ddd==1){
			cout << "w obrazku"<<i<<"zmienic kordy x:"<<xkor<<"y:"<<ykor<<endl;
			fixable++;
		}else if(ddd>1){
			bad++;
		}
		
        //cout<<ddd<<endl;
    }
    cout<<"ilosc dobrych:"<<good<<endl;
    cout<<"ilosc naprawialnych:"<<fixable<<endl;
    cout<<"ilosc zlych:"<<bad<<endl;
    //cout<<"max zlych:"<<maxblad<<endl;
    //cout<<"ilosc rewersow:"<<reversecount<<endl;
    //cout<<"max czarnych:"<<maxblack<<endl;
}
    bool ex64::rewers(string scren[20][20]){
        int black =0;
        for(int i = 0;i<20;++i){
            for(int j=0;j<20;++j){
                if(scren[i][j]=="1"){
                    ++black;
                }
            }
            if(black>maxblack){
                maxblack=black;
            }
        }
        if(black>(20*20/2)){
            return true;
        }else{
            return false;
        }
    }
	int ex64::parza(){
		int bladpoz=0;
		int bladpion=0;
		int prpi=0;
		int prpz=0;
		for(int i = 0;i<20;++i){
			prpi=0;
			prpz=0;
            for(int j=0;j<20;++j){
                if(image[i][j]=="1")++prpi;
                if(image[j][i]=="1")++prpz;
            }
            if(((prpz%2) == 1 && pozparz[i]=='0')||((prpz%2)== 0 && pozparz[i]=='1')){
        		xkor = i;
				bladpoz++;
			}
            if(((prpi%2) == 1 && pionparz[i]=='0')||((prpi%2)== 0 && pionparz[i]=='1')){
            	ykor = i;
				bladpion++;
			}
        }
        if( bladpoz + bladpion == 0 ) return 0;
        if( bladpoz <= 1 && bladpion <= 1 ) return 1;
    	return bladpoz+bladpion;
		
		
		
		
	}



int main() {
    ex64 kva;
    kva.loop();
    return 0;
}
