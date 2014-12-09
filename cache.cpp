/*
Calvin Huynh, Andy Polanco
CS 161L Spring 2014
Lab7 - Cache Simulator
*/
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

#define  BLOCK_SIZE     16
const int CACHE_SIZE[5] = {16384, 8192, 4096, 2048, 1024};
const int n_way[4] = {1, 2, 4, 8};

void FIFO_Policy(vector<unsigned long long> x){
  vector< vector<double> > print_info(4);
  for(int n_way_index = 0; n_way_index < 4; ++n_way_index){
     vector<double> print_line;
     for(int cache_size_index = 0; cache_size_index < 5; ++cache_size_index){
       int number_of_blocks = CACHE_SIZE[cache_size_index] / BLOCK_SIZE;
       int set = number_of_blocks/n_way[n_way_index];
       vector < vector <unsigned long long> > cache (set);
       for (int i = 0; i < set; ++i)
         for(int j = 0; j < n_way[n_way_index]; ++j)
           cache[i].push_back(0);
       
       // read memory accesses from standard input
       int total = 0, miss = 0;
       for (unsigned int tmpi = 0; tmpi < x.size(); ++tmpi) {
         total++;
         unsigned long long tag   = x[tmpi] >> (10 - cache_size_index - n_way_index + 4); // get tag
         unsigned long long index = x[tmpi] >> 4;        // get index
         index = index & (0x00000000000003FF >> (cache_size_index + n_way_index));
         // check for miss
         int check_miss = 0;
         for(int tmpj = 0; tmpj< n_way[n_way_index]; tmpj++){
           if (cache[index][tmpj] != tag) {
             check_miss++;
           }
         }
         
         if (check_miss == n_way[n_way_index]){
           ++miss;
           for(int r_index = 0; r_index < n_way[n_way_index]-1; ++r_index){
             cache[index][r_index] = cache[index][r_index+1];
           }
           cache[index][n_way[n_way_index]-1] = tag;
         }
       }
       double miss_rate = (double)miss / (double)(total);
       miss_rate *= 100;
       print_line.push_back(miss_rate);
     }
     print_info[n_way_index] = print_line;
   }
   cout << "\n      FIFO Replacement Policy\n";
   for(int i = 4; i >= 0; --i){
     cout << setfill(' ') << setw(7) << right << CACHE_SIZE[i];
   }
   for(unsigned int i = 0; i < print_info.size(); ++i){
     cout << "\n";
     cout << n_way[i] << " ";
     for(int j = print_info[i].size()-1; j >= 0; j--){
       cout << setfill('0') << setw(5) << right << setprecision(2) << fixed << print_info[i][j] << "  ";
     }
   }
}

void LRU_Policy(vector<unsigned long long> x){
  vector< vector<double> > print_info(4);
  for(int n_way_index = 0; n_way_index < 4; ++n_way_index){
     vector<double> print_line;
     for(int cache_size_index = 0; cache_size_index < 5; ++cache_size_index){
       int number_of_blocks = CACHE_SIZE[cache_size_index] / BLOCK_SIZE;
       int set = number_of_blocks/n_way[n_way_index];
       vector < vector <unsigned long long> > cache (set);
       for (int i = 0; i < set; ++i)
         for(int j = 0; j < n_way[n_way_index]; ++j)
           cache[i].push_back(0);
       
       // read memory accesses from standard input
       int total = 0, miss = 0;
       for (unsigned int tmpi = 0; tmpi < x.size(); ++tmpi) {
      
         total++;
         unsigned long long tag   = x[tmpi] >> (10 - cache_size_index - n_way_index + 4); // get tag
         unsigned long long index = x[tmpi] >> 4;        // get index
         index = index & (0x00000000000003FF >> (cache_size_index + n_way_index));
         // check for miss
         int check_miss = 0;
         for(int tmpj = 0; tmpj< n_way[n_way_index]; tmpj++){
           if (cache[index][tmpj] != tag) {
             check_miss++;
           }
           else if (cache[index][tmpj] == tag){
             if (tmpj == n_way[n_way_index]-1){}
             else{
               for(int copy_index = tmpj; copy_index < n_way[n_way_index]-1; ++copy_index){
                 cache[index][copy_index ] = cache[index][copy_index +1];
               }
               cache[index][n_way[n_way_index]-1] = tag;
             }
           }
         }
         if (check_miss == n_way[n_way_index]){
           ++miss;
           for(int r_index = 0; r_index < n_way[n_way_index]-1; ++r_index){
             cache[index][r_index] = cache[index][r_index+1];
           }
           cache[index][n_way[n_way_index]-1] = tag;
         }
       }
       double miss_rate = (double)miss / (double)(total);
       miss_rate *= 100;
       print_line.push_back(miss_rate);
     }
     print_info[n_way_index] = print_line;
   }
   cout << "\n      LRU Replacement Policy\n";
   for(int i = 4; i >= 0; --i){
     cout << setfill(' ') << setw(7) << right << CACHE_SIZE[i];
   }
   for(unsigned int i = 0; i < print_info.size(); ++i){
     cout << "\n";
     cout << n_way[i] << " ";
     for(int j = print_info[i].size()-1; j >= 0; j--){
       cout << setfill('0') << setw(5) << right << setprecision(2) << fixed << print_info[i][j] << "  ";
     }
   }
}

int main () {
   vector<unsigned long long> tmp_cache;
   unsigned long long read_line;
   while (cin >> hex >> read_line) {
     tmp_cache.push_back(read_line);
   }
   LRU_Policy(tmp_cache);
   cout << "\n";
   FIFO_Policy(tmp_cache);
   cout << "\n";
   return 0;
}


