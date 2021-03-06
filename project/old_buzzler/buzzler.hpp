#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

using namespace eosio;
using std::string;

class buzzler : public eosio::contract
{

  public:
    using contract::contract;

    // @abi action
    void hello(account_name user);

    // @abi action
    void create(const account_name account,
                const string &nickname,
                const string &univ,
                const string &major);

    // @abi action
    void update(const account_name account,
                const string &nickname,
                const string &univ,
                const string &major,
                uint64_t token);

    // @abi action
    void remove(const account_name account);

    // @abi action
    void getuser(const account_name account);

    // @abi action
    void bytoken(uint64_t token);

    // @abi action
    void rangetoken(uint64_t less, uint64_t over);

  private:
    // @abi table users
    struct user
    {
        account_name account;
        string nickname;
        string univ;
        string major;
        uint64_t token;
        time created_at;

        account_name primary_key() const { return account; }
        uint64_t by_token() const { return token; }
        EOSLIB_SERIALIZE(user, (account)(nickname)(univ)(major)(token)(created_at))
    };

    typedef eosio::multi_index<
        N(users), user,
        indexed_by<N(token), const_mem_fun<user, uint64_t, &user::by_token>>>
        user_table;
};

EOSIO_ABI(buzzler, (hello)(create)(update)(remove)(getuser)(bytoken)(rangetoken))

///////

// account table
// - eosaccount_name
// - buzztoken
// - created_at

// - action
//     - create account ->

// post table
// - post_hash
// - amount(보상 토큰)
// - 모두 require_auth -> server
// - created_at

// post_like
// post_comment

// inline