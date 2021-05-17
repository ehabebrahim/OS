#include <iostream>
#include<bits/stdc++.h>
using namespace std;

//--------------------------global variables---------------------//
int num_of_recources=0,num_of_process=0;

//-----------------function implementation-------------//
vector<vector<int>> get_need_matrix(vector<vector<int>>Max,vector<vector<int>>Allocation);
bool comp(vector<int>Need,vector<int>Available);
vector<int> new_available(vector<int>Available,vector<int>Allocation);
bool is_safe(vector<bool>finish);
vector<int> update_Available_and_Need(vector<int>Available,vector<int>Request);
vector<int> update_Allocation(vector<int>Allocation,vector<int>Request);

//------------start------------//
int main()
{

    cout<<"Enter the number of resources: ";
    cin>>num_of_recources;
    cout<<"Enter the number of process: ";
    cin>>num_of_process;
    vector<vector<int>>allocation(num_of_process,vector<int>(num_of_recources));
    vector<vector<int>>Max_allocation(num_of_process,vector<int>(num_of_recources));
    vector<int>available(num_of_recources);
    vector<vector<int>> Need(num_of_process,vector<int>(num_of_recources));
    vector<bool> finish(num_of_process);
    vector<int>arrange;
    vector<int>not_taken;
    vector<int>request(num_of_recources);
    int req;
    bool f=false;
    for(int i=0;i<num_of_process;i++)
    {   char a='A';
        for(int j=0;j<num_of_recources;j++)
        {
            cout<<"Enter Allocation of p"<<i+1<<", value for "<<a<<": ";
            cin>>allocation[i][j];
            a++;
        }
    }
    for(int i=0;i<num_of_process;i++)
    {   char a='A';
        for(int j=0;j<num_of_recources;j++)
        {
            cout<<"Enter Max Allocation of p"<<i+1<<", value for "<<a<<": ";
            cin>>Max_allocation[i][j];
            a++;
        }
    }
    for(int i=0;i<num_of_recources;i++)
    {
        char a;
        if(i==0)
             a='A';

        cout<<"Enter Available recources of "<<a<<" ";
        cin>>available[i];
        a++;
    }
    Need= get_need_matrix(Max_allocation,allocation);
    for(int i=0;i<num_of_process;i++)
    {
        char a;

        if(i==0)
        {
            cout<<"    ";
            a='A';
            for(int j=0;j<num_of_recources;j++)
            {
                cout<<a<<" ";
                a++;
            }
            cout<<endl;
        }

        cout<<"p"<<i+1<<" [";
        for(int j=0;j<num_of_recources;j++)
        {
            cout<<Need[i][j]<<" ";
        }
        cout<<"]"<<endl;
    }
    cout<<"if need an immediate request Enter the number of process starts from 1 if not needed Enter 0 : ";
    cin>>req;

    if(req)
    {
       // cout<<req-1<<endl;
        for(int i=0;i<num_of_recources;i++)
        {
            char a;
            if(i==0)
                 a='A';

            cout<<"Enter The Request of p"<<req<<", value for: "<<a<<" ";
            cin>>request[i];
            a++;
        }
        if(comp(request,Need[req-1])&&comp(request,available))
        {
            available=update_Available_and_Need(available,request);
            allocation[req-1]=update_Allocation(allocation[req-1],request);
            Need[req-1]=update_Available_and_Need(Need[req-1],request);
            //available=new_available(available,allocation[req-1]);
            arrange.push_back(req-1);
            finish[req-1]=true;
            f=true;
           // for(int i=0;i<num_of_recources;i++)
            //    cout<<Need[req-1][i]<<" ";
        }
        else
        {
            cout<<"Not granted"<<endl;
            return 0;
        }

    }


    // make a compare
    for(int i=0;i<num_of_process;i++)
    {

        if(comp(Need[i],available))
        {
            if(i!=req-1)
                arrange.push_back(i);

            finish[i]=true;

            available=new_available(available,allocation[i]);
        }
        else
        {
            not_taken.push_back(i);
            //cout<<i<<" ";
        }
    }
     int n=not_taken.size();
     int prev_flag=0;
    while(n>0)
    {
       int flag=0;
        for(int i=0;i<not_taken.size();i++)
        {

            if(comp(Need[not_taken[i]],available))
            {
                if(not_taken[i]!=req-1)
                    arrange.push_back(not_taken[i]);
                finish[not_taken[i]]=true;
                available=new_available(available,allocation[not_taken[i]]);
                n--;
                remove(not_taken.begin(),not_taken.end(),not_taken[i]);

            }
            else
                flag++;
        }

        if(prev_flag==flag)
            break;
        prev_flag=flag;
    }
    if(f&&is_safe(finish))
        cout<<"Yes request can be granted with safe state";

    else if(is_safe(finish)&&!f)
        cout<<"Yes";

    if(is_safe(finish))
    {
        cout<<", Safe state "<<"<";
        for(int i=0;i<arrange.size();i++)
        {
            cout<<"p"<<arrange[i]+1<<" ";
        }
        cout<<">"<<endl;
    }
    else
        cout<<"NO"<<endl;


    return 0;
}

vector<vector<int>> get_need_matrix(vector<vector<int>>Max,vector<vector<int>>Allocation)
{
    vector<vector<int>> Need(num_of_process,vector<int>(num_of_recources));
    for(int i=0;i<num_of_process;i++)
    {
        for(int j=0;j<num_of_recources;j++)
        {
            Need[i][j]=Max[i][j]-Allocation[i][j];
        }
    }
    return Need;
}

bool comp(vector<int>Need,vector<int>Available)
{
    for(int i=0;i<num_of_recources;i++)
    {

        if(Need[i]>Available[i])
            return false;
    }
    return true;
}
vector<int> new_available(vector<int>Available,vector<int>Allocation)
{

    for(int i=0;i<num_of_recources;i++)
    {
        Available[i]+=Allocation[i];
    }

    return Available;
}
bool is_safe(vector<bool>finish)
{
    for(int i=0;i<num_of_process;i++)
    {
        if(!finish[i])
            return false;
    }
    return true;
}
vector<int> update_Available_and_Need(vector<int>Available,vector<int>Request)
{
    for(int i=0;i<num_of_recources;i++)
    {
        Available[i]-=Request[i];
    }
    return Available;
}
vector<int> update_Allocation(vector<int>Allocation,vector<int>Request)
{
    for(int i=0;i<num_of_recources;i++)
    {
        Allocation[i]+=Request[i];
    }
    return Allocation;
}

