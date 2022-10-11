//(2,1,8) convolutional code encoder and decoder viterbi algorithm
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<malloc.h>

#define state_num 256 //2^8個state
#define register_num 8 //m


int state_vary(int input, int state){// function :輸入input 跟當前state 輸出下一個state
    int rr_value[register_num];
    for (int i = sizeof(rr_value) / sizeof(int)-1; i >=0 ;i--) //state轉二進位
    {
        rr_value[i] = state % 2;
        state = state / 2;
    }
    
    int all_value[register_num];
    all_value[0] = input;
    for (int p = 0 ; p < register_num -1 ; p++){ //register shift
        all_value[p + 1] = rr_value[p] ;
    }

    int nstate = 0;
    for (int q = 0; q < register_num;q++){  //next state 轉十進位
        nstate = nstate + all_value[q] * pow(2, (register_num-1) - q); 
    }
    return nstate;
    }

int v0(int input, int state){//function
    int g1[] = {1,0,1,1,1,0,0,0,1};//change
        int vv;
        int rr_value[register_num];
        for (int i = sizeof(rr_value) / sizeof(int)-1; i >=0 ;i--){
            rr_value[i] = state % 2;
            state = state / 2;
        }
        //做convolutional
        vv = (input * g1[0] + rr_value[0] * g1[1] + rr_value[1] * g1[2] + rr_value[2] * g1[3] + rr_value[3] * g1[4] + rr_value[4] * g1[5] + rr_value[5] * g1[6] + rr_value[6] * g1[7] + rr_value[7] * g1[8]) % 2;//要改
        return vv;
}

int v1(int input, int state){//function
    int g2[] = {1,1,1,1,0,1,0,1,1};//change
        int vv;
        int rr_value[register_num]; 
        for (int i = sizeof(rr_value) / sizeof(int) - 1; i >= 0; i--){
            rr_value[i] = state % 2;
            state = state / 2;
        }
        //做convolutional
        vv = (input * g2[0] + rr_value[0] * g2[1] + rr_value[1] * g2[2] + rr_value[2] * g2[3] + rr_value[3] * g2[4] + rr_value[4] * g2[5] + rr_value[5] * g2[6] + rr_value[6] * g2[7] + rr_value[7] * g2[8]) % 2; //要改
        return vv;
}

int main() {

    /*viterbi decoder */
    
    //int r_data[] = {1,1,1,0,1,1,1,1,1,0,1,0,0,1,0,0,1,0,1,0,1,0,1,1,1,0,1,1,0,0,1,1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,0,1,0,0,0,1,1,1,1,0,1,1,1,1,0,0,1,1,1,0,0,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,0,0,1,0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0,1,1,0,1,1,1,0,0,0,0,0,1,0,1,1,1,1,0,1,0,1,0,1,1,0,0,0,1,0,1,1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,1,1,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,1,1,1,0,0,1,0,0,0,0,0,0,1,1,1,0,1,1,0,1,1,0,1,0,1,0,1,1,0,0,0,0,0,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,1,1,1,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,1,0,1,1,0,1,0,0,1,0,1,0,1,0,1,0,0,1,1,0,1,0,1,0,0,1,0,0,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1,0,0,1,0,1,0,0,1,0,1,0,0,1,1,1,1,1,0,0,1,0,0,1,1,0,0,1,1,1,0,0,1,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,1,0,0,1,1,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1,0,0,0,1,1,1,0,1,0,0,1,0,0,1,1,1,0,1,1,0,1,1,0,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,1,1,0,0,0,0,1,1,1,0,1,1,0,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,1,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1,1,1,1,1,0,0,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,0,0,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,0,1,1,0,1,0,0,0,1,1,0,0,1,0,0,1,1,0,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,1,1,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,0,1,0,0,1,1,0,1,0,0,1,0,1,1,1,1,0,0,1,1,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,0,0,1,1,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,1,1,0,0,1,0,0,1,0,1,1,0,1,1,0,0,0,1,0,0,1,0,0,0,1,1,0,0,0,1,0,1,1,0,1,0,1,0,1,0,0,0,1,1,0,1,0,0,1,1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,1,0,0,1,1,0,1,1,1,0,1,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,1,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,1,0,1,0,1,0,0,1,1,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,1,0,1,0,1,1,1,0,0,1,0,1,1,0,1,1,0,1,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,0,1,1,0,0,0,1,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,0,0,1,0,0,0,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0};
    int r_data[] = {1,1,1,0,1,1,1,1,1,0,1,0,0,1,0,0,1,0,1,0,1,0,1,1,1,0,1,1,0,0,1,1,1,1,1,0,1,0,0,0,0,0,1,0,1,1,0,1,0,1,1,0,1,1,0,1,0,1,0,1,0,0,0,1,1,1,1,0,1,1,1,1,0,0,1,1,1,0,0,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,0,0,1,0,0,1,1,0,0,1,0,0,0,0,1,0,0,1,1,0,1,1,0,1,1,1,0,0,0,0,0,1,0,1,1,1,1,0,1,0,1,0,1,1,0,0,0,1,0,1,1,1,0,0,0,0,0,1,0,1,0,0,0,0,0,0,0,1,1,0,0,1,0,0,1,0,1,1,0,0,0,1,0,0,0,0,1,0,1,0,0,0,0,0,0,1,1,1,1,0,0,1,0,0,0,0,0,0,1,1,1,0,1,1,0,1,1,0,1,0,1,0,1,1,0,0,0,0,0,1,0,0,1,1,1,1,0,0,1,1,0,0,1,1,0,1,1,1,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,1,0,1,1,0,1,0,0,1,0,1,0,1,0,1,0,0,1,1,0,1,0,1,0,0,1,0,0,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1,0,0,1,0,1,0,0,1,0,1,0,0,1,1,1,1,1,0,0,1,0,0,1,1,0,0,1,1,1,0,0,1,0,1,1,1,1,1,0,0,0,0,1,0,1,0,1,0,1,0,0,0,0,1,0,0,0,0,0,1,1,1,1,1,0,0,1,1,0,0,0,1,0,0,1,1,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,1,1,1,1,0,1,1,1,0,1,1,1,1,0,0,0,1,1,0,1,0,1,0,0,0,1,0,0,0,1,1,1,0,1,0,0,1,0,0,1,1,1,0,1,1,0,1,1,0,1,0,0,1,1,0,0,0,0,1,1,1,1,0,0,1,0,0,1,0,1,1,0,0,0,0,1,1,1,0,1,1,0,1,1,1,1,1,0,1,0,0,0,0,0,0,0,1,0,1,0,0,1,0,0,1,0,1,0,1,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1,1,1,1,1,0,0,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,0,1,1,0,1,0,1,0,1,0,0,0,0,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,0,0,1,1,0,1,0,0,0,1,1,0,0,1,0,0,1,1,0,0,1,0,1,0,1,0,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,1,1,0,1,1,0,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,0,0,1,0,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,0,1,0,0,1,1,0,1,0,0,1,0,1,1,1,1,0,0,1,1,1,0,0,1,0,0,0,0,0,1,0,0,0,0,0,1,0,1,1,0,0,0,1,1,0,0,1,0,1,0,0,0,0,1,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,1,1,0,0,1,1,0,1,1,0,0,1,0,0,1,0,1,1,0,1,1,0,0,0,1,0,0,1,0,0,0,1,1,0,0,0,1,0,1,1,0,1,0,1,0,1,0,0,0,1,1,0,1,0,0,1,1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,1,0,0,1,1,0,1,1,1,0,1,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0,0,1,0,0,1,0,0,1,0,1,0,1,0,0,1,1,0,0,0,0,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,1,1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,0,1,1,1,0,1,0,1,0,0,1,1,0,1,0,0,0,1,0,0,0,0,0,0,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,0,0,1,1,1,0,1,0,1,0,1,1,1,0,0,1,0,1,1,0,1,1,0,1,0,0,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1,0,0,0,1,0,0,1,1,0,0,1,0,1,1,0,0,0,1,0,0,0,1,0,0,0,1,1,0,1,1,0,0,0,1,1,0,1,1,0,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,1,1,0,1,1,0,1,1,0,0,0,1,0,0,0,0,1,1,0,0,1,1,1,0,0,0,0,0,0,0};
    /*srand(time(0));,
    for (int g = 0; g < 15;g++){
        position[g]=rand() % 1254;
        printf("%d\n", position[g]+1);
        r_data[position[g]] = (r_data[position[g]] + 1) % 2;
    }*/


    int distance[state_num] = {0};                       //每個state後留下的最短hamming distance
    int path[state_num][sizeof(r_data) / (2 * sizeof(int))] = {0}; //答案

    int vv_code[2];

    for (int i = 0; i < sizeof(r_data) / sizeof(int); i += 2){ //r_data依次兩個進去做比較
        
        if (i == 0) //由state S0開始，出去有2個state
        {
            int tt_d[sizeof(distance) / sizeof(int)]; //把distance暫存起來，因為用原本的distance計算時會被洗掉
            for (int w = 0; w < sizeof(distance) / sizeof(int); w++)
            {
                tt_d[w] = distance[w];
            }
            for (int k = 0; k < 2; k++) //先算input為0，求出output再和r_data比較得distance，再算input為1
            {
                int state = 0; //由state S0開始
                int next_state;
                vv_code[0] = v0(k, state); //那個state的輸出
                vv_code[1] = v1(k, state); 
                next_state = state_vary(k, state);

                distance[next_state] = tt_d[state] + (r_data[i] + vv_code[0]) % 2 + (r_data[i + 1] + vv_code[1]) % 2 ; //第一個時間點的//得到兩個state的metric

                path[next_state][i / 2] = k;
            }
        }

        else if (i == 2) //2個state進去，出去會有4個state
        {

            int tt_d[sizeof(distance) / sizeof(int)]; //把上個時間點的metric暫存起來，因為用原本的distance計算時會被洗掉
            for (int w = 0 ; w < sizeof(distance) / sizeof(int) ; w++)
            {
                tt_d[w] = distance[w];
            }

            int t_path[state_num][sizeof(r_data) / (2 * sizeof(int))]; //把上個時間點的path暫存起來
            for (int m = 0 ; m < i / 2 ; m++)
            {
                for (int n = 0 ; n < state_num ; n++)
                {
                    t_path[n][m] = path[n][m];
                }
            }

            for (int u = 0 ; u < state_num ; u += 128) //這個時間點input有S0、S128
            {
                for (int k = 0; k < 2; k++) //先算input為0，求出output再和r_data比較得distance，再算input為1
                {
                    int state = u; //兩個state跑向四個state
                    int next_state;
                    vv_code[0] = v0(k, state);
                    vv_code[1] = v1(k, state);
                    next_state = state_vary(k, state);
                    distance[next_state] = tt_d[state] + (r_data[i] + vv_code[0]) % 2 + (r_data[i + 1] + vv_code[1]) % 2;
                    for (int s = 0; s < i / 2; s++)
                    {
                        path[next_state][s] = t_path[state][s];
                    }
                    path[next_state][i / 2] = k;
                }
            }
        }

        else if (i == 4) //4個state為input，出去會有8個state
        {

            int tt_d[sizeof(distance) / sizeof(int)]; 
            for (int w = 0; w < sizeof(distance) / sizeof(int); w++)
            {
                tt_d[w] = distance[w];
            }
            int t_path[state_num][sizeof(r_data) / (2 * sizeof(int))]; 
            for (int m = 0; m < i / 2; m++)
            {
                for (int n = 0; n < state_num; n++)
                {
                    t_path[n][m] = path[n][m];
                }
            }
            for (int u = 0; u < state_num; u += 64) //這個時間點input有S0、S64、S128、S192
            {
                for (int k = 0; k < 2; k++)
                {
                    int state = u; 
                    int next_state;
                    vv_code[0] = v0(k, state);
                    vv_code[1] = v1(k, state);
                    next_state = state_vary(k, state);
                    distance[next_state] = tt_d[state] + (r_data[i] + vv_code[0]) % 2 + (r_data[i + 1] + vv_code[1]) % 2;
                    for (int s = 0; s < i / 2; s++)
                    {
                        path[next_state][s] = t_path[state][s];
                    }
                    path[next_state][i / 2] = k;
                }
            }
        }

        else if (i == 6) //8個state為input，出去會有16個state
        {

            int tt_d[sizeof(distance) / sizeof(int)]; 
            for (int w = 0; w < sizeof(distance) / sizeof(int); w++)
            {
                tt_d[w] = distance[w];
            }
            int t_path[state_num][sizeof(r_data) / (2 * sizeof(int))]; 
            for (int m = 0; m < i / 2; m++)
            {
                for (int n = 0; n < state_num; n++)
                {
                    t_path[n][m] = path[n][m];
                }
            }
            for (int u = 0; u < state_num; u += 32) //這個時間點input有S0、S32、S64、S96、S128、S160、192、S224
            {
                for (int k = 0; k < 2; k++)
                {
                    int state = u; 
                    int next_state;
                    vv_code[0] = v0(k, state);
                    vv_code[1] = v1(k, state);
                    next_state = state_vary(k, state);
                    distance[next_state] = tt_d[state] + (r_data[i] + vv_code[0]) % 2 + (r_data[i + 1] + vv_code[1]) % 2;
                    for (int s = 0; s < i / 2; s++)
                    {
                        path[next_state][s] = t_path[state][s];
                    }
                    path[next_state][i / 2] = k;
                }
            }
        }

        else if (i == 8) //8個state為input，出去會有16個state
        {
            int tt_d[sizeof(distance) / sizeof(int)]; 
            for (int w = 0; w < sizeof(distance) / sizeof(int); w++)
            {
               tt_d[w] = distance[w];
            }
            int t_path[state_num][sizeof(r_data) / (2 * sizeof(int))]; 
            for (int m = 0; m < i / 2; m++)
            {
               for (int n = 0; n < state_num; n++)
               {
                   t_path[n][m] = path[n][m];
               }
            }
            for (int u = 0; u < state_num; u += 16) //這個時間點input有S0、S16、S32、...、S208、S224、S240共16個
            {
                for (int k = 0; k < 2; k++)
                {
                    int state = u; 
                    int next_state;
                    vv_code[0] = v0(k, state);
                    vv_code[1] = v1(k, state);
                    next_state = state_vary(k, state);
                    distance[next_state] = tt_d[state] + (r_data[i] + vv_code[0]) % 2 + (r_data[i + 1] + vv_code[1]) % 2;
                    for (int s = 0; s < i / 2; s++)
                    {
                        path[next_state][s] = t_path[state][s];
                    }
                    path[next_state][i / 2] = k;
                }
            }
        }

        else if (i == 10) //16個state為input，出去會有32個state
        {
            int tt_d[sizeof(distance) / sizeof(int)]; 
            for (int w = 0; w < sizeof(distance) / sizeof(int); w++)
            {
               tt_d[w] = distance[w];
            }
            int t_path[state_num][sizeof(r_data) / (2 * sizeof(int))]; 
            for (int m = 0; m < i / 2; m++)
            {
                for (int n = 0; n < state_num; n++)
                {
                   t_path[n][m] = path[n][m];
               }
            }
            for (int u = 0; u < state_num; u += 8) //這個時間點input有S0、S8、S16、...、S232、S240、S248共16個
            {
                for (int k = 0; k < 2; k++)
                {
                   int state = u; 
                   int next_state;
                   vv_code[0] = v0(k, state);
                   vv_code[1] = v1(k, state);
                   next_state = state_vary(k, state);
                   distance[next_state] = tt_d[state] + (r_data[i] + vv_code[0]) % 2 + (r_data[i + 1] + vv_code[1]) % 2;
                   for (int s = 0; s < i / 2; s++)
                   {
                       path[next_state][s] = t_path[state][s];
                   }
                   path[next_state][i / 2] = k;
                }
            }
        }

        else if (i == 12) //32個state為input，出去會有64個state
        {
            int tt_d[sizeof(distance) / sizeof(int)]; 
            for (int w = 0; w < sizeof(distance) / sizeof(int); w++)
            {
                tt_d[w] = distance[w];
            }
            int t_path[state_num][sizeof(r_data) / (2 * sizeof(int))];
            for (int m = 0; m < i / 2; m++)
            {
                for (int n = 0; n < state_num; n++)
                {
                    t_path[n][m] = path[n][m];
                }
            }
            for (int u = 0; u < state_num; u += 4) //這個時間點input有S0、S4、S8、...、S244、S248、S252共32個
            {
                for (int k = 0; k < 2; k++)
                {
                    int state = u; 
                    int next_state;
                    vv_code[0] = v0(k, state);
                    vv_code[1] = v1(k, state);
                    next_state = state_vary(k, state);
                    distance[next_state] = tt_d[state] + (r_data[i] + vv_code[0]) % 2 + (r_data[i + 1] + vv_code[1]) % 2;
                    for (int s = 0; s < i / 2; s++)
                    {
                        path[next_state][s] = t_path[state][s];
                    }
                    path[next_state][i / 2] = k;
                }
            }
        }

        else if (i == 14) //64個state為input，出去會有128個state
        {
            int tt_d[sizeof(distance) / sizeof(int)]; 
            for (int w = 0; w < sizeof(distance) / sizeof(int); w++)
            {
                tt_d[w] = distance[w];
            }
            int t_path[state_num][sizeof(r_data) / (2 * sizeof(int))]; 
            for (int m = 0; m < i / 2; m++)
            {
                for (int n = 0; n < state_num; n++)
                {
                    t_path[n][m] = path[n][m];
                }
            }
            for (int u = 0; u < state_num; u += 2) //這個時間點input有S0、S2、S4、...、S250、S252、S254共64個
            {
                for (int k = 0; k < 2; k++)
                {
                    int state = u; 
                    int next_state;
                    vv_code[0] = v0(k, state);
                    vv_code[1] = v1(k, state);
                    next_state = state_vary(k, state);
                    distance[next_state] = tt_d[state] + (r_data[i] + vv_code[0]) % 2 + (r_data[i + 1] + vv_code[1]) % 2;
                    for (int s = 0; s < i / 2; s++)
                    {
                        path[next_state][s] = t_path[state][s];
                    }
                    path[next_state][i / 2] = k;
                }
            }
        }

        else //開始比較，這裡的寫法是倒敘法，藉由next state 來判斷會交會他的會是哪兩個state(這邊要找規律，不然會寫到死掉)，會發現交會的兩個state input都是一樣的，不是0就是1。
             //每個state分為input為0(上半部分)及input為1(下半部分)兩部分
        {
            int tt_d[sizeof(distance) / sizeof(int)];
            for (int w = 0; w < sizeof(distance) / sizeof(int); w++)
            {
                tt_d[w] = distance[w];
            }

            int t_path[state_num][sizeof(r_data) / (2 * sizeof(int))];
            for (int m = 0; m < i / 2; m++) //代表一次做半部分的state
            {
                for (int n = 0; n < state_num; n++) 
                {
                    t_path[n][m] = path[n][m];
                }
            }

            int d_1;
            int d_2;

            for (int state = 0 ; state < state_num / 2 ; state ++){ //上半部分的state(皆是input為0的)//從S0到S127                               
                vv_code[0] = v0(0 , (state + 1) * 2 - 1); //規律//S0從S0、S1//S1從S2、S3//S2從S4、S5...
                vv_code[1] = v1(0 , (state + 1) * 2 - 1);
                d_1 = tt_d[(state + 1) * 2 - 1] + (r_data[i] + vv_code[0]) % 2 + (r_data[i + 1] + vv_code[1]) % 2 ;//這邊已經把前一個state累積的distance加上去了
                
                vv_code[0] = v0(0 , (state + 1) * 2 - 2); //規律//S0從S0、S1//S1從S2、S3//S2從S4、S5...
                vv_code[1] = v1(0 , (state + 1) * 2 - 2);
                d_2 = tt_d[(state + 1) * 2 - 2] + (r_data[i] + vv_code[0]) % 2 + (r_data[i + 1] + vv_code[1]) % 2 ;//這邊已經把前一個state累積的distance加上去了
                
                if(d_1 > d_2){ //比較完distance後決定當個state的state metric//選state metric小的
                    distance[state] = d_2;
                    for (int s = 0 ; s < i / 2 ; s++){
                    path[state][s] = t_path[(state + 1 ) * 2 - 2][s];
                    }
                }
                else{
                    distance[state] = d_1;
                    for (int s = 0; s < i / 2 ; s++){
                    path[state][s] = t_path[(state + 1) * 2 - 1][s];
                    }
                }

                path[state][i / 2] = 0;
                }


            for (int state = state_num - 1 ; state > (state_num / 2) - 1 ; state --){ //下半部分的state(皆是input為1的)//從S255到S128//倒過來算
                int n_state = state - 128; //拿來做下面運算用                                
                vv_code[0] = v0(1 , (n_state + 1) * 2 - 1);//規律//S255從S254、S255//S254從S252、S253//S253從S250、S251...
                vv_code[1] = v1(1 , (n_state + 1) * 2 - 1);
                d_1= tt_d[(n_state + 1) * 2 - 1] + (r_data[i] + vv_code[0]) % 2 + (r_data[i + 1] + vv_code[1]) % 2 ;
               
                vv_code[0] = v0(1 , (n_state + 1) * 2 - 2);
                vv_code[1] = v1(1 , (n_state + 1) * 2 - 2);
                d_2= tt_d[(n_state + 1) * 2 - 2] + (r_data[i] + vv_code[0]) % 2 + (r_data[i + 1] + vv_code[1]) % 2 ;
               
                if(d_1 > d_2){ //比較完distance後決定當個state的state metric//選state metric小的
                    distance[state] = d_2;
                    for (int s = 0 ; s < i / 2 ; s ++){
                    path[state][s] = t_path[(n_state + 1) * 2 - 2][s];
                    }
                }
                else{
                    distance[state] = d_1;
                    for (int s = 0 ; s < i / 2 ; s ++){
                    path[state][s] = t_path[(n_state + 1) * 2 - 1][s];
                    }
                }
                path[state][i / 2] = 1;
                }
        }
        }
        /*for (int j = 0 ; j < sizeof(r_data) / (3 * sizeof(int)) ; j ++){
            printf("%d", path[0][j]);
        }*/



/*encoder convolutional code */

    int g_1[]={1,0,1,1,1,0,0,0,1}; //561
    int g_2[]={1,1,1,1,0,1,0,1,1}; //753

    int r_v[register_num]={0}; //register 裡面一開始的值

    int v[2]; //兩個output
    printf("r_data :\n");
    for(int i = 0 ; i < sizeof(r_data) / sizeof(int) ; i ++){
        printf("%d" , r_data[i]);
    }
    printf("\n\n");

    int u[sizeof(r_data) / (2 * sizeof(int))] = {0}; //decode結果//要encode的sequence
    printf("decode result:\n");
    for (int i = 0 ; i < sizeof(r_data) / (2 * sizeof(int)) ; i ++){ //把解出來的original data放進u中
        u[i] = path[0][i];
        printf("%d" , u[i]);
    }
    printf("\n\n");
    
    
    //int u[] = {0,0,1,1,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0,1,1,0,1,0,0,0,0,1,1,1,0,0,0,0,1,1,0,1,0,1,0,1,0,0,1,0,1,1,1,1,1,1,0,1,0,1,1,0,1,0,1,0,0,0,1,0,1,0,0,1,0,1,1,0,1,0,0,1,1,0,1,1,0,0,1,0,1,0,0,1,0,1,1,0,1,1,0,1,0,1,1,1,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,1,1,1,0,0,1,0,1,0,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,0,1,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,0,0,0,1,1,1,1,1,1,0,1,0,1,1,1,1,0,1,1,1,1,0,0,0,1,0,0,1,0,1,1,0,1,0,0,1,1,0,1,0,1,1,1,0,0,1,1,0,1,0,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0,1,0,0,1,1,0,1,1,1,0,1,0,1,0,1,1,0,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,1,0,1,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,0,0,0,0,0,0,1,0,0,1,1,1,1,1,0,1,0,1,1,1,0,0,0,0,0,0,1,0,0,1,1,0,0,0,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,1,0,1,1,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,0,0,0,1,0,0,1,1,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,1,0,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0};

    /*printf("u = ");
    for(int i = 1 ; i <= 32 ; i ++){
    printf("%d" , u[i]);
    }
    printf("\n");
    */

    int encoded_data[sizeof(u) / sizeof(int) * sizeof(g_1) / sizeof(g_1[0])]; //制定encode data大小
    
    int c = 0;

    for (int a = 0; a < sizeof(u) / sizeof(int); a++){ //做encode
        
            v[0] = (u[a] * g_1[0] + r_v[0] * g_1[1] + r_v[1] * g_1[2] + r_v[2] * g_1[3] + r_v[3] * g_1[4] + r_v[4] * g_1[5] + r_v[5] * g_1[6] + r_v[6] * g_1[7] + r_v[7] * g_1[8]) % 2; //要改
            v[1] = (u[a] * g_2[0] + r_v[0] * g_2[1] + r_v[1] * g_2[2] + r_v[2] * g_2[3] + r_v[3] * g_2[4] + r_v[4] * g_2[5] + r_v[5] * g_2[6] + r_v[6] * g_2[7] + r_v[7] * g_2[8]) % 2;
            
            for (int i = 0; i < 2; i ++){
                encoded_data[c] = v[i];//把全部值存進encode data中
                c++;
            }
    
            for (int b = sizeof(r_v) / sizeof(int); b > 1; b--){ //registor的值shift一位
                r_v[b - 1] = r_v[b - 2];
            }
                r_v[0] = u[a]; //input值shift進來
    }
    printf("encoded result:\n");
    for (int h = 0 ; h < 3 * sizeof(u) / sizeof(int) ; h ++){ //輸出encode結果
        printf("%d", encoded_data[h]);
    }
    printf("\n\n");
    printf("different bits:\n");

    for (int y = 0 ; y < 2 * sizeof(u) / sizeof(int) ; y ++){ //比較有錯的並輸出//比較有錯的r_data跟encode data的差異的位置，也就是有錯的位置print 出來

        if(r_data[y] != encoded_data[y]){
            printf("%d\n", y + 1);
        }
    }
        return 0;
}

