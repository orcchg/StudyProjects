//////////////////////////////////////////////////////////////////////////////////////
//Необходимо разделить большое чило на большое число.
//Эти числа хранятся в массиве (каждый элемент - одна цифра числа).
//////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
//////////////////////////////////////////////////////////////////////////////////////
typedef std::string  T_num_s;
//////////////////////////////////////////////////////////////////////////////////////
void  del_leading_zero(T_num_s&  a)
{
    while(a.size() > 1
          && a[0] == '0')
    {
        a.erase(0, 1);
    }
}
//////////////////////////////////////////////////////////////////////////////////////
bool less_for_big_int(T_num_s  a, T_num_s  b)
{
    del_leading_zero(a);
    del_leading_zero(b);
 
    return  a.size() == b.size() ? a < b : a.size() < b.size();
}
//////////////////////////////////////////////////////////////////////////////////////
void  reduce_big_int(T_num_s&  minuend, const T_num_s&  subtrahend)
{    
    for(T_num_s::size_type  cur_pos = 0; cur_pos < subtrahend.size(); ++cur_pos)
    {
        T_num_s::size_type  minuend_cur_pos     = minuend.size()     - 1 - cur_pos;
        T_num_s::size_type  subtrahend_cur_pos  = subtrahend.size()  - 1 - cur_pos;
 
        char&        cur_minuend_dig_ref     = minuend     [minuend_cur_pos];
        const char&  cur_subtrahend_dig_ref  = subtrahend  [subtrahend_cur_pos];
 
        if(cur_minuend_dig_ref >= cur_subtrahend_dig_ref)
        {
            cur_minuend_dig_ref -= cur_subtrahend_dig_ref - '0';
        }
        else
        {
            (cur_minuend_dig_ref -= cur_subtrahend_dig_ref - '0') += 10;
            for(int i = 1; ; ++i)
            {
                if(minuend[minuend_cur_pos - i] == '0')
                {
                    minuend[minuend_cur_pos - i] = '9';
                }
                else
                {
                    --minuend[minuend_cur_pos - i];
                    break;
                }
            }
        }
        del_leading_zero(minuend);
    }
    del_leading_zero(minuend);
}
//////////////////////////////////////////////////////////////////////////////////////
void  inc_big_int(T_num_s&  a)
{    
    for(T_num_s::size_type  cur_pos = a.size() - 1;; --cur_pos)
    {
        if(a[cur_pos] < '9')
        {
            ++a[cur_pos];
            return;
        }
        else
        {
            a[cur_pos] = '0';
            if(cur_pos == 0)
            {              
                a.insert(0, "1");
                return;
            }
        }    
    }
}
//////////////////////////////////////////////////////////////////////////////////////
T_num_s  div_big_int(const T_num_s&  a, const T_num_s&  b)
{
    if(b == "0")
    {
        return  "division into zero";
    }    
 
    T_num_s  res = "0";
    T_num_s  minuend     = a;
    T_num_s  subtrahend  = b;
    
    while(subtrahend.size() < minuend.size())
    {
        subtrahend += '0';    
    }
 
    for(;;)
    {
        while(!less_for_big_int(minuend, subtrahend))
        {
            reduce_big_int(minuend, subtrahend);
            inc_big_int(res);
        }
        if(subtrahend.size() <= b.size())
        {
            break;
        }
        
        subtrahend.erase(subtrahend.size() - 1);   
        res += '0';              
        del_leading_zero(res);
    }          
    
    return  res;
}
//////////////////////////////////////////////////////////////////////////////////////