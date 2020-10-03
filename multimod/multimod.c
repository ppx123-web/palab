#include <stdint.h>

static inline int bit_of(uint64_t x, int i) 
{
    return (x >> i) & 1;
}//取位运算

static inline  void right(short * a,int x)
{
    for(int i = 0;i < 128;i++)
    {
        a[i]=a[i+1];
    }
    a[127]=0;
}

static inline void sub(short *a,short *b)
{
    short cin=0;
    for(int i= 0;i < 128;i++)
    {
        if(a[i] >= b[i]+cin)
        {
            a[i]=a[i]-b[i]-cin;
            cin=0;
        }
        else{
            a[i]=a[i]+2-b[i]-cin;
            cin=1;
        }
    }
}

static inline short com(short *a,short *b)
{
    for(int i = 127;i>=0;i--)
    {
        if(a[i] > b[i])
        {
            return 1;
        }
        else if(a[i] < b[i]){
            return 0;
        }
        else continue;
    }
    return 1;
}

uint64_t multimod(uint64_t a, uint64_t b, uint64_t m) 
{
    short int x[64]={0},y[64]={0},cin=0,ans[128]={0},mod[128]={0};
    int num=0;
    uint64_t ret=0;
    for(int i = 0;i < 64;i++)
    {
        x[i]=bit_of(a,i);
        y[i]=bit_of(b,i);
        mod[i]=bit_of(m,i);
    }
    for(int i = 0;i < 128;i++)
        {
            for(int j = i > 63? i-63:0;j < (i > 63? 64: i+1); j++)
            {
                ans[i]=ans[i]+(x[j]&y[i-j]);
            }
            ans[i]=ans[i]+cin;
            cin=ans[i]>>1;
            ans[i]=ans[i]&1;
        }
    
    for(int i= 63;i >= 0;i--)
    {
        if(bit_of(m,i)==1)
        {
            num=i;
            break;
        }
    }

    for(int i = num;i >= 0;i--)
    {
        mod[127-num+i]=mod[i];
        mod[i]=0;
    }
    while(num < 127)
    {
        if(com(ans,mod))
        {
            sub(ans,mod);
        }
        num++;
        right(mod,1);
    }
    for(int i = 63;i >= 0;i--)
    {
        ret=(ret<<1)+ans[i];
    }
    return ret;
}