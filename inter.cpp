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
    
    void skip_whitespace(){
            while(text.at(pos) == 32){
                pos+=1;
            }
    }

    std::string get_number(){

        std::string number;
        
        char c = text.at(pos);
        while(c >= 48 && c <= 57 && pos < text.size()){
            c = text.at(pos);
            number += c;
            ++pos;
           
        }
        return number;
    }
    
    Token get_next_token(){
        int size_text = text.size();
        if(pos > size_text-1){
            return Token(Type::END, "__NONE__");
        }
        skip_whitespace();
        char c_p = text.at(pos);
        
        if (std::isdigit(c_p)){
            std::string val = get_number(); 
            return Token(Type::NUMBER,val);
        }
        if (c_p == '+'){
            pos += 1;
            std::string s(1, c_p);  
            return Token(Type::PLUS,s);
        }
        return Token(Type::ERROR, "");
    }

    void check(Type t){
        if(current_token.get_type() == t){
            current_token = get_next_token();
        }
        else{
            throw tokenError();
        }
    }

    long int expr(){
        current_token = get_next_token();
        std::string left = current_token.get_value();
        check(Type::NUMBER);

        Token op = current_token;
        check(Type::PLUS);

        std::string right = current_token.get_value();
        check(Type::NUMBER);

        return std::stoi(left) + std::stoi(right);

    }
};

int main(void){
    std::string text;
        std::cout << "Type 'e' to exit" << std::endl;
    while(true){
        
        std::cout << "Calc> ";
        std::getline(std::cin, text);
        if(text == "e"){
            return 0;
        }
        Interpreter I(text);
        long int result = I.expr();
        std::cout << result << std::endl;
    }
        
        
}

//TODO - handle inputs with more than one operator 