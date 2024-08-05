#include <vector>
#include <string>

#include <iostream>
void print(const std::vector<int>& container){
    for (const int x : container)
        std::cout << x << ' ';
    std::cout << '\n';
}


class Long{
    public:
        Long(){
        }
        Long(std::string p){
            int l=0;
            if(p[0]=='-'){
                sign=0;
                l=1;
            }else{
                sign=1;
            }
            int j=-l;
            bool w=0;
            for(char c:p){
                if(c=='.'){
                    fp=j;
                    w=1;
                }else{
                    data.push_back(c-'0');
                }
                j++;
            }
            if(!w) fp=j;
            if(l) data.erase(data.begin());
        };
        Long(int p){
            if(p<0){sign=0;}else{sign=1;}
            int y=p;
            std::vector<int> h;
            while(y){
                h.push_back(y%10);
                y/=10;
            }
            data.insert(data.begin(),h.size(),0);
            for(unsigned int i=data.size();i>0;i--){
                data[data.size()-i]=h[i-1];
            }
            fp=data.size();
        }
        std::string toString(){
            std::string i;
            for(int p:data){
                i+=p+'0';
            }
            i.insert(i.begin()+fp,'.');
            if(!sign) i='-'+i;
            return i;
        };
        unsigned int GetRight(){//get right length from floatpoint
            return data.size()-fp;
        }
        void LeftAdd0(unsigned int size){
            if(size){
                data.insert(data.begin(),size,0);
                fp+=size;
            }
        }
        void RightAdd0(unsigned int size){
            if(size) data.insert(data.end(),size,0);
        }
        Long abs(){
            Long u=*this;
            u.sign=1;
            return u;
        }
        Long* b9(){
            for(int j=0;j<data.size();j++){
                data[j]=9-data[j];
            }
            return this;
        }
        Long SingleMult(int a){
            Long u=abs();
            int next=0;
            for(int i=u.data.size()-1;i>=0;i--){
                next=next+a*u.data[i];
                u.data[i]=next%10;
                next/=10;
            }
            if(next){
                u.data.insert(u.data.begin(),1,next);
                u.fp+=1;
                next=0;
            }
            return u;
        }
        Long* Mult10(int p){//mult 10^p
            if(GetRight()<=p){
                RightAdd0(p-GetRight()+1);
            }
            fp+=p;
            return this;
        }
        Long* operator+(Long a){
            //unit byte to this &Long;
            if(fp<a.fp){
                LeftAdd0(a.fp-fp);
            }else{
                a.LeftAdd0(fp-a.fp);
            }
            if(GetRight()<a.GetRight()){
                RightAdd0(a.GetRight()-GetRight());
            }else{
                a.RightAdd0(GetRight()-a.GetRight());
            }
            //print(data);
            //print(a.data);
            int next=0;
            for(unsigned int i=data.size();i>0;i--){
                next+=data[i-1]+a.data[i-1];//std::cout<<i-1<<std::endl;
                data[i-1]=next%10;
                next/=10;
            }
            //print(data);
            if(next){
                data.insert(data.begin(),1,next);
                fp+=1;
                next=0;
            }
            return this;
        };
        Long* operator+(int a){return *this+Long(a);}
        Long* operator-(Long a){
            if(sign==a.sign){
                sign=*this>=a;
                print(data);
                a.b9();

                Long u;
                u.sign=1;
                u.fp=a.fp;
                int i=0;
                for(;i<a.data.size();i++){
                    u.data.push_back(0);
                }
                u.data[i-1]=1;

                a+u;
                *this+a;
                print(data);
                data.erase(data.begin());
                fp--;
                return this;
            }else{
                return *this+a;
            }
        }

        Long* operator*(Long a){
            Long p=*this;
            data={0};
            fp=0;
            for(int i=a.data.size()-1;i>=0;i--){
                *this+*(p.SingleMult(a.data[i]).Mult10(a.data.size()-1-i));
            }
            sign=!((sign-a.sign)*(sign-a.sign));
            fp-=a.GetRight();
            return this;
        };
        Long* operator/(Long a){
            return this;
        }

        bool operator>(Long a){//0 's sign?
            if(sign>a.sign) return true;
            if(a.sign==0){
                return abs()<a.abs();
            }
            if(fp<a.fp){
                return false;
            }else if(fp>a.fp){
                return true;
            }
            if(GetRight()<a.GetRight()){
                RightAdd0(a.GetRight()-GetRight());
            }else{
                a.RightAdd0(GetRight()-a.GetRight());
            }
            for(int j=0;j<data.size();j++){
                if(data[j]>a.data[j]){
                    return true;
                }else if(data[j]<a.data[j]){
                    return false;
                }
            }
            return false;
        }
        bool operator<(Long a){
            if(sign<a.sign) return true;
            if(a.sign==0){
                return abs()>a.abs();
            }
            if(fp>a.fp){
                return false;
            }else if(fp<a.fp){
                return true;
            }
            if(GetRight()<a.GetRight()){
                RightAdd0(a.GetRight()-GetRight());
            }else{
                a.RightAdd0(GetRight()-a.GetRight());
            }
            for(int j=0;j<data.size();j++){
                if(data[j]<a.data[j]){
                    return true;
                }else if(data[j]>a.data[j]){
                    return false;
                }
            }
            return false;
        }
        bool operator==(Long a){
            if(fp!=a.fp||GetRight()!=a.GetRight()||sign!=a.sign){
                return false;
            }
            for(int j=0;j<data.size();j++){
                if(data[j]!=a.data[j]){
                    return false;
                }
            }
            return true;
        }
        bool operator>=(Long a){
            return *this>a||*this==a;
        }
        bool operator<=(Long a){
            return *this<a||*this==a;
        }
    private:
        std::vector<int> data;//unsigned int
        bool sign;//1:+ or 0,0:-
        unsigned int fp;//floatpoint
};