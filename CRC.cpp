#include<iostream>
#include<string.h>
#include<unistd.h>
using namespace std;
string CRC_12=     "1100000001111";
string CRC_12_zero="0000000000000";
string CRC_16=     "11000000000000101";
string CRC_16_zero="00000000000000000";

string key= CRC_12;//"";
string zero=CRC_12_zero;
string performXOR(string key,string inputData){
    int n=key.length();
    string result="";
    if(inputData[0]=='0'){
        key=zero;
    }else{
        key=::key;
    }
    for(int i=1;i<n;i++){
        if(key[i]==inputData[i]){
            result+="0";
        }
        else{
            result+="1";
        }
    }
    return result;
}

void receiver(string data){

    cout<<"\n\n\nReceiving...\n";
    usleep(2*1000000);
    
    string result=data.substr(0,key.length());
    int length=key.length()-1;
    for(int i=0;i<data.length() && length<data.length();i++){
        result=performXOR(key,result+data[length]);
        length++;
    }
    
    size_t pos=result.find("1");
    
    if(pos!=string::npos){
        cout<<"Error in Transmission!\n";
    }
    else{
        cout<<"Transferred Successfully\n";
    }

}
void sender(string key,string tempData,string inputData){
    cout<<"Preparing data to send...\n";
    usleep(1*1000000);
    string result=tempData;
    int length=key.length()-1;
    for(int i=0;i<=tempData.length()-key.length();i++){
        result=performXOR(key,result+tempData[length]);
        length++;
    }
    inputData=inputData.append(result);
    
    cout<<"\n"<<"\""<<result<<"\""<<"is the remainder\n"<<" \" "<<inputData<<" \" prepared and sent to receiver.";
    receiver(inputData);
    
}

int main()
{
    string inputData,tempData;
    int keyLength;
    cout<<"Enter the data:";
    cin>>inputData;
    tempData=inputData;
    keyLength=key.length();
    for(int i=0;i<keyLength-1;i++){
        tempData=tempData.append("0");
    }
    sender(key,tempData,inputData);
    return 0;
}