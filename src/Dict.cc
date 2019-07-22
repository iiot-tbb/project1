#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <sstream>
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::map;
using std::vector;
using std::set;
using std::ostringstream;
using std::istringstream;
using namespace std;
//using namespace std;
class Dictionary{

public:
    void read(const string &filename);
    void store(const string &filename);
    void trans(const string &filename){
        string line;
        fstream  fs;
        ifstream is;
        fs.open("../data/Eng.txt",std::ios::out);
        is.open(filename);
        while(std::getline(is,line)){
            for(size_t i=0;i<line.size();i++){
                if(line[i]<='Z'&&line[i]>='A'){
                    line[i]='a'+line[i]-'A';
                }else if((line[i]<='z'&&line[i]>='a')||line[i]=='\n'){

                }else{
                    line[i]=' ';
                }
            }
            fs<<line<<endl;;
        
        }
        fs.close();
        is.close();
    }

    int getSize(){
        return dict.size();
    }
private:
    string word;
    map<string,int> dict;
    vector<pair<string,int>> _sto; //用这个存储词典
    unordered_map<string,set<int>> _index;//索引,在store里进行存储
};
void Dictionary::read(const string &filename){
    ifstream ifs;
    ifs.open(filename,std::ios::in);
    while(ifs.good()&&!ifs.eof()){
        ifs>>word;
        dict[word]++;
   //     cout<<"the word is "<<word<<endl;;
    }
    ifs.close();
}
void Dictionary::store(const string &filename){
    ofstream ofs;
    string line;
    ofs.open(filename,std::ios::out);
    ostringstream oss;
    map<string,int>::iterator it=dict.begin();
    int i=0;
    while(it!=dict.end()&&i<12567){
    
        oss <<it->first<<"  "<<it->second<<"\n";
        line=oss.str();
        oss.clear();
        oss.str("");
        ofs<<line;
        line="";
        _sto.push_back(make_pair(it->first,it->second));
        it++;
        i++;
    }
    for(size_t o=0;o<_sto.size();o++){
            string tp =_sto[o].first;
        for(size_t k=0;k<tp.size();k++){
            string s;
            s=tp[k];
            _index[s].insert(o);
        }
    }
    ofstream ofs2;
    ofs2.open("../data/index.txt",std::ios::out);
    for(auto it = _index.begin();it !=_index.end();it++){
        ofs2<<it->first<<" ";
        for(auto it2 = (it->second).begin();it2!=(it->second).end();it2++){
            ofs2<<*it2<<" ";
        }
        ofs2<<endl;
    }
    ofs.close();
    
}

int main()
{
    Dictionary D;
    D.trans("../data/english.txt");
    D.read("../data/Eng.txt");
    D.store("../data/dict.txt");
   cout<< D.getSize();
    
    return 0;
}

