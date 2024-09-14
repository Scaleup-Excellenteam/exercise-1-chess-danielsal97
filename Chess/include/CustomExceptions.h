#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <exception>
#include <string>

class InvalidInputException : public std::exception {
public:
    InvalidInputException(const std::string& message) : msg_(message) {}
    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

class IllegalMoveException : public std::exception {
public:
    IllegalMoveException(const std::string& message) : msg_(message) {}
    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

class InvalidCastlingException : public std::exception {
public:
    InvalidCastlingException(const std::string& message) : msg_(message) {}
    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

class InvalidPromotionException : public std::exception {
public:
    InvalidPromotionException(const std::string& message) : msg_(message) {}
    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

#endif // CUSTOMEXCEPTIONS_H
