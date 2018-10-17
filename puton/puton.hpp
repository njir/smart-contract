#include <string>
#include <vector>
#include <eosiolib/eosio.hpp> 
#include <random.cpp>

using namespace eosio; 
using namespace std;

// define singleton
random_gen random_gen::instance;

// struct post for user_table
struct postrow {
    uint64_t post_id = 0;
};

// struct comment for post_table
struct commentrow {
    uint64_t comment_id = 0;
};

class puton_service: public eosio::contract {

    public: 
        puton_service(account_name self): contract::contract(self),
                                          user_table(self, self),
                                          post_table(self, self) {}

        /// USER ACTIONS
        // @abi action 
        void createuser(const account_name account);

        /// POST ACTIONS
        // @abi action 
        void addpost(const account_name author, const string hash_value);

        // // @abi action 
        // void updatepost(const account_name author, const uint32_t id, const string hash_value);

        /// ETC
        // @abi action
        void printrandom(account_name author);

    private:

        // @abi table users 
        struct user {
            account_name account;
            std::vector<postrow> written_rows;

            auto primary_key() const { return account; }

            EOSLIB_SERIALIZE(user, (account)(written_rows))
        };

        // @abi table posts
        struct post {
            uint64_t id;
            account_name author;
            string post_hash;
            uint8_t like_cnt;
            std::vector<commentrow> comment_rows;
            time created_at;

            auto primary_key() const { return id; }

            EOSLIB_SERIALIZE(post, (id)(author)(post_hash)(like_cnt)(comment_rows)(created_at))
        };

        // define tables
        multi_index<N(users), user> user_table;
        multi_index<N(posts), post> post_table;

        // private variable
        std::vector<postrow> empty_postrows;
        postrow empty_postrow;

        std::vector<commentrow> empty_commentrows;
        postrow empty_commentrow;
 };

EOSIO_ABI(puton_service, (createuser)(addpost)(printrandom))