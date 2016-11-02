//遗传算法 GA
#include<iostream>
#include <cstdlib>
#include<bitset>
using namespace std;
const int L=5; //定义编码的长度
int f(int x) //定义测设函数f(x)
{
    int result;
    result=x*x*x-60*x*x+900*x+100;
    return result;
}
int main(int argc,char *argv[])
{
    int a(0),b(32); //定义x的定义域范围
    const int pop_size=8; //定义种群大小
    int L; //指定编码的长度
    const int NG=20; //指定种群最大的繁殖的代数
    int t=0; //当前繁殖的代数
    int p[pop_size]; //定义种群
    int q[pop_size]; //定义繁殖种群 即种群的下一代
    srand(6553); //定义随机数生成的种子
    double sum; //适值总和
    double avl_sum; //适度平均值
    double p_probability[pop_size]; //适值概率
    double pp[pop_size];
    double pro; //定义随机生成的概率
    float pc=0.90; //定义交叉的概率
    float pm=0.05; //定义变异的概率
    cout<<"初始的种群 ";
    for(int i=0;i<pop_size;i++) //生成初始的第0代种群
    {
        p[i]=rand()%31;
        cout<<p[i]<<" ";
    }
    cout<<endl;
    cout<<endl;
    void Xover(int &,int &); //声明交叉函数
    //当停止准则不满足 即繁殖代数没到最大代数 ,继续繁殖
    while(t<=NG)
    {
        cout<<"繁殖的代数：t="<<t<<endl;
        sum=0.0;
        for(int i=0;i<pop_size;i++)
        {
            q[i]=p[i];
            cout<<q[i]<<" ";
        }
        cout<<endl;
        for(int i=0;i<pop_size;i++) //计算sum
            sum +=f(p[i]);
        avl_sum=sum/pop_size;
        cout<<"sum="<<sum<<endl;
        cout<<"适度平均值="<<avl_sum<<endl;
        for(int i=0;i<pop_size;i++) //计算适值概率
        {
            p_probability[i]=f(p[i])/sum;
            if(i==0)
            {
                pp[i]=p_probability[i];
                cout<<"pp"<<i<<"="<<pp[i]<<endl;
            }
            else
            {
                pp[i]=p_probability[i]+pp[i-1];
                cout<<"pp"<<i<<"="<<pp[i]<<endl;
            }
            //cout<<"p_probability"<<i<<"="<<p_probability[i]<<endl;
        }
        //选择双亲
        for(int i=0;i<pop_size;i++)
        {
            pro=rand()%1000/1000.0;
            if(pro>=pp[0]&&pro<pp[1])
                p[i]=q[0];
            else if(pro>=pp[1]&&pro<pp[2])
                p[i]=q[1];
            else if(pro>=pp[2]&&pro<pp[3])
                p[i]=q[2];
            else if(pro>=pp[3]&&pro<pp[4])
                p[i]=q[3];
            else if(pro>=pp[4]&&pro<pp[5])
                p[i]=q[4];
            else
                p[i]=q[5];
        }
        //杂交算子

        
        int r=0;
        int z=0;
        for(int j=0;j<pop_size;j++)
        {
            pro=rand()%1000/1000.0;
            if(pro<pc)
            {
                ++z;
                if(z%2==0)
                    Xover(p[r],p[j]);
                else
                    r=j;
            }
        }
        //变异算子
        for(int i=1;i<=pop_size;i++)
            for(int j=0;j<L;j++)
            {
                pro=rand()%1000/1000.0; //在【0,1】区间产生随机数
                if(pro<pm)
                {
                    bitset<L>v(p[i]);      
                    v.flip(j);
                    p[i]=v.to_ulong();
                } 
            } 
        t++;
        cout<<endl; //种群繁殖一代 
    }
    cout<<"最终结果：";  
    for(int i(0);i<pop_size;i++) //算法结束，输出结果 
    {
        cout<<p[i]<<" ";
    }
    cout<<endl;
    return 0;
}
//定义杂交操作 
void Xover(int &a,int &b)         
{ 
    int pos; //随机生成杂交点 即第几个分量进行相互交换
    pos=rand()%5+1; //在n个分量中，随机确定第pos个分量 
    int j,k;
    j=pos;
    k=pos;
    bitset<L>e(a);
    bitset<L>f(b); //前pos个分量进行相互交换
    bitset<L>g;            
    bitset<L>h;
    for(int i=0;i<pos;i++)
    {
        if(e[i]==1)
            g.set(i); 
    }
    for(int i=0;i<pos;i++)
    {
        if(f[i]==1)
            h.set(i);
    }
    for(j;j<L;j++)
    {
        if(f[j]==1)
            g.set(j);
    }
    for(k;k<L;k++)
    {
        if(e[k]==1)
            h.set(k);
    }
    a=g.to_ulong();
    b=h.to_ulong();  
}
