#include <iostream>
#include <string>
#include <cctype>
#include <exception>

enum class Type{
    NUMBER,
    PLUS,
    ERROR,
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

class tokenError : public std::exception{
    private:
    std::string message = "Token types do not match";
    public:
    const char* what() const noexcept override{
        return message.c_str();
    }
};

class Token{
    private:
        Type token_type;
        std::string value;
    
    public:
        Token() = default;
        Token(Type a, std::string b) : token_type(a), value(b) {}
        Type get_type() const {return token_type;}
        const std::string& get_value() const {return value;}
};

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << "Token(Type: " << token.get_type() << ", Value: \"" << token.get_value() << "\")";
    return os;
}
class Interpreter{
    private:
        int pos = 0;
        std::string text;
        Token current_token;
    
    public:
        Interpreter(std::string s) : text(s) {}
    
    Token get_next_token(){
        int size_text = text.size();
        if(pos > size_text-1){
            return Token(Type::END, "__NONE__");
        }

        char c_p = text.at(pos);
        if (std::isdigit(c_p)){
            pos += 1;
            std::string s(1, c_p);  
            return Token(Type::NUMBER,s);
        }
        if (c_p == '+'){
            pos += 1;
            std::string s(1, c_p);  
            return Token(Type::PLUS,s);
        }
        return Token(Type::ERROR, "");
    }

    void check(Type t){
        if(current_token.get_type() != t){
            throw tokenError();
        }
    }
};




int main(void){
    std::string text;
    std::cout << "Calc> ";
    std::cin >> text;
    Interpreter I(text);
    
}