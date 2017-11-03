#include <iostream>
#include <time.h>
#include <cmath>

#define dimension 2 //維度
#define particle_num 20 //粒子數
#define c1 2 // c1常數
#define c2 2 // c2常數
#define iteration_times 10000 // run幾次
#define upbound 5.12
#define lowbound -5.12

using namespace std;
float particle[particle_num][dimension*2];  //紀錄particle的位置與速度
float particle_optimal[particle_num][dimension];
float global_optimal[dimension];
float global_fitness=999;
float particle_fitnessOptimal[particle_num];
float fx_new[particle_num];


void initial(){
    for(int i=0;i<particle_num;i++) {
        for (int j = 0; j < dimension; j++) {
            particle[i][j*2]=(upbound - lowbound) * (double)rand() / RAND_MAX + lowbound;
            particle[i][j*2+1]=0;
            particle_optimal[i][j]=particle[i][j*2];
        }
    }

    for(int i=0;i<particle_num;i++){
        cout<<"particle "<<i<<endl;
        for(int j=0;j<dimension;j++){
            cout<<j<<" dimension "<<particle[i][j*2]<<endl;
        }
    }

    for(int i=0;i<particle_num;i++){
        particle_fitnessOptimal[i]=999;
    }

}
void update(){
    for (int i = 0; i < particle_num; i++) {
        for (int j = 0; j < dimension; j++) {
            particle[i][j*2+1]=(1*particle[i][j*2+1])+(c1*((double)(rand())/(RAND_MAX + 1.0))*(particle_optimal[i][j]-particle[i][j*2]))+(c2*((double)(rand())/(RAND_MAX + 1.0))*(global_optimal[j]-particle[i][j*2]));
            particle[i][j*2]+=particle[i][j*2+1];
            if(particle[i][j*2]>upbound){
                particle[i][j*2]=upbound;
            }
            else if(particle[i][j*2]<lowbound){
                particle[i][j*2]=lowbound;
            }
        }
    }

}

void Rastrigin_Function() {
    for (int i = 0; i < particle_num; i++) {
        float total=0;
        for (int j = 0; j < dimension; j++) {
            float temp;
            temp=(particle[i][j*2]*particle[i][j*2])-10*cos(2*M_PI*particle[i][j*2]);
            total+=temp;
        }
        fx_new[i]=(10*dimension)+total;
        if(fx_new[i]<global_fitness){
            global_fitness=fx_new[i];
            for (int k = 0; k < dimension; k++) {
                global_optimal[k]=particle[i][k*2];
            }
        }
    }

    /*
    for(int i=0;i<particle_num;i++) {
        cout << fx[i] << endl;
    }
     */
}

void Optimal_Replace(){
    for(int i=0;i<particle_num;i++){
        if(fx_new[i]<particle_fitnessOptimal[i]) {
            for (int j=0;j<dimension;j++) {
                particle_optimal[i][j]=particle[i][j*2];
                particle_fitnessOptimal[i]=fx_new[i];
            }
        }
    }
}


int main() {
    srand(time(NULL));
    initial();
    Rastrigin_Function();
    Optimal_Replace();
    cout<<"Global Optimization"<<endl;
    for (int k = 0; k < dimension; k++) {
        cout<<global_optimal[k]<<endl;
    }
    cout<<"=========================================================="<<endl;
    for(int a=0;a<iteration_times;a++) {
        update();
        Rastrigin_Function();
        Optimal_Replace();
    }

    cout<<"Patical Optimal:"<<endl;
    for (int i = 0; i < particle_num; i++) {
        cout << "particle " << i << endl;
        for (int j = 0; j < dimension; j++) {
            cout << j << " dimension " << particle_optimal[i][j * 2] << endl;
        }
        cout << "f(x)=" << particle_fitnessOptimal[i] << endl;
    }
    cout<<endl;
    cout<<"Global Optimization"<<endl;
    for (int k = 0; k < dimension; k++) {
        cout<< k << " dimension "<<global_optimal[k]<<endl;
    }
    cout<<"global fitness: "<<global_fitness<<endl;

}