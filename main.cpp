#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <sstream>

std::vector<unsigned char> readfile(const std::string&p){
    std::ifstream f(p,std::ios::binary);
    if(!f.is_open()) return {};
    return std::vector<unsigned char>((std::istreambuf_iterator<char>(f)),std::istreambuf_iterator<char>());
}

void writefile(const std::string&p,const std::vector<unsigned char>&d){
    std::ofstream f(p,std::ios::binary);
    f.write((char*)d.data(),d.size());
}

void dump(const std::vector<unsigned char>&d){
    for(size_t i=0;i<d.size();i++){
        if(i%16==0) std::cout<<std::setw(8)<<std::setfill('0')<<std::hex<<i<<"  ";
        std::cout<<std::setw(2)<<std::setfill('0')<<std::hex<<(int)d[i]<<" ";
        if(i%16==15) std::cout<<"\n";
    }
    std::cout<<"\n";
}

int hexbyte(const std::string&s){
    int v=0;
    std::stringstream ss;
    ss<<std::hex<<s;
    ss>>v;
    return v;
}

int main(){
    std::string path;
    std::cout<<"file: ";
    std::cin>>path;

    auto data=readfile(path);
    if(data.empty()){
        std::cout<<"failed\n";
        return 0;
    }

    dump(data);

    std::cout<<"offset hex (-1 exit): ";
    std::string off;
    std::cin>>off;
    if(off=="-1") return 0;

    size_t o=0;
    std::stringstream ss;
    ss<<std::hex<<off;
    ss>>o;

    if(o>=data.size()){
        std::cout<<"bad offset\n";
        return 0;
    }

    std::cout<<"new byte hex: ";
    std::string nb;
    std::cin>>nb;

    data[o]=hexbyte(nb)&0xff;
    writefile(path,data);

    std::cout<<"done\n";
    return 0;
}
