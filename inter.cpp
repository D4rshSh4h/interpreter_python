#include <iostream>
#include <string>

enum class Type{
    NUMBER,
    PLUS,
    END
};

std::ostream& operator<<(std::ostream& os, Type type){
    switch (type){
        case Type::NUMBER: return os<<"Number";
        case Type::PLUS: return os<<"Plus";
        case Type::END: return os<<"EOF";
        default: return os<<"Undefined";
    }
}

class Token{
    private:
        Type token_type;
        std::string value;
    
    public:
        Token(Type a, std::string b) : token_type(a), value(b) {}
        Type get_type() const {return token_type;}
        const std::string& get_value() const {return value;}
};




int main(void){
    Token mytoken = Token(Type::NUMBER, "3");
    Type t = mytoken.get_type();
    std::cout << t << std::endl;
    const std::string& v = mytoken.get_value();
    std::cout << v << std::endl;
    
}